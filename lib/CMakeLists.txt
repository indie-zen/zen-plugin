set(SOURCES
  I_ModuleManager.cpp)

add_definitions(-DZEN_PLUGIN_EXPORTS)

add_library(zen_plugin ${SOURCES})
