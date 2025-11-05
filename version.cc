#include <config.h>

#include <hooks/hooks.h>

namespace isc {
namespace auto_reservation {

extern "C" {

int
version() {
    return (KEA_HOOKS_VERSION);
}

}  // extern "C"

}  // namespace auto_reservation
}  // namespace isc
