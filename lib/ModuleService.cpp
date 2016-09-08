//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "ModuleService.hpp"
#include "ModuleInfo.hpp"

#include <Zen/Plugin/I_Module.hpp>
#include <Zen/Plugin/I_ModuleInfo.hpp>
#include <Zen/Plugin/I_ModuleManager.hpp>
#include <Zen/Plugin/I_PluginManager.hpp>
#include <Zen/Plugin/I_Application.hpp>

// #include <Zen/Core/Utility/GetLastError.hpp>
// #include <Zen/Core/Utility/log_stream.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <iostream>
#include <sstream>

#include <stddef.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

ModuleService::ModuleService()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ModuleService::~ModuleService()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ModuleService::module_ptr_type
ModuleService::load(const std::string& _moduleName)
{
    // Get the logger stream
    // TODO Implement logging
    // Zen::Utility::log_stream& logStream(
    //     I_PluginManager::getSingleton().getApplication()->getLogStream()
    // );

    // Guard this method
    std::lock_guard<std::mutex> guard(m_moduleGuard);

    // See if the module has already been loaded
    module_name_index_type::iterator iter = m_moduleIndex.find(_moduleName);
    if(iter != m_moduleIndex.end())
    {
        // Increment the reference count
        m_modules[iter->second]->incrementReferences();

        // Return the module
        return iter->second;
    }

    module_info_ptr_type pModuleInfo(new ModuleInfo);

    I_ModuleManager* pModuleManager = &I_ModuleManager::getSingleton();

    boost::filesystem::path modulePath;
    if(!pModuleManager->findPath(_moduleName, modulePath))
    {
        // logStream << "DEBUG: Module " << _moduleName << " not found in defined module search paths." << std::endl;

        // TODO: Throw an exception with the error
        return NULL;
    }

    pModuleInfo->setName(_moduleName);

#ifdef _WIN32
    I_ModuleInfo::module_handle_type hModule = LoadLibraryA(modulePath.string().c_str());
#else
    // logStream << "DEBUG: dlopen " << modulePath.string().c_str() << std::endl;
    I_ModuleInfo::module_handle_type hModule = dlopen(modulePath.string().c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif // _WIN32

    if (hModule == NULL)
    {
        // TODO Implement
        // int err = Zen::Utility::GetLastError();
        int err = 0;

        // logStream << "DEBUG: Error loading module " << modulePath.string()
// #ifndef _WIN32
//         << dlerror()
// #else
//             << (err == 14001 ? "probably the module has dependencies not on the path.  Use depends.exe to figure it out." : "")
// #endif
//             << std::endl;


        // TODO: Throw an exception with the error
        return NULL;
#if 0
        std::stringstream errorStream;
        // errorStream << "Unable to find plugin module: " << moduleName.str();
        pPluginInfo->setError(errorStream.str());
#endif
    }

    pModuleInfo->setHandle(hModule);

    // Get the "getModule" procedure
#if   defined _WIN32
    FARPROC proc = GetProcAddress(hModule, "getModule");
#else
    void* proc = dlsym(hModule, "getModule");
#endif

    // Check to make sure the procedure exists
    if (proc)
    {
        // Convert the procedure type to the assumed type
#ifdef _WIN32
        I_Module::proc_ptr_type pRealProc = (I_Module::proc_ptr_type)proc;
#else
        I_Module::QUERY_MODULE_FUNCTION_PTR pRealProc = reinterpret_cast<I_Module::QUERY_MODULE_FUNCTION_PTR>(proc);
#endif

        // Execute the procedure to get the I_Module for this module.
        module_ptr_type pModule = &(pRealProc());

        // Set the reference count to 1
        pModuleInfo->incrementReferences();

        // Put it in the index
        m_moduleIndex[_moduleName] = pModule;

        // Put it in the cache
        m_modules[pModule] = pModuleInfo;

        // And return it.
        return pModule;
    }
    else
    {
        // logStream << "DEBUG: Error getting procedure address in module " << modulePath.string() << " Error " << Zen::Utility::GetLastError() << std::endl;

        // Not found, so return NULL
        return NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ModuleService::unload(module_ptr_type _pModule)
{
    // TODO Implement logging
    // Get the logger stream
    // Zen::Utility::log_stream& logStream(
    //     I_PluginManager::getSingleton().getApplication()->getLogStream()
    // );

    // Guard this method
    std::lock_guard<std::mutex> guard(m_moduleGuard);

    // Use _pModule to get the module info
    module_info_ptr_type pModuleInfo = m_modules[_pModule];

    // Decrement the reference
    // If the count is zero, get the handle and unload the library
    if( pModuleInfo->decrementReferences() == 0 )
    {
        std::string moduleName = pModuleInfo->getName();

        // Remove module from the index
        module_name_index_iterator_type moduleIndexIterator = m_moduleIndex.find(moduleName);
        m_moduleIndex.erase(moduleIndexIterator);

        // Physically unload module
        I_ModuleInfo::module_handle_type hModule = pModuleInfo->getHandle();

#ifdef _WIN32
        if( !FreeLibrary(hModule) )
#else
        if( dlclose(hModule) )
#endif // _WIN32
        {
            // logStream << "DEBUG: Error unloading module " << moduleName << " Error " << Zen::Utility::GetLastError() << std::endl;

            // TODO Throw an exception with the error
            return;
        }

        // Remove module from the cache
        modules_iterator_type moduleIterator = m_modules.find(_pModule);
        m_modules.erase(moduleIterator);

    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ModuleService::install(const std::string& _moduleName, I_Module& _module)
{
    // Guard this method
    std::lock_guard<std::mutex> guard(m_moduleGuard);

    // See if the module has already been loaded
    module_name_index_type::iterator iter = m_moduleIndex.find(_moduleName);
    if(iter != m_moduleIndex.end())
    {
        // Increment the reference count
        m_modules[iter->second]->incrementReferences();
        
        return;
    }

    module_info_ptr_type pModuleInfo(new ModuleInfo);

    I_ModuleManager* pModuleManager = &I_ModuleManager::getSingleton();

    pModuleInfo->setName(_moduleName);

    I_ModuleInfo::module_handle_type hModule = NULL;

    pModuleInfo->setHandle(hModule);

    // Set the reference count to 1
    pModuleInfo->incrementReferences();

    // Put it in the index
    m_moduleIndex[_moduleName] = &_module;

    // Put it in the cache
    m_modules[&_module] = pModuleInfo;

}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Plugins
}	// namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
