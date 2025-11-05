#ifndef AUTO_RESERVATION_H
#define AUTO_RESERVATION_H

#include <log/macros.h>
#include <log/message_initializer.h>

#include <auto_reservation_messages.h>

namespace isc {
namespace auto_reservation {

void
storeConfiguration(bool runtime_logging, bool enabled, std::vector<std::string> subnets);

void
clearConfiguration();

}  // namespace auto_reservation
}  // namespace isc

#endif
