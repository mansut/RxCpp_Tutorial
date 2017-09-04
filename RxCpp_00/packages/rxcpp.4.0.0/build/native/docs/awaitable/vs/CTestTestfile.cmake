# CMake generated Testfile for 
# Source directory: C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable
# Build directory: C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(RunTests "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs/Debug/awaitable.exe")
  set_tests_properties(RunTests PROPERTIES  WORKING_DIRECTORY "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(RunTests "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs/Release/awaitable.exe")
  set_tests_properties(RunTests PROPERTIES  WORKING_DIRECTORY "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(RunTests "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs/MinSizeRel/awaitable.exe")
  set_tests_properties(RunTests PROPERTIES  WORKING_DIRECTORY "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(RunTests "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs/RelWithDebInfo/awaitable.exe")
  set_tests_properties(RunTests PROPERTIES  WORKING_DIRECTORY "C:/Users/kshoop/Desktop/source/rxcpp/Rx/v2/examples/awaitable/vs")
else()
  add_test(RunTests NOT_AVAILABLE)
endif()
