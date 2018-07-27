//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_MODULE_MANAGER_HPP_INCLUDED
#define ZEN_PLUGIN_MODULE_MANAGER_HPP_INCLUDED

#include <Zen/Plugin/I_ModuleManager.hpp>


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleManager
:   public I_ModuleManager
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_ModuleService>                  module_service_ptr_type;
    typedef std::list</*const*/ boost::filesystem::path>            module_paths_type;
    typedef std::list</*const*/ boost::filesystem::path>::iterator  module_paths_iterator_type;
    /// @}

    /// @name I_ModuleManager implementation
    /// @{
public:
    virtual service_ptr_type getService(MODULE_SERVICE_TYPE _serviceType);
    virtual void addPath(const boost::filesystem::path& _modulePath);
    virtual void dropPath(const boost::filesystem::path& _modulePath);
    virtual bool findPath(const std::string _moduleName, boost::filesystem::path &_modulePath);
    /// @}

    /// @name ModuleManager implementation
    /// @{
public:
    static ModuleManager& getSingleton() { return *(dynamic_cast<ModuleManager*>(&I_ModuleManager::getSingleton())); }
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleManager();
    virtual ~ModuleManager();
    /// @}

    /// @name Member variables
    /// @{
private:

    /// Module service
    module_service_ptr_type     m_pModuleService;

    /// Module search paths
    module_paths_type           m_modulePaths;
    /// @}

};  // interface ModuleManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_MODULE_MANAGER_HPP_INCLUDED
