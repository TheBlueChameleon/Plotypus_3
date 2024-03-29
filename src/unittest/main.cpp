#include <iostream>

#include "unittest.h"
#include "unittest_procs.h"

#include "showcase.h"

// ========================================================================== //
// main

int main()
{
    std::cout << "UNIT TEST MAIN" << std::endl;

#if false
    UNITTEST_MAIN_VARS;

    // ...................................................................... //

    std::cout << "REGISTERING UNIT TESTS ... " << std::flush;

    ADD_UNITTEST(unittest_report_basicSheetManagement);
    ADD_UNITTEST(unittest_report_emptyScriptOutput);
    ADD_UNITTEST(unittest_report_sheets_scriptOutput);
    ADD_UNITTEST(unittest_sheets_labels);

    std::cout << "DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "ABOUT TO RUN UNIT TESTS" << std::endl;

    RUN_UNITTESTS;

    std::cout << "ALL REGISTERED UNIT TESTS DONE" << std::endl << std::endl;

    // ...................................................................... //

    std::cout << "UNIT TESTS SUMMARY" << std::endl;

    SUMMARIZE_UNITTESTS;
#endif
    // ...................................................................... //

    std::cout << std::endl;
    std::cout << "SHOWCASE CODE BEGINS HERE" << std::endl;

    SHOWCASE_TXT_REPORT = false;

    showcase_environment();
    showcase_minimal();
    showcase_run(Showcases::All);

    return 0;
}
