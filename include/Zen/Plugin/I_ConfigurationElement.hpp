//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
// Copyright Raymond A. Richards 2001 - 2018
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_CONFIGURATION_ELEMENT_HPP_INCLUDED
#define ZEN_PLUGIN_I_CONFIGURATION_ELEMENT_HPP_INCLUDED

#include "Configuration.hpp"

#include <string>
#include <list>
#include <memory>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @note The methods that are commented are planned to be implemented but they're
///     not needed yet so I've not implemented them.
/// @todo Implement a way to get the value of an element.
class PLUGIN_DLL_LINK I_ConfigurationElement
:   boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef const I_ConfigurationElement&       const_ref_type;
    typedef const I_ConfigurationElement*       const_ptr_type;

    typedef std::list<const_ptr_type>           config_list_type;
    typedef std::shared_ptr<config_list_type>   config_list_ptr_type;

    // Defined below
    class I_ConfigurationElementVisitor;
    /// @}

    /// @name I_ConfigurationElement interface
    /// @{
public:
    /// Get an attribute by name.
    virtual const std::string& getAttribute(const std::string& _name) const = 0;

    /// Gets the names of all of the attributes of this configuration element.
    //virtual void getAttributeNames(I_AttributeVisitor& _visitor) = 0;

    /// Gets all of the children of this element.
    /// The lifetime of the data contained by the collection is the same
    /// as the lifetime of this I_ConfigurationElement.
    virtual config_list_ptr_type getChildren() const = 0;

    /// Gets all of the children of this element with the specified name.
    /// The lifetime of the data contained by the collection is the same
    /// as the lifetime of this I_ConfigurationElement.
    virtual config_list_ptr_type getChildren(const std::string& _name) const = 0;

    /// Gets all of the children of this element with the specified name
    /// using a visitor.
    virtual void getChildren(const std::string& _name, I_ConfigurationElementVisitor& _visitor) const = 0;

    /// Gets all of the children of this element using a visitor.
    virtual void getChildren(I_ConfigurationElementVisitor& _visitor) const = 0;

    /// Get a single child with the specified name.
    /// If more than one child with the specified name exists, the first one is returned.
    virtual const_ptr_type getChild(const std::string& _name) const = 0;

    /// Gets the name of this element.
    virtual const std::string& getName() const = 0;

    //virtual const std::string& getNamespaceIdentifier() = 0;

    /// Returns true if this configuration element object is valid.
    virtual bool isValid() const = 0;

    /// Get the parent element
    virtual const_ptr_type getParent() const = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ConfigurationElement() = default;
    virtual ~I_ConfigurationElement() = default;
    /// @}

    /// @name Inner Classes
    /// @{
public:
    class PLUGIN_DLL_LINK I_ConfigurationElementVisitor
    {
    public:
        virtual void begin() = 0;
        virtual void visit(const I_ConfigurationElement& _element) = 0;
        virtual void end() = 0;
    public:
                 I_ConfigurationElementVisitor() = default;
        virtual ~I_ConfigurationElementVisitor() = default;
    };  // interface I_ConfigurationElementVisitor
    
    // Not copyable nor assignable
    I_ConfigurationElement(const I_ConfigurationElement&) = delete;
    void operator=(const I_ConfigurationElement&) = delete;
    
};	// interface I_ConfigurationElement

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_CONFIGURATION_ELEMENT_HPP_INCLUDED
