#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>

#define PLOTYPUS_ERROR(ErrorClassName) \
    class ErrorClassName : public PlotypusError { \
        public : ErrorClassName (const std::string & m) : PlotypusError(m) {} \
    }

namespace Plotypus
{
//! @addtogroup Platypus_Definitions
//! @{
    /**
     * @brief thrown when trying to set an invalid file name
     */

    // *INDENT-OFF*
    class PlotypusError : public std::runtime_error {
        public : PlotypusError (const std::string& m) : std::runtime_error(m) {};
    };
    // *INDENT-ON*

    PLOTYPUS_ERROR(InvalidFilenameError);
    PLOTYPUS_ERROR(InvalidIndexError);
    PLOTYPUS_ERROR(InvalidArgumentError);

    PLOTYPUS_ERROR(FileIOError);

    PLOTYPUS_ERROR(IncompleteDescritporError);

    PLOTYPUS_ERROR(UnsupportedOperationError);
//! @}
}

#endif // ERRORS_H
