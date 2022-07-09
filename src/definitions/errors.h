#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>

#define PLOTYPUS_ERROR(ErrorClassName) \
    class ErrorClassName : public std::runtime_error { \
        public : ErrorClassName (const std::string & m) : std::runtime_error(m) {} \
    }

namespace Plotypus
{
//! @addtogroup Platypus_Definitions
//! @{
    /**
     * @brief thrown when trying to set an invalid file name
     */
    PLOTYPUS_ERROR(InvalidFilenameError);
    PLOTYPUS_ERROR(InvalidIndexError);
//! @}
}

#endif // ERRORS_H
