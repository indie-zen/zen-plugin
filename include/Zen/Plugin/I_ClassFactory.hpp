//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_CLASS_FACTORY_HPP_INCLUDED
#define ZEN_PLUGIN_I_CLASS_FACTORY_HPP_INCLUDED

#include "Configuration.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Base class factory interface
class PLUGIN_DLL_LINK I_ClassFactory
{
	/// @name Types
	/// @{
public:
	/// @}

    /// @name I_ClassFactory interface
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ClassFactory() = default;
    virtual ~I_ClassFactory() = default;
    /// @}

    // Not copyable nor assignable
    I_ClassFactory(const I_ClassFactory&) = delete;
    void operator=(const I_ClassFactory&) = delete;

};	// interface I_ClassFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_CLASS_FACTORY_HPP_INCLUDED
