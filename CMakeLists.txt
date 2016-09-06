cmake_minimum_required (VERSION 3.5)

# Using experimental C++ features, including c++14 and c++17.
set(CMAKE_CXX_FLAGS "-std=c++1z")

project(zenplugin)

# Don't build in this directory
# mkdir ../zen-plugin-build
# cd ../zen-plugin-build
# cmake ../zen-plugin
# make
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)


find_file ( UNISTD_H unistd.h ENV )
if ( UNISTD_H )
    add_definitions( -DHOST_POSIX )
    add_definitions( -DTHREADMODEL_POSIX )
endif ( UNISTD_H )

find_file ( WINDOWS_H windows.h ENV )
if ( WINDOWS_H )
    add_definitions( -DHOST_WIN32 )
	add_definitions( -DTHREADMODEL_WIN32 )
endif ( WINDOWS_H )

find_package(Boost REQUIRED unit_test_framework)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCES
  lib/I_ClassFactory.cpp
  lib/I_Configuration.cpp
  lib/I_ConfigurationElement.cpp
  lib/I_Extension.cpp
  lib/I_ExtensionFactory.cpp
  lib/I_ExtensionPoint.cpp
  lib/I_ExtensionRegistry.cpp
  lib/I_Module.cpp
  lib/I_Plugin.cpp
  lib/I_PluginManager.cpp)

set(HEADERS
  include/Zen/Plugin/I_Configuration.hpp
)

add_definitions(-DZEN_PLUGIN_EXPORTS)
add_definitions(-DBOOST_TEST_DYN_LINK) 

add_library(zen-plugin ${SOURCES})

enable_testing()

set(TEST_SOURCES
  test/simple.cpp
)

add_executable(zen-plugin-tests ${TEST_SOURCES})

target_link_libraries(zen-plugin-tests zen-plugin
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(tests zen-plugin-tests)

install(TARGETS zen-plugin DESTINATION /usr/local/bin)
install(DIRECTORY include DESTINATION /usr/local)
