//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_SERVICE_INFO_HPP_INCLUDED
#define ZEN_PLUGIN_I_SERVICE_INFO_HPP_INCLUDED

#include "Configuration.hpp"

#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Service information
class PLUGIN_DLL_LINK I_ServiceInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ServiceInfo interface
    /// @{ 
public:
    /// @return the name of the service
    virtual const std::string& getName() const = 0;
    /// @}

    /// @{ 'Structors
protected:
             I_ServiceInfo();
    virtual ~I_ServiceInfo();
    /// @}

    // Not copyable nor assignable
    I_ServiceInfo(const I_ServiceInfo&) = delete;
    void operator=(const I_ServiceInfo&) = delete;

};  // interface I_ServiceInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_SERVICE_INFO_HPP_INCLUDED

