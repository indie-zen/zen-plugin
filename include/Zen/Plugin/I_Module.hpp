//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <list>

#ifdef HOST_POSIX
#include <dlfcn.h>
#endif //HOST_POSIX

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

// Forward declarations
class I_Plugin;

/// Base class for a Zen Module
/// A plugin DLL should implement one of these
class PLUGIN_DLL_LINK I_Module
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef std::string                 plugin_name_type;
    typedef std::list<plugin_name_type> plugin_name_collection_type;
    typedef boost::shared_ptr<I_Plugin> plugin_ptr_type;

#ifdef HOST_WIN32
    typedef I_Module& (*proc_ptr_type)();
#elif HOST_POSIX
    typedef I_Module& (*QUERY_MODULE_FUNCTION_PTR)();
#else
#error Unsupported platform in I_Module.hpp
#endif
    /// @}

    /// @name I_Module interface
    /// @{
public:
    /// Returns the names of the plugins implemented by this module.
    virtual plugin_name_collection_type& getPluginNames() = 0;

    /// Returns a plugin by name.
    /// For now, plugins are all considered singletons.   The plugin should
    /// normally not be created until getPlugin is called, in case the plugin
    /// isn't required.
    /// @return - Returns the plugin if the name is a valid plugin name for this
    ///         module, otherwise NULL is returned.
    virtual plugin_ptr_type getPlugin(const plugin_name_type& _PluginName) = 0;

    /// Destroys the plugin.
    /// The framework will call this when it is finished with the plugin.
    virtual void destroyPlugin(plugin_ptr_type _Plugin) = 0;
    
    typedef void(*plugin_visitor_type)(const std::string&, plugin_ptr_type); 
    /// Visit the plugins in this module
    /// @since 2.0
    virtual void visitPlugins(plugin_visitor_type _visitor) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Module() = default;
    virtual ~I_Module() = default;
    /// @}

};  // interface I_Module

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen
}   // namespace Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_HPP_INCLUDED
