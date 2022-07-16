#ifndef LOCALMACROS_H
#define LOCALMACROS_H

#include <string>

using namespace std::string_literals;

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)
#define THROW_INVALID_INDEX(i, indexName) {throw Plotypus::InvalidIndexError(THROWTEXT("    Invalid "s + indexName + ": " + std::to_string(i)));}
#define CHECK_INDEX(i, vector, indexName) { if (i >= vector.size() || (i < 0)) {THROW_INVALID_INDEX(i, indexName);} }



#endif // LOCALMACROS_H
