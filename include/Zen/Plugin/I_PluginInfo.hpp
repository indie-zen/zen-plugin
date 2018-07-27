//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_PLUGIN_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_I_PLUGIN_INFO_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Plugin/I_Configuration.hpp>
#include <Zen/Plugin/I_ConfigurationElement.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Plugin Description
/// @todo Change name to I_PluginDescription
class PLUGIN_DLL_LINK I_PluginInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_PluginInfo interface
    /// @{
public:
    /// @return the name of the plugin
    virtual const std::string& getName() const = 0;

    /// @return The description of the plugin
    virtual const std::string& getDescription() const = 0;

    /// @return true if the plugin is loaded
    virtual bool isLoaded() const = 0;

    /// @return an error message if I_PluginManager::loadPlugin()
    ///         encounters an error while attempting to load the
    ///         plugin.  If no error was encountered, an empty
    ///         string is returned.
    virtual const std::string& getLoadError() const = 0;

    /// Set to true if the user wants to load this plugin
    virtual void setWantsToLoad(bool _WantsToLoad) = 0;

    /// True if the user wants to load this plugin.
    /// @see isLoaded() to check if the plugin is already
    ///     loaded or not.
    virtual bool getWantsToLoad() const = 0;

    /// Get the configuration related to this plugin info.
    /// @todo Should this be public?
    //virtual I_Configuration::const_config_ref_type getConfiguration(const std::string& _name) const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_PluginInfo();
    virtual ~I_PluginInfo();
    /// @}

    // Not copyable nor assignable
    I_PluginInfo(const I_PluginInfo&) = delete;
    void operator=(const I_PluginInfo&) = delete;

};  // interface I_PluginInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_PLUGIN_INFO_HPP_INCLUDED
