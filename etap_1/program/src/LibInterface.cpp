#include <dlfcn.h>
#include "LibInterface.hh"

/*!
 * \brief Destruktor zwalniający zasoby biblioteki.
 *
 * Zamyka uchwyt do biblioteki dynamicznej, jeśli był otwarty.
 */
LibInterface::~LibInterface() {
    if (pLibHnd) {
        dlclose(pLibHnd);
    }
}