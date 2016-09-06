//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_SERVICE_CACHE_HPP_INCLUDED
#define ZEN_PLUGIN_SERVICE_CACHE_HPP_INCLUDED

#include <Zen/Plugin/I_Configuration.hpp>
#include <Zen/Plugin/I_ConfigurationElement.hpp>
#include <Zen/Plugin/I_ExtensionQuery.hpp>
#include <Zen/Plugin/I_ExtensionRegistry.hpp>
#include <Zen/Plugin/I_StartupShutdownManager.hpp>
#include <Zen/Plugin/I_StartupShutdownParticipant.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <map>
#include <memory>

#include <stddef.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @brief Service Cache
///
/// Service manager that assumes there is only once service for each index_type.
/// If a service fits this assumption, use this template to provide caching and
/// memory management services.
template<typename Service_type, typename Factory_type = typename Service_type::factory_type>
class ServiceCache
{
    /// @name Types
    /// @{
public:
    typedef typename Service_type::index_type           index_type;
    typedef std::shared_ptr<Service_type>               pService_type;
    typedef std::weak_ptr<Service_type>                 wpService_type;
    typedef Event::Connection<wpService_type>*          pConnection_type;
    typedef std::map<wpService_type, pConnection_type>  connections_type;
    typedef std::map<index_type, pService_type>         services_type;
    typedef std::map<wpService_type, index_type>        service_ptr_index_type;
    typedef typename services_type::iterator            iterator;
    /// @}

    /// @name Manager implementation
    /// @{
public:
    /// Get the service index by index_type.
    /// @return the service on a cache hit, otherwise NULL
    pService_type getCachedService(index_type _type);

    /// Get the factory based on index_type
    Factory_type* getFactory(index_type _type);

    /// Cache the service for later use.  The lifetime of the cached service will
    /// expire after the last reference goes out of scope.  This template only
    /// retains a weak pointer to the service to prevent a dangling reference.
    pService_type cacheService(index_type, pService_type _pService, const std::string& _instanceName = "default");

    /// Get resource guard
    std::mutex getGuard() const;

    iterator begin();
    iterator end();

private:
    /// This method is called when the service is destroyed.
    void onDestroy(wpService_type _pService);
    void installParticipant(pService_type _pService, const std::string& _instanceName, const boost::true_type&);
    void installParticipant(pService_type _pService, const std::string& _instanceName, const boost::false_type&);
    /// @}

    /// @name 'Structors
    /// @{
public:
             ServiceCache();
    virtual ~ServiceCache();
    /// @}

    /// @name Member Variables
    /// @{
private:
    Threading::I_Mutex*     m_pMutex;
    services_type           m_services;
    service_ptr_index_type  m_serviceIndex;
    connections_type        m_connections;
    /// @}

};  // template class ServiceCache

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
ServiceCache<Service_type, Factory_type>::ServiceCache()
{
    m_pMutex = Threading::MutexFactory::create();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
ServiceCache<Service_type, Factory_type>::~ServiceCache()
{
    // Loop through all of the connections and disconnect them
    {
        Threading::CriticalSection guard(m_pMutex);

        for(typename ServiceCache<Service_type, Factory_type>::connections_type::iterator iter = m_connections.begin(); iter != m_connections.end(); iter++)
        {
            iter->second->disconnect();
        }
    }

    Threading::MutexFactory::destroy(m_pMutex);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
typename ServiceCache<Service_type, Factory_type>::pService_type
ServiceCache<Service_type, Factory_type>::getCachedService(index_type _type)
{
    // Look for the cached service
    typename ServiceCache<Service_type, Factory_type>::services_type::iterator iter = m_services.find(_type);

    // If found, return it.
    if (iter != m_services.end())
    {
        return iter->second;
    }

    // If not found, return NULL
    return pService_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
Factory_type*
ServiceCache<Service_type, Factory_type>::getFactory(index_type _type)
{
    // Create an extension query
    const I_ExtensionRegistry::pExtensionQuery_type pQuery = I_ExtensionRegistry::getSingleton().createQuery();

    pQuery->setNamespace(Service_type::getNamespace());
    pQuery->setExtensionPoint(Service_type::getExtensionPointName());
    pQuery->setType(_type);


    // Get the extensions
    // Note that the result set takes ownership of pQuery
    I_ExtensionRegistry::extension_result_set_ptr_type pExtensions = I_ExtensionRegistry::getSingleton().findExtensions(pQuery);

    // Grab the first extension; if there are more installed then eventually we can
    // deal with that but for now just grab one.
    I_ExtensionRegistry::extension_result_set_type::iterator pExtensionIter = pExtensions->begin();

    if (pExtensionIter != pExtensions->end())
    {
        Plugins::I_ExtensionRegistry::class_factory_ref_type 
            classFactory(Plugins::I_ExtensionRegistry::getSingleton().getClassFactory(*pExtensionIter));

        return dynamic_cast<Factory_type*>(&classFactory);
    }
    else
    {
        return NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
void
ServiceCache<Service_type, Factory_type>::installParticipant(pService_type _pService, const std::string& _instanceName, const boost::true_type&)
{
#ifdef _WIN32   // HACK: Can't get this to compile correctly on GCC :-(
    typename I_StartupShutdownManager::pParticipant_type pParticipant(_pService.as< typename I_StartupShutdownManager::pParticipant_type >());
    I_StartupShutdownManager::getInstance(_instanceName).installParticipant(pParticipant);
#endif 
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
void
ServiceCache<Service_type, Factory_type>::installParticipant(pService_type _pService, const std::string& _instanceName, const boost::false_type&)
{
    // Nothing to do
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
typename ServiceCache<Service_type, Factory_type>::pService_type
ServiceCache<Service_type, Factory_type>::cacheService(index_type _type, pService_type _pService, const std::string& _instanceName)
{
    pConnection_type pConnection = _pService->onDestroyEvent.connect(boost::bind(&ServiceCache<Service_type, Factory_type>::onDestroy, this, _1));

    installParticipant(_pService, _instanceName, boost::is_base_of<I_StartupShutdownParticipant,Service_type>());

    // Save the connection so it can be disconnected later
    m_connections[_pService.getWeak()] = pConnection;

    m_services[_type] = _pService;
    m_serviceIndex[_pService.getWeak()] = _type;

    return _pService;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
Threading::I_Mutex*
ServiceCache<Service_type, Factory_type>::getLock() const
{
    return m_pMutex;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
void
ServiceCache<Service_type, Factory_type>::onDestroy(wpService_type _pService)
{
    Threading::CriticalSection guard(m_pMutex);

    typename ServiceCache<Service_type, Factory_type>::service_ptr_index_type::iterator index = m_serviceIndex.find(_pService);

    if (index != m_serviceIndex.end())
    {
        typename ServiceCache::services_type::iterator service = m_services.find(index->second);

        if (service != m_services.end())
        {
            m_serviceIndex.erase(index);
            m_services.erase(service);
            
            m_connections[_pService]->disconnect();
            m_connections.erase(_pService);
        }
        else
        {
            // TODO Error
        }
    }
    else
    {
        // TODO Error
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
typename ServiceCache<Service_type, Factory_type>::iterator
ServiceCache<Service_type, Factory_type>::begin()
{
    return m_services.begin();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename Service_type, typename Factory_type>
inline
typename ServiceCache<Service_type, Factory_type>::iterator
ServiceCache<Service_type, Factory_type>::end()
{
    return m_services.end();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_SERVICE_CACHE_HPP_INCLUDED
