// ========================================================================== //
// Depenencies

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
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
