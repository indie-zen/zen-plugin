//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Module;

class PLUGIN_DLL_LINK I_ModuleService
:   public boost::noncopyable
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
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleService();
    virtual ~I_ModuleService();
    /// @}

};  // interface I_ModuleService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Plugins
}	// namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_SERVICE_HPP_INCLUDED
