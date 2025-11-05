#ifndef AUTO_RESERVATION_MESSAGES_H
#define AUTO_RESERVATION_MESSAGES_H

#include <log/message_types.h>

extern const isc::log::MessageID AUTO_RESERVATION_RUNTIME_LOGGING_BAD_TYPE;
extern const isc::log::MessageID AUTO_RESERVATION_MISSING_PARAMS;
extern const isc::log::MessageID AUTO_RESERVATION_ENABLED_PARAM_BAD_TYPE;
extern const isc::log::MessageID AUTO_RESERVATION_SUBNETS_PARAM_BAD_TYPE;
extern const isc::log::MessageID AUTO_RESERVATION_SUBNET_VALUE_BAD_TYPE;
extern const isc::log::MessageID AUTO_RESERVATION_DHCP4_CONFIG_FILE_NOT_EXIST;
extern const isc::log::MessageID AUTO_RESERVATION_SUBNET_VALUE_NOT_SUBNET;
extern const isc::log::MessageID AUTO_RESERVATION_UNEXPECTED_ERROR;
extern const isc::log::MessageID AUTO_RESERVATION_UNLOAD_SUCCESS;
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_RESERVED_SUCCESSFULLY;
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_NOT_RESERVED;
extern const isc::log::MessageID AUTO_RESERVATION_LEASE_ALREADY_ADDED;

#endif
