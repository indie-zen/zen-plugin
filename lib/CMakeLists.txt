set(SOURCES
  I_Configuration.cpp
  I_ConfigurationElement.cpp
  I_Extension.cpp
  I_ExtensionFactory.cpp
  I_ExtensionPoint.cpp
  I_ExtensionRegistry.cpp
  I_Plugin.cpp 
  I_PluginManager.cpp)

add_definitions(-DZEN_PLUGIN_EXPORTS)

add_library(zen_plugin ${SOURCES})
