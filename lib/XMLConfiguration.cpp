//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "XMLConfiguration.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

XMLConfiguration::XMLConfiguration()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
XMLConfiguration::~XMLConfiguration()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
XMLConfiguration::config_list_ptr_type
XMLConfiguration::getConfigurationElements()
{
    XMLConfiguration::config_list_ptr_type pList(new XMLConfiguration::config_list_ptr_type());

    config_collection_type::iterator iter;
    for(iter = m_config.begin(); iter != m_config.end(); ++iter)
    {
        pList->push_back(dynamic_cast<I_ConfigurationElement::const_ptr_type>(iter->second));
    }

    return pList;
}
#endif

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ConfigurationElement::const_ptr_type 
XMLConfiguration::getConfigurationElement(const std::string& _name) const
{
    config_collection_type::const_iterator iter = m_config.find(_name);

    if (iter != m_config.end() && strcmp(iter->first.c_str(), _name.c_str()) == 0)
    {
        return iter->second.get();
    }

    return NULL;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
XMLConfiguration::listenElement(const std::string& _name, element_event_type _function)
{
    m_elementEvents[_name] = _function;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
XMLConfiguration::parse(const boost::filesystem::path& _configFile)
{
    xmlDocPtr const pDoc = xmlParseFile(_configFile.string().c_str());

    // Check to see if the config file could be parsed.
    if (pDoc == NULL)
    {
        // TODO Thrown an exception or something?  
        return false;
    }

    xmlNodePtr pNode = xmlDocGetRootElement(pDoc);

    if (pNode == NULL)
    {
	    xmlFreeDoc(pDoc);
        return false;
    }

    // Loop through all of the nodes
    while(pNode != NULL)
    {
        // Create a configuration element out of this node
        config_element_ptr_type pElement(new XMLConfigurationElement(*this, NULL, pNode));

        m_config.insert(config_pair_type(pElement->getName(), pElement));

        // Call the callback function passing the new element
        //_function(pElement);

        // Dispatch event if necessary
        dispatchEvent(pElement);

        pNode = pNode->next;
    }

	xmlFreeDoc(pDoc);

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
XMLConfiguration::dispatchEvent(config_element_ptr_type _pElement)
{
    element_event_map_type::iterator iter = m_elementEvents.find(_pElement->getName());

    if (iter != m_elementEvents.end())
    {
        (iter->second)(_pElement);
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen
}   // namespace Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
