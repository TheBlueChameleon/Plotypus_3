#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <string>

namespace Plotypus
{
    void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest);

    void runGnuplot(const std::string& filename, bool verbose = true);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);
};

#endif // UTIL_H
