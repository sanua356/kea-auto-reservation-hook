#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID AUTO_RESERVATION_RUNTIME_LOGGING_BAD_TYPE = "AUTO_RESERVATION_RUNTIME_LOGGING_BAD_TYPE";
extern const isc::log::MessageID AUTO_RESERVATION_MISSING_PARAMS = "AUTO_RESERVATION_MISSING_PARAMS";
extern const isc::log::MessageID AUTO_RESERVATION_ENABLED_PARAM_BAD_TYPE = "AUTO_RESERVATION_ENABLED_PARAM_BAD_TYPE";
extern const isc::log::MessageID AUTO_RESERVATION_SUBNETS_PARAM_BAD_TYPE = "AUTO_RESERVATION_SUBNETS_PARAM_BAD_TYPE";
extern const isc::log::MessageID AUTO_RESERVATION_SUBNET_VALUE_BAD_TYPE = "AUTO_RESERVATION_SUBNET_VALUE_BAD_TYPE";
extern const isc::log::MessageID AUTO_RESERVATION_DHCP4_CONFIG_FILE_NOT_EXIST = "AUTO_RESERVATION_DHCP4_CONFIG_FILE_NOT_EXIST";
extern const isc::log::MessageID AUTO_RESERVATION_SUBNET_VALUE_NOT_SUBNET = "AUTO_RESERVATION_SUBNET_VALUE_NOT_SUBNET";
extern const isc::log::MessageID AUTO_RESERVATION_UNEXPECTED_ERROR = "AUTO_RESERVATION_UNEXPECTED_ERROR";
extern const isc::log::MessageID AUTO_RESERVATION_UNLOAD_SUCCESS = "AUTO_RESERVATION_UNLOAD_SUCCESS";
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_RESERVED_SUCCESSFULLY = "AUTO_RESERVATION_LEASE_RESERVED_SUCCESSFULLY";
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_NOT_RESERVED = "AUTO_RESERVATION_LEASE_NOT_RESERVED";
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_ALREADY_ADDED = "AUTO_RESERVATION_LEASE_ALREADY_ADDED";

namespace {

const char* values[] = {
    "AUTO_RESERVATION_RUNTIME_LOGGING_BAD_TYPE", "Param \"runtime-logging\" must be of boolean type.",
    "AUTO_RESERVATION_MISSING_PARAMS", "Hook awaiting required parameters: \"enabled\" and \"subnets\".",
    "AUTO_RESERVATION_ENABLED_PARAM_BAD_TYPE", "Param \"enabled\" must be of boolean type.",
    "AUTO_RESERVATION_SUBNETS_PARAM_BAD_TYPE", "Param \"subnets\" must be list of strings type.",
    "AUTO_RESERVATION_SUBNET_VALUE_BAD_TYPE", "One or more values of the \"subnets\" parameter has a non-string data type.",
    "AUTO_RESERVATION_DHCP4_CONFIG_FILE_NOT_EXIST", "DHCP4 config file is not exist.",
    "AUTO_RESERVATION_SUBNET_VALUE_NOT_SUBNET", "One or more values of the \"subnets\" parameter does not have a format that does not match the pattern: IPv4-address/netmask.",
    "AUTO_RESERVATION_UNEXPECTED_ERROR", "An unexpected error occurred while turning on the hook.",
    "AUTO_RESERVATION_UNLOAD_SUCCESS", "Hook unloaded successfully.",
    "AUTO_RESERVATION_LEASE_RESERVED_SUCCESSFULLY", "An IP address is reserved for the client with the specified MAC address. MAC: %1, IPV4: %2, Hostname: (may be empty) %3.",
    "AUTO_RESERVATION_LEASE_NOT_RESERVED", "It was not possible to reserve an IP address for the client with the specified MAC address. MAC: %1, IPV4: %2, Hostname: (may be empty) %3.",
    "AUTO_RESERVATION_LEASE_ALREADY_ADDED", "Reservation with hostname already added. MAC: %1, IPV4: %2, Hostname: (may be empty) %3.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace
