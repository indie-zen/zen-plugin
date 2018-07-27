//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/filesystem/path.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Module;

class PLUGIN_DLL_LINK I_ModuleService
{
    /// @name Types
    /// @{
public:
    /// This is a raw pointer because the lifetime
    /// is handled by load / unload pairs.
    typedef I_Module*                   module_ptr_type;
    /// @}

    /// @name I_ModuleService interface
    /// @{
public:
    /// Load a module.
    virtual module_ptr_type load(const std::string& _moduleName) = 0;

    /// Unload a module.
    virtual void unload(module_ptr_type _module) = 0;
    
    /// Install a static module
    virtual void install(const std::string& _moduleName, I_Module& _module) = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleService() = default;
    virtual ~I_ModuleService() = default;
    /// @}

    // Not copyable nor assignable
    I_ModuleService(const I_ModuleService&) = delete;
    void operator=(const I_ModuleService&) = delete;

};  // interface I_ModuleService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED
