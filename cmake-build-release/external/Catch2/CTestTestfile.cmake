# CMake generated Testfile for 
# Source directory: /home/anders/CLionProjects/untitled2/external/Catch2
# Build directory: /home/anders/CLionProjects/untitled2/cmake-build-release/external/Catch2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RunTests "/home/anders/CLionProjects/untitled2/builds/SelfTest")
add_test(ListTests "/home/anders/CLionProjects/untitled2/builds/SelfTest" "--list-tests")
set_tests_properties(ListTests PROPERTIES  PASS_REGULAR_EXPRESSION "[0-9]+ test cases")
add_test(ListTags "/home/anders/CLionProjects/untitled2/builds/SelfTest" "--list-tags")
set_tests_properties(ListTags PROPERTIES  PASS_REGULAR_EXPRESSION "[0-9]+ tags")
add_test(ApprovalTests "python" "/home/anders/CLionProjects/untitled2/external/Catch2/scripts/approvalTests.py" "/home/anders/CLionProjects/untitled2/builds/SelfTest")
set_tests_properties(ApprovalTests PROPERTIES  FAIL_REGULAR_EXPRESSION "Results differed")
