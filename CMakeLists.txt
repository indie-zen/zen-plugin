cmake_minimum_required (VERSION 3.5)

# Using experimental C++ features, including c++14 and c++17.
set(CMAKE_CXX_FLAGS "-std=c++11")

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

find_package(Boost REQUIRED unit_test_framework system filesystem)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCES
  lib/I_ModuleManager.cpp
  lib/I_StartupShutdownManager.cpp
  lib/I_ExtensionRegistry.cpp
  lib/ModuleInfo.cpp
  lib/ModuleManager.cpp
  lib/ModuleService.cpp
  lib/StartupShutdownManager.cpp
  lib/PluginInfo.cpp
)

set(HEADERS
  include/Zen/Plugin/I_ClassFactory.hpp
  include/Zen/Plugin/I_Configuration.hpp
  include/Zen/Plugin/I_Extension.hpp
  include/Zen/Plugin/I_ExtensionPoint.hpp
  include/Zen/Plugin/I_ExtensionQuery.hpp
  include/Zen/Plugin/I_ExtensionRegistry.hpp
  include/Zen/Plugin/I_PluginInfo.hpp
  include/Zen/Plugin/extension_point.hpp
)

add_definitions(-DZEN_PLUGIN_EXPORTS)
add_definitions(-DBOOST_TEST_DYN_LINK) 

add_library(zen-plugin ${SOURCES})

#TODO dl is only applicable on Linux
target_link_libraries(zen-plugin
    ${Boost_LIBRARIES} dl
)

enable_testing()

set(TEST_SOURCES
  test/simple.cpp
)

add_executable(zen-plugin-tests ${TEST_SOURCES})

target_link_libraries(zen-plugin-tests zen-plugin
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(tests zen-plugin-tests)

install(TARGETS zen-plugin DESTINATION /usr/local/lib)
install(DIRECTORY include DESTINATION /usr/local)
