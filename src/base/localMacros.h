#ifndef LOCALMACROS_H
#define LOCALMACROS_H

#include <string>

using namespace std::string_literals;

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

#endif // LOCALMACROS_H
