//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_PLUGIN_MANAGER_HPP_INCLUDED
#define ZEN_PLUGIN_I_PLUGIN_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>

#include <experimental/filesystem>

#include <string>
#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Application;
class I_Module;
class I_Plugin;
class I_PluginDescription;

class PLUGIN_DLL_LINK I_PluginManager
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_Application>       app_ptr_type;
    typedef std::shared_ptr<I_Plugin>            plugin_ptr_type;
    typedef std::shared_ptr<I_PluginDescription> plugin_desc_ptr_type;
    typedef std::list<plugin_desc_ptr_type>      plugin_desc_list_type;
    /// @}

    /// @name I_PluginManager interface
    /// @{
public:
    /// Install an application
    virtual app_ptr_type installApplication(const std::experimental::filesystem::path& _configFile, const std::experimental::filesystem::path& _logFile = std::experimental::filesystem::path("Zen.log")) = 0;

    /// Get the installed application
    /// If an application is not installed, a NULL smart pointer
    /// is returned.
    virtual app_ptr_type getApplication() = 0;

    /// Set the root path of this application and the special character that is used
    /// to identify when the path should be used.
    /// For instance, if _ch is '~' and a path passed to setPluginPath or setModulePath
    /// begins with '~' (i.e. ~/../Zen/plugins) then ~ will be replaced with _rootPath.
    /// If _rootPath is "C:/dev/MyGame" then the final path will be "C:/dev/Zen/plugins".
    virtual void setRootPath(const char _ch, const std::experimental::filesystem::path& _rootPath) = 0;

    /// Adds a path to the plugin search path where the plugins are located.
    ///
    /// The <plugin-path path="xxx"/> entry in the application configuration file is added
    /// to the plugin search path.  Because of that it's possible that this doesn't need to
    ///  be exposed on the public interface.
    ///
    /// @todo Should this be more like "addPluginPath" to add a new directory
    ///         to the plugin search path?
    virtual void setPluginPath(const std::experimental::filesystem::path& _pluginPath) = 0;

    /// Set the path where the plugin binaries are located.  By
    /// default this is the plugin path plus /release or /debug
    /// depending on if the framework was compiled with -DRELEASE
    /// or -DDEBUG
    ///
    /// The <module-path path="xxx"/> entry in the application configuration file is added
    /// to the module search path.  Because of that it's possible that this doesn't need to
    ///  be exposed on the public interface.
    ///
    virtual void setModulePath(const std::experimental::filesystem::path& _modulePath) = 0;

    /// Install a named plugin.  The plugin.xml definition is found at
    /// the plugin path plus module name plus plugin.xml.
    /// Other plugins required by the specified plugin will be automatically
    /// installed as well.
    virtual plugin_desc_ptr_type installPlugin(const std::string& _pluginName) = 0;

    /// Enumerate all of the plugins
    /// @return non-const list of plugins
    virtual const plugin_desc_list_type& enumeratePlugins() const = 0;

    /// Load a plugin
    /// Plugins can only be loaded once.  If the plugin has already
    /// been loaded then the reference count is increased but the
    /// plugin is not re-loaded.
    /// Other plugins required by the specified plugin will automatically
    /// be loaded first.
    ///
    /// @return a pointer to the plugin object.  Returns NULL if
    ///         the plugin cannot be loaded for some reason.  If
    ///         an error occurs while loading, _pPluginInfo will
    ///         contain an error.
    //virtual plugin_ptr_type loadPlugin(plugin_desc_ptr_type _pPluginInfo) = 0;

	/// Gets a previously loaded plugin
	/// @return a pointer to the plugin object.  Returns NULL if
	///			the plugin wasn't found or isn't loaded.
	//virtual plugin_ptr_type getPlugin(plugin_info_ptr_type _pPluginInfo) = 0;
    /// @}

    /// @name Static Instance
    /// @{
public:
    static I_PluginManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_PluginManager();
    virtual ~I_PluginManager();
    /// @}

};	// interface I_PluginManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_PLUGIN_MANAGER_HPP_INCLUDED
