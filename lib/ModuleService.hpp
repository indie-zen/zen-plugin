//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_MODULE_SERVICE_HPP_INCLUDED
#define ZEN_PLUGIN_MODULE_SERVICE_HPP_INCLUDED

#include <Zen/Plugin/I_ModuleInfo.hpp>
#include <Zen/Plugin/I_ModuleService.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>

#include <map>
#include <mutex>
#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleService
:   public I_ModuleService
{
    /// @name Types
    /// @{
public:
    typedef std::map<std::string, module_ptr_type>                      module_name_index_type;
    typedef std::map<std::string, module_ptr_type>::iterator            module_name_index_iterator_type;
    typedef boost::shared_ptr<I_ModuleInfo>                             module_info_ptr_type;
    typedef std::map<module_ptr_type, module_info_ptr_type>             modules_type;
    typedef std::map<module_ptr_type, module_info_ptr_type>::iterator   modules_iterator_type;
    /// @}

    /// @name I_ModuleService implementation
    /// @{
public:
    virtual module_ptr_type load(const std::string& _moduleName);
    virtual void unload(module_ptr_type _pModule);
    virtual void install(const std::string& _moduleName, I_Module& _module);
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleService();
    virtual ~ModuleService();
    /// @}

    /// @name Member variables
    /// @{
private:
    module_name_index_type      m_moduleIndex;
    modules_type                m_modules;
    std::mutex                  m_moduleGuard;
    /// @}

};  // interface ModuleService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Plugins
}	// namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_MODULE_SERVICE_HPP_INCLUDED
