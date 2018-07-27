//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED

#include "Configuration.hpp"

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class PLUGIN_DLL_LINK I_ModuleInfo
{
    /// @name Types
    /// @{
public:
#if defined _WIN32
    typedef HMODULE     module_handle_type;
#else
    typedef void*       module_handle_type;
#endif // _WIN32
    /// @}

    /// @name I_ModuleInfo interface
    /// @{
public:
    virtual void setName(const std::string _name) = 0;
    virtual std::string getName() const = 0;

    virtual void setHandle(const module_handle_type _handle) = 0;
    virtual module_handle_type getHandle() const = 0;

    virtual unsigned incrementReferences() = 0;
    virtual unsigned decrementReferences() = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleInfo() = default;
    virtual ~I_ModuleInfo() = default;
    /// @}

    // Not copyable nor assignable
    I_ModuleInfo(const I_ModuleInfo&) = delete;
    void operator=(const I_ModuleInfo&) = delete;

};  // interface I_ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED
