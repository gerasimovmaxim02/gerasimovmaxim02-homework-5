cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
		GIT_REPOSITORY    https://github.com/google/googletest.git
		GIT_TAG           release-1.10.0
		SOURCE_DIR        "C:/Users/geras/CLionProjects/gerasimovmaxim02-homework-5/cmake-build-debug-mingw/googletest-src"
		BINARY_DIR        "C:/Users/geras/CLionProjects/gerasimovmaxim02-homework-5/cmake-build-debug-mingw/googletest-build"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND     ""
		INSTALL_COMMAND   ""
		TEST_COMMAND      ""
		)
