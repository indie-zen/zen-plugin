//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_MANAGER_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/filesystem/path.hpp>

#include <list>
#include <memory>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_ModuleService;

class PLUGIN_DLL_LINK I_ModuleManager
{
    /// @name Types
    /// @{
public:
    typedef I_ModuleService*        service_ptr_type;

    /// Eventually other service types will be supported such as
    /// static, downloadable, remote, etc.
    enum MODULE_SERVICE_TYPE
    {
        DYNAMIC,
        STATIC
    };
    /// @}

    /// @name I_ModuleManager interface
    /// @{
public:
    /// Load a module service
    virtual service_ptr_type getService(MODULE_SERVICE_TYPE _serviceType) = 0;

    /// Add a module search path
    virtual void addPath(const boost::filesystem::path& _modulePath) = 0;

    // Drop a module search path
    virtual void dropPath(const boost::filesystem::path& _modulePath) = 0;

    // Find module path if one exists
    virtual bool findPath(const std::string _moduleName, boost::filesystem::path &_modulePath) = 0;
    /// @}

    /// @name Static Instance
    /// @{
public:
    static I_ModuleManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleManager() = default;
    virtual ~I_ModuleManager() = default;
    /// @}

    // Not copyable nor assignable
    I_ModuleManager(const I_ModuleManager&) = delete;
    void operator=(const I_ModuleManager&) = delete;

};  // interface I_ModuleManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Plugins
}	// namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_MANAGER_HPP_INCLUDED

