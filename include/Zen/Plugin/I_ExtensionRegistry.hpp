//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_EXTENSION_REGISTRY_HPP_INCLUDED
#define ZEN_PLUGIN_I_EXTENSION_REGISTRY_HPP_INCLUDED

#include "Configuration.hpp"

#include <memory>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_ClassFactory;
class I_Extension;
class I_ExtensionPoint;
class I_ExtensionQuery;

class PLUGIN_DLL_LINK I_ExtensionRegistry
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_Extension>                  pExtension_type;
    typedef std::shared_ptr<I_ExtensionPoint>             pExtensionPoint_type;
    typedef std::shared_ptr<I_ExtensionQuery>             pExtensionQuery_type;
    typedef I_ClassFactory&                               ClassFactory_ref_type;

    /// Visitor inteface for traversing extension  points.  
    /// Defined below as an inner class.
    class I_ExtensionPointVisitor;
    /// @}

    /// @name I_ExtensionRegistry interface
    /// @{
public:
    /// Construct an empty query
    virtual pExtensionQuery_type createQuery() = 0;

    typedef void (*ExtensionVisitor_type)(pExtension_type);
    typedef bool (*ExtensionFilter_type)(pExtension_type);

    /// Get all of the extensions using a visitor
    virtual void getExtensions(pExtensionQuery_type _pQuery, ExtensionVisitor_type _visitor) = 0;

    /// Find an extension using a filter
    virtual pExtension_type findExtension(pExtensionQuery_type _pQuery, ExtensionFilter_type _visitor) = 0;

    /// Get the class factory for an extension
    /// @throw Utility::runtime_exception if the class factory is not found.
    virtual ClassFactory_ref_type getClassFactory(pExtension_type _pExtension) = 0;
    /// @}
    
    /// @name Singleton instance
    /// @{
public:
    static I_ExtensionRegistry& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{

protected:
             I_ExtensionRegistry() = default;
    virtual ~I_ExtensionRegistry() = default;
    /// @}

    // Non copyable
    I_ExtensionRegistry(const I_ExtensionRegistry&) = delete;
    // Non assignable
    I_ExtensionRegistry& operator=(const I_ExtensionRegistry&) = delete;

};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_EXTENSION_REGISTRY_HPP_INCLUDED
