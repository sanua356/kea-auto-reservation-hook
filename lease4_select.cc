// lease4_select.cc
#include <dhcp/pkt4.h>

#include <exception>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>

#include <auto_reservation.h>
#include <auto_reservation_log.h>

#include "dhcpsrv/host.h"
#include "dhcpsrv/host_mgr.h"
#include "dhcpsrv/lease.h"
#include "dhcpsrv/subnet.h"
#include "dhcpsrv/subnet_id.h"
#include "log/macros.h"

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::auto_reservation;
using namespace isc::data;

namespace {
bool runtime_logging = false;
bool enabled = false;
std::vector<std::string> subnets;
}  // namespace

namespace isc {
namespace auto_reservation {

void
storeConfiguration(bool param_runtime_logging,
                   bool param_enabled,
                   std::vector<std::string> param_subnets) {
    runtime_logging = param_runtime_logging;
    enabled = param_enabled;
    subnets = param_subnets;
}

void
clearConfiguration() {
    runtime_logging = false;
    enabled = false;
    subnets.clear();
}
}  // namespace auto_reservation
}  // namespace isc

extern "C" {

int
lease4_select(CalloutHandle& handle) {
    // If a packet has already been dropped, the hook is not allowed to change its status.
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP || status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    if (!enabled) {
        return (0);
    }

    Lease4Ptr lease4_ptr;
    ConstSubnet4Ptr subnet4_ptr;
    handle.getArgument("lease4", lease4_ptr);
    handle.getArgument("subnet4", subnet4_ptr);

    if (!lease4_ptr || !subnet4_ptr) {
        return (0);
    }

    if (!lease4_ptr->addr_.isV4()) {
        return (0);
    }

    std::string hwaddr_text = lease4_ptr->hwaddr_->toText(false);
    std::string subnet_ip_with_netmask = subnet4_ptr.get()->toText();
    SubnetID subnet_id = lease4_ptr->subnet_id_;

    bool is_found = false;
    for (size_t i = 0; i < subnets.size(); i++) {
        if (subnets[i] == subnet_ip_with_netmask) {
            is_found = true;
            break;
        }
    }

    // If the subnet is not specified in the hook configuration, do not take any action.
    if (!is_found) {
        return (0);
    }

    try {
        ConstHostPtr reservation = HostMgr::instance().get4(lease4_ptr->subnet_id_,
                                                            lease4_ptr->addr_,
                                                            HostMgrOperationTarget::PRIMARY_SOURCE);

        if (reservation) {
            if (runtime_logging) {
                LOG_INFO(auto_reservation_logger, AUTO_RESERVATION_LEASE_ALREADY_ADDED)
                    .arg(lease4_ptr->hwaddr_)
                    .arg(lease4_ptr->addr_)
                    .arg(lease4_ptr->hostname_);
            }
            return (0);
        }

        // We create an instance for writing to the global config.
        // SUBNET_ID_UNUSED is specified intentionally, as this parameter expects an IPv6 subnet ID.
        HostPtr host = boost::make_shared<Host>(hwaddr_text, "hw-address", subnet_id,
                                                SubnetID(SUBNET_ID_UNUSED), lease4_ptr->addr_,
                                                lease4_ptr->hostname_);

        // HostMgrOperationTarget::PRIMARY_SOURCE is specified to explicitly define that the server
        // configuration is being changed, and not third-party backends.
        HostMgr::instance().add(host, HostMgrOperationTarget::PRIMARY_SOURCE);

        if (runtime_logging) {
            // The log message must contain "%number" which will be substituted into .arg().
            LOG_INFO(auto_reservation_logger, AUTO_RESERVATION_LEASE_RESERVED_SUCCESSFULLY)
                .arg(lease4_ptr->hwaddr_)
                .arg(lease4_ptr->addr_)
                .arg(lease4_ptr->hostname_);
        }

        return (0);

    } catch (const std::exception& ex) {
        LOG_ERROR(auto_reservation_logger, AUTO_RESERVATION_UNEXPECTED_ERROR).arg(ex.what());

        if (runtime_logging) {
            LOG_INFO(auto_reservation_logger, AUTO_RESERVATION_LEASE_NOT_RESERVED)
                .arg(lease4_ptr->hwaddr_)
                .arg(lease4_ptr->addr_)
                .arg(lease4_ptr->hostname_);
        }
        return (1);
    }

    return (0);
}  // namespace auto_reservation
}  // namespace isc
