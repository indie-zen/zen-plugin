//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class PLUGIN_DLL_LINK I_ModuleInfo
:   public boost::noncopyable
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
             I_ModuleInfo();
    virtual ~I_ModuleInfo();
    /// @}

};  // interface I_ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_MODULE_INFO_HPP_INCLUDED
