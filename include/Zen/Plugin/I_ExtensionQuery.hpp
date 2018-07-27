//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#ifndef ZEN_PLUGIN_I_EXTENSION_QUERY_HPP_INCLUDED
#define ZEN_PLUGIN_I_EXTENSION_QUERY_HPP_INCLUDED

#include "Configuration.hpp"

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @deprecated Instead of using this, use I_ExtensionRegistry::getExtensionPoints()
/// @see I_ExtensionRegistry::getExtensionPoints().
class I_ExtensionQuery
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ExtensionQuery interface
    /// @{
public:
    /// Set the namespace of the extension
    virtual void setNamespace(const std::string& _namespace) = 0;

    /// Set the extension point of the extension
    virtual void setExtensionPoint(const std::string& _extensionPoint) = 0;

    /// Set the type of the extension.
    /// This is a very general type and should be considered a
    /// quick and dirty hack.  This probably will not be supported
    /// in the future.
    virtual void setType(const std::string& _type) = 0;

    /// Get the string representation of this query
    virtual const std::string& toString() const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ExtensionQuery();
	virtual ~I_ExtensionQuery();
    /// @}

    // Not copyable nor assignable
    I_ExtensionQuery(const I_ExtensionQuery&) = delete;
    void operator=(const I_ExtensionQuery&) = delete;

};	// interface I_ExtensionQuery

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_EXTENSION_QUERY_HPP_INCLUDED
