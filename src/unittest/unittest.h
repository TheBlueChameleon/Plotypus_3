// ========================================================================== //
// template function

/*
bool unittest_foobar()
{
    std::cout << "TESTING FOOBAR CLASS" << std::endl;

    UNITTEST_VARS;

    // ...................................................................... //

    UNITTEST_ASSERT(
        1 == 1,
        "assert basic logic"
        );

    // ...................................................................... //

    UNITTEST_FINALIZE;
}
*/

// ========================================================================== //
// true code

#ifndef UNITTESTMACROS_H
#define UNITTESTMACROS_H

// ========================================================================== //
// dependencies

#include <stdexcept>

#include <string>
#include <sstream>
#include <vector>

// ========================================================================== //
// type defs

using unittest_list_t = std::vector<std::pair<std::string, std::function<bool()>>>;

// ========================================================================== //
// macros

// -------------------------------------------------------------------------- //
// main module

#define UNITTEST_MAIN_VARS \
    unittest_list_t             unittest_list; \
    std::vector<std::string>    unittest_fails;

#define ADD_UNITTEST(func) {unittest_list.emplace_back(std::make_pair(#func, func));}

#define RUN_UNITTESTS { \
        for (auto & [name, func] : unittest_list) { \
            std::cout << "### STARTING TEST '" << name << "' ..." << std::endl; \
            if (! func()) { \
                unittest_fails.push_back(name); \
                std::cout << "~~~ FAILED!" << std::endl; \
            } else { \
                std::cout << "~~~ PASSED!" << std::endl; \
            } \
        } \
    }

#define SUMMARIZE_UNITTESTS {unittest_show_summary(unittest_list, unittest_fails);}

//    std::cout << "Passed " << unittest_list.size() - unittest_fails.size() << "/" << unittest_list.size() << " tests"  << std::endl; \
//    if (!unittest_fails.empty()) { \
//        std::cout << "Failed Tests:" << std::endl; \
//        for (auto& name : unittest_fails) {std::cout << "~~~ " << name << std::endl;} \
//    }

// -------------------------------------------------------------------------- //
// unittest modules

#define UNITTEST_VARS \
    bool              unittest_result      = true; \
    bool              unittest_last_result = true; \
    bool              unittest_captureCerr = false; \
    std::stringstream unittest_cerrBuffer; \
    std::streambuf*   unittest_originalCerr;

#define UNITTEST_FINALIZE \
    if (unittest_captureCerr) {UNITTEST_RELEASE_CERR;} \
    return unittest_result;

#define UNITTEST_CRITICAL_BARRIER \
    if (!unittest_last_result) { throw std::runtime_error("Inconsistent state of the unittest framework"); }

// .......................................................................... //

#define UNITTEST_ASSERT(expr, taskDescription) \
    unittest_last_result = expr; \
    if (unittest_last_result) {std::cout << "  succeeded to " << taskDescription << std::endl;} \
    else                      {std::cout << "  failed to " << taskDescription << std::endl;} \
    unittest_result &= unittest_last_result;

// .......................................................................... //

#define UNITTEST_THROWS(expr, exception, taskDescription) \
    try { \
        unittest_last_result = false; expr; \
    } catch (const exception& e) { \
        unittest_last_result = true; \
    } \
    if (unittest_last_result) {std::cout << "  succeeded to " << taskDescription << std::endl;} \
    else                      {std::cout << "  failed to "    << taskDescription << std::endl;} \
    unittest_result &= unittest_last_result;

#define UNITTEST_DOESNT_THROW(expr, exception, taskDescription) \
    try { \
        unittest_last_result = true; expr; \
    } catch (const exception& e) { \
        unittest_last_result = false; \
        std::cout << "  " << e.what() << std::endl; \
    } \
    if (unittest_last_result) {std::cout << "  succeeded to " << taskDescription << std::endl;} \
    else                      {std::cout << "  failed to " << taskDescription << std::endl;} \
    unittest_result &= unittest_last_result;

// .......................................................................... //

#define UNITTEST_CAPTURE_CERR \
    unittest_captureCerr  = true; \
    unittest_originalCerr = std::cerr.rdbuf(unittest_cerrBuffer.rdbuf());

#define UNITTEST_RELEASE_CERR \
    if (unittest_cerrBuffer.str().length()) {\
        std::cout << "  Warning: Unprocessed messages in CERR:" << std::endl; \
        std::cout << "    " << unittest_cerrBuffer.str() << std::endl; \
    } \
    std::cerr.rdbuf( unittest_originalCerr );

#define UNITTEST_CLEAR_CERR \
    unittest_cerrBuffer.str("");

#define UNITTEST_ASSERT_STATE_CERR(cerrText, taskDescription) \
    UNITTEST_ASSERT(unittest_cerrBuffer.str() == cerrText, taskDescription); \
    if (!unittest_last_result) { \
        std::cout << "    found state:" << std::endl; \
        std::cout << "      '" << unittest_cerrBuffer.str() << "'"<< std::endl; \
        std::cout << "    expected state:" << std::endl; \
        std::cout << "      '" << cerrText << "'"<< std::endl; \
    }

#define UNITTEST_ASSERT_AND_CLEAR_CERR(cerrText, taskDescription) \
    UNITTEST_ASSERT_STATE_CERR(cerrText, taskDescription); \
    UNITTEST_CLEAR_CERR;

#define UNITTEST_ASSERT_OUTPUTS_ON_CERR(expr, cerrText, taskDescription) \
    UNITTEST_CLEAR_CERR; \
    expr; \
    UNITTEST_ASSERT_STATE_CERR(cerrText, taskDescription)


// ========================================================================== //
// type

using Unittest_RessorceList = std::vector<std::string>;

// ========================================================================== //
// procs

void unittest_check_files_present(const Unittest_RessorceList& files);
void unittest_check_directories  (const Unittest_RessorceList& directories);
void unittest_show_summary(const unittest_list_t& unittest_list, const std::vector<std::string>& unittest_fails);

#endif // UNITTESTMACROS_H
