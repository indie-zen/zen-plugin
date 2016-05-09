cmake_minimum_required (VERSION 3.5)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Using experimental C++ features, including c++14 and c++17.
set(CMAKE_CXX_FLAGS "-std=c++1z -Wc++11-extensions")

project(zenplugin)

# Don't build in this directory
# mkdir ../zen-plugin-build
# cd ../zen-plugin-build
# cmake ../zen-plugin
# make
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CLDOC "" CACHE STRING "User specified '/path/to/cldoc'")
if(CLDOC STREQUAL "")
	find_program(CLDOC cldoc)
elseif(NOT EXISTS ${CLDOC})
	message(FATAL_ERROR "CLDOC was set to '${CLDOC}' but does not exist")
endif()

if(NOT DOCS_OUTPUT_DIR)
	set(DOCS_OUTPUT_DIR "gendocs" CACHE STRING "Generated documentation output directory" FORCE)
endif()

if(NOT DOCS_DIR)
	set(DOCS_DIR "" CACHE STRING "Location of external documentation files to be merged in" FORCE)
endif()

set(SOURCES
  lib/I_Configuration.cpp
  lib/I_ConfigurationElement.cpp
  lib/I_Extension.cpp
  lib/I_ExtensionFactory.cpp
  lib/I_ExtensionPoint.cpp
  lib/I_ExtensionRegistry.cpp
  lib/I_Plugin.cpp
  lib/I_PluginManager.cpp)

set(HEADERS
  include/Zen/Plugin/I_Configuration.hpp
)

add_definitions(-DZEN_PLUGIN_EXPORTS)

add_library(zen_plugin ${SOURCES})

if(NOT ${CLDOC} STREQUAL "CLDOC-NOTFOUND")
  if(NOT ${DOCS_DIR} STREQUAL "")
  	set(CLDOC_MERGE "--merge ${DOCS_DIR}")
  else()
  	set(CLDOC_MERGE "")
  endif()

  add_custom_target(docs COMMAND
    ${CLDOC} generate
    "-std=c++11"
    -I${PROJECT_SOURCE_DIR}/include
    --
    ${CLDOC_MERGE}
    --output ../${DOCS_OUTPUT_DIR}
    ${HEADERS}
    ${SOURCES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_target_properties(docs PROPERTIES
    EXCLUDE_FROM_ALL false
    EXCLUDE_FROM_DEFAULT_BUILD false
  )

else()
  message(STATUS
    "Documentation will not be generated"
  )
endif()
