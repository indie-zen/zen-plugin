//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_MODULE_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_MODULE_INFO_HPP_INCLUDED

#include <Zen/Plugin/I_ModuleInfo.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleInfo
:   public I_ModuleInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ModuleInfo implementation
public:
    virtual void setName(const std::string _name);
    virtual std::string getName() const;

    virtual void setHandle(const module_handle_type _handle);
    virtual module_handle_type getHandle() const;

    virtual unsigned incrementReferences();
    virtual unsigned decrementReferences();
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleInfo();
    virtual ~ModuleInfo();
    /// @}

    /// @name Member variables
    /// @{

    // Module name
    std::string         m_name;

    // Module handle
    module_handle_type  m_hModule;

    // Module reference count
    unsigned            m_references;
    /// @}

};  // interface ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_MODULE_INFO_HPP_INCLUDED
