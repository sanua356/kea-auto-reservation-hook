#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <cc/dhcp_config_error.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config.h>
#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>
#include <process/daemon.h>

#include <regex>
#include <string>
#include <vector>

#include <auto_reservation.h>
#include <auto_reservation_log.h>

#include "cc/data.h"
#include "log/macros.h"

namespace isc {
namespace auto_reservation {

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::hooks;

static std::regex IPV4_WITH_NETMASK_PATTERN(
    R"(^((25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)(\/(3[0-2]|[12]?\d))$)");

extern "C" {
int
load(isc::hooks::LibraryHandle& handle) {
    try {
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected,
                          "Bad process name: " << proc_name << ", expected kea-dhcp4");
            }
        }

        ConstElementPtr enabled = handle.getParameter("enabled");
        ConstElementPtr subnets = handle.getParameter("subnets");

        // Not required param
        ConstElementPtr runtime_logging = handle.getParameter("runtime-logging");

        bool runtime_logging_value = false;

        if (runtime_logging != nullptr) {
            if (runtime_logging->getType() != Element::boolean) {
                LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_RUNTIME_LOGGING_BAD_TYPE);
                return (1);
            }
            runtime_logging_value = runtime_logging->boolValue();
        }
        if (enabled == nullptr || subnets == nullptr) {
            LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_MISSING_PARAMS);
            return (1);
        }

        if (enabled->getType() != Element::boolean) {
            LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_ENABLED_PARAM_BAD_TYPE);
            return (1);
        }

        if (subnets->getType() != Element::list) {
            LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_SUBNETS_PARAM_BAD_TYPE);
            return (1);
        }

        int enabled_value = enabled->boolValue();
        std::vector<std::string> subnets_value = {};

        for (auto& el : subnets->listValue()) {
            if (el->getType() == Element::string) {
                std::string subnet = el->stringValue();

                if (!std::regex_match(subnet, IPV4_WITH_NETMASK_PATTERN)) {
                    LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_SUBNET_VALUE_NOT_SUBNET);
                    return (1);
                }

                subnets_value.push_back(subnet);
            } else {
                LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_SUBNET_VALUE_BAD_TYPE);
                return (1);
            }
        }

        clearConfiguration();
        storeConfiguration(runtime_logging_value, enabled_value, subnets_value);
        return (0);
    } catch (const std::exception& ex) {
        LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_UNEXPECTED_ERROR);
        return (1);
    }
}

int
unload() {
    clearConfiguration();
    LOG_INFO(auto_reservation_logger, AUTO_RESERVATION_UNLOAD_SUCCESS);
    return (0);
}

int
multi_threading_compatible() {
    return (1);
}
}

}  // namespace auto_reservation
}  // namespace isc
