@echo off

set SYSTEMC_PATH=..\..\..\libs\systemc-2.3.3
set SYSTEMC_SRC_PATH=%SYSTEMC_PATH%\src
set SYSTEMC_LIB_DBG_PATH=%SYSTEMC_PATH%\msvc10\SystemC\x64\Debug
set SYSTEMC_LIB_RELEASE_PATH=%SYSTEMC_PATH%\msvc10\SystemC\x64\Release

set GTEST_PATH=..\..\..\libs\googletest\googletest
set GTEST_INCLUDE_PATH=%GTEST_PATH%\include

call msvc\FreeSourceC_DevEnv_SystemC.sln