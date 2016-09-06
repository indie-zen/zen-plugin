//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_APPLICATION_HPP_INCLUDED
#define ZEN_PLUGIN_I_APPLICATION_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Utility/log_stream.hpp>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_Configuration;

/// @author Tony Richards
/// @since 1.0
class PLUGIN_DLL_LINK I_Application
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_Application>                ptr_type;
    //typedef I_ConfigurationElement::config_list_type        config_list_type;
    //typedef I_ConfigurationElement::config_list_ptr_type    config_list_ptr_type;
    /// @}

    /// @name I_Application interface
    /// @{
public:
    /// Get the configuration elements that match the specified name.
    virtual const I_Configuration& getConfiguration() const = 0;

    virtual const std::string& getId() const = 0;
    virtual const std::string& getName() const = 0;
    virtual const std::string& getVersion() const = 0;
    virtual const std::string& getProviderName() const = 0;
    virtual Utility::log_stream& getLogStream() = 0;
    /// @}

    /// @{ 'Structors
protected:
             I_Application();
    virtual ~I_Application();
    /// @}

};  // interface I_Application

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_APPLICATION_HPP_INCLUDED

