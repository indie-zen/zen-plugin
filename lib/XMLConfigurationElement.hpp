//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#ifndef ZEN_PLUGIN_XML_CONFIGURATION_ELEMENT_HPP_INCLUDED
#define ZEN_PLUGIN_XML_CONFIGURATION_ELEMENT_HPP_INCLUDED

#include <Zen/PluginI_ConfigurationElement.hpp>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>

#include <map>
#include <utility>

// <string> and <list> were already included from <I_ConfigurationElement.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class XMLConfiguration;

class XMLConfigurationElement
:   public I_ConfigurationElement
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<XMLConfigurationElement>              ptr_type;

    typedef std::multimap<std::string, std::string>                 property_collection_type;
    typedef std::pair<property_collection_type::key_type, 
                      property_collection_type::mapped_type>        property_pair_type;

    typedef std::multimap<std::string, ptr_type>                    children_collection_type;
    typedef std::pair<children_collection_type::key_type, 
                      children_collection_type::mapped_type>        children_pair_type;

    /// @}

    /// @name I_ConfigurationElement implementation
    /// @{
public:
    virtual const std::string& getAttribute(const std::string& _name) const;
    virtual config_list_ptr_type getChildren() const;
    virtual config_list_ptr_type getChildren(const std::string& _name) const;
    virtual void getChildren(const std::string& _name, I_ConfigurationElementVisitor& _visitor) const;
    virtual void getChildren(I_ConfigurationElementVisitor& _visitor) const;
    virtual const_ptr_type getChild(const std::string& _name) const;
    virtual const std::string& getName() const;
    virtual bool isValid() const;
    virtual const_ptr_type getParent() const;
    /// @}

    /// @name XMLConfigurationElement implementation
    /// @{
protected:
    void addChild(ptr_type _pChild);
    /// @}

    /// @name 'Structors
    /// @{
public:
             XMLConfigurationElement(XMLConfiguration& _topParent, XMLConfigurationElement* _pParent, xmlNodePtr const _pNode);
    virtual ~XMLConfigurationElement();
    /// @}

    /// @name Member Variables
    /// @{
private:
    XMLConfiguration&           m_topParent;
    XMLConfigurationElement*    m_pParent;
    bool                        m_isValid;
    std::string                 m_name;
    std::string                 m_value;
    property_collection_type    m_properties;
    children_collection_type    m_children;
    /// @}

};	// class XMLConfigurationElement

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_XML_CONFIGURATION_ELEMENT_HPP_INCLUDED
