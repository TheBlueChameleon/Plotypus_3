// ========================================================================== //
// Depenencies

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "unittest.h"

namespace fs = std::filesystem;
using namespace std::string_literals;

#include "unittest.h"

// ========================================================================== //
// procs

void unittest_check_files_present(const Unittest_RessorceList& files)
{
    for (auto& file : files)
    {
        // *INDENT-OFF*
        if (!fs::exists (file)) {throw std::runtime_error("Inconsistent state of test system: file '"s + file + "' not found");}
        if (fs::is_empty(file)) {throw std::runtime_error("Inconsistent state of test system: file '"s + file + "' is empty");}
        // *INDENT-ON*
    }
}

void unittest_check_directories(const Unittest_RessorceList& directories)
{
    for (auto& directory : directories)
    {
        // *INDENT-OFF*
        if (!fs::exists      (directory)) {throw std::runtime_error("Inconsistent state of test system: directory '"s + directory  + "' not found");}
        if (!fs::is_directory(directory)) {throw std::runtime_error("Inconsistent state of test system: directory '"s + directory  + "' is not a directory");}
        if (fs::is_empty     (directory)) {throw std::runtime_error("Inconsistent state of test system: directory '"s + directory  + "' is empty");}
        // *INDENT-ON*
    }
}

void unittest_show_summary(const unittest_list_t& unittest_list, const std::vector<std::string>& unittest_fails)
{
    std::cout << "Passed " << unittest_list.size() - unittest_fails.size() << "/" << unittest_list.size() << " tests"  << std::endl;
    if (!unittest_fails.empty())
    {
        std::cout << "Failed Tests:" << std::endl;
        for (auto& name : unittest_fails)
        {
            std::cout << "~~~ " << name << std::endl;
        }
    }
}

bool unittest_string_compare_by_lines(const std::string& lhs, const std::string& rhs)
{
    // *INDENT-OFF*
    if (lhs == rhs) {return true;}

    const size_t maxLen = std::min( lhs.length(), rhs.length() );
    size_t lhs_line      = 1u, rhs_line      = 1u;
    size_t lhs_lineStart = 0u, rhs_lineStart = 0u;
    size_t lhs_lineEnd   = 0u, rhs_lineEnd   = 0u;

    for (size_t i = 0; i < maxLen; ++i) {
        if (lhs[i] == '\n') {++lhs_line; lhs_lineStart = i + 1;}
        if (rhs[i] == '\n') {++rhs_line; rhs_lineStart = i + 1;}

        if (lhs[i] != rhs[i]) {
            std::cout << "    Discrepancy detected in LHS line "<< lhs_line << " (RHS line " << rhs_line << "), index " << i << ":" << std::endl;

            lhs_lineEnd = lhs.find('\n', i); if (lhs_lineEnd == std::string::npos) {lhs_lineEnd = lhs.length() -1;}
            rhs_lineEnd = rhs.find('\n', i); if (rhs_lineEnd == std::string::npos) {rhs_lineEnd = lhs.length() -1;}

            std::string_view lhs_view(lhs.begin() + lhs_lineStart, lhs.begin() + lhs_lineEnd);
            std::string_view rhs_view(rhs.begin() + rhs_lineStart, rhs.begin() + rhs_lineEnd);

            std::cout << "    LHS:" << std::endl;
            std::cout << "    " << std::quoted(lhs_view) << std::endl;

            std::cout << "    RHS:" << std::endl;
            std::cout << "    " << std::quoted(rhs_view) << std::endl;

            std::cout << std::endl;
            return false;
        }
    }

    std::cout << "    Discrepancy detected at rear of strings to compare:" << std::endl;
    if (lhs.length() > maxLen) {
        std::string_view view(lhs.begin() + maxLen, lhs.end());
        std::cout << "    LHS has trailing string:" << std::endl;
        std::cout << "    " << std::quoted(view) << std::endl;
    } else {
        std::string_view view(rhs.begin() + maxLen, rhs.end());
        std::cout << "    RHS has trailing string:" << std::endl;
        std::cout << "    " << std::quoted(view) << std::endl;
    }

    // *INDENT-OFF*
    return false;
}
