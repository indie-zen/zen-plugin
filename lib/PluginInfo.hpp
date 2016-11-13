//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_PLUGIN_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_PLUGIN_INFO_HPP_INCLUDED

#include <Zen/Plugin/I_PluginInfo.hpp>

#include "XMLConfiguration.hpp"

#include "ExtensionPoint.hpp"
#include "Extension.hpp"

#include <boost/shared_ptr.hpp>

#include <string>
#include <map>
#include <list>
#include <utility>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
    namespace Threading {
        class I_Mutex;
    }
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_Plugin;
class Extension;

/// Plugin information
class PluginInfo
:   public I_PluginInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_PluginInfo implementation
    /// @{
public:
    virtual const std::string& getName() const;
    virtual const std::string& getDescription() const;
    virtual bool isLoaded() const;
    virtual const std::string& getLoadError() const;
    virtual void setWantsToLoad(bool _WantsToLoad);
    virtual bool getWantsToLoad() const;
    //virtual config_list_ptr_type getConfiguration(const std::string& _name) const;
    /// @}

    /// @name PluginInfo implementation
    /// @{
public:
    /// Set the configuration file.
    ///
    /// @note This should only be called by the PluginManager when the
    ///     plugin is being installed.
    bool parseConfigurationFile(const boost::filesystem::path& _configFile);

    void setLoaded(bool _isLoaded);
    void setError(const std::string& _ErrorMessage);

    /// Event listener for "plugin" elements (there should only be one)
    void onPluginElement(XMLConfigurationElement::ptr_type _pElement);

    /// Get the I_Plugin associated with this description
    boost::shared_ptr<I_Plugin> getPlugin();

    const std::list<boost::shared_ptr<ExtensionPoint> >& getExtensionPoints() const;
    const std::list<boost::shared_ptr<Extension> >& getExtensions() const;

    const std::list<std::string>& getRequiredPlugins() const;

#if 0 // deprecated
    void setModule(HMODULE _hModule);
#endif
    /// @}

    /// @name 'Structors
    /// @{
public:
             PluginInfo();
             PluginInfo(const std::string& _Name, const std::string& _Description);
    virtual ~PluginInfo();
    /// @}

    /// @name Member variables
    /// @{
private:
    std::string m_name;
    std::string m_description;
    std::string m_version;
    std::string m_provider;
    std::string m_moduleName;

    std::list<std::string>  m_requiredPlugins;

    bool        m_isLoaded; ///< @todo reference count?
    std::string m_error;
    bool        m_wantsToLoad;

#ifdef _WIN32
    // This was moved to ModuleInfo_win32
    //HMODULE     m_hModule;
#endif

    XMLConfiguration            m_config;
    //config_collection_type      m_config;

    /// Guard for the m_pRawPlugin assignemnt
    Threading::I_Mutex*         m_pGuard;
    volatile I_Plugin*          m_pRawPlugin;
    boost::shared_ptr<I_Plugin> m_plugin;

    std::list<boost::shared_ptr<ExtensionPoint> >   m_extensionPoints;

    std::list<boost::shared_ptr<Extension> >        m_extensions;

    /// @}
};  // class PluginInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_PLUGIN_INFO_HPP_INCLUDED
