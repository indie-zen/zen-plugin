//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_EXTENSION_CACHE_HPP_INCLUDED
#define ZEN_PLUGIN_EXTENSION_CACHE_HPP_INCLUDED

#include <Zen/Plugin/I_Configuration.hpp>
#include <Zen/Plugin/I_ConfigurationElement.hpp>
#include <Zen/Plugin/I_ExtensionPoint.hpp>
#include <Zen/Plugin/I_ExtensionQuery.hpp>
#include <Zen/Plugin/I_ExtensionRegistry.hpp>

#include <type_traits>
#include <map>
#include <memory>
#include <mutex>

#include <stddef.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @brief Extension Cache
///
/// Extension manager that assumes there is only once extension for each index_type.
/// If a extension fits this assumption, use this template to provide caching and
/// memory management capabilities.
template<typename ExtensionPoint_type>
class ExtensionCache
{
    /// @name Types
    /// @{
public:
    typedef typename ExtensionPoint_type::Extension_type    Extension_type;
    typedef typename ExtensionPoint_type::Factory_type      Factory_type;
    typedef typename Extension_type::index_type           index_type;
    typedef std::shared_ptr<Extension_type>               pExtension_type;
    typedef std::weak_ptr<Extension_type>                 wpExtension_type;
    // typedef Event::Connection<wpExtension_type>*          pConnection_type;
    // typedef std::map<wpExtension_type, pConnection_type>  connections_type;
    typedef std::map<index_type, pExtension_type>         extensions_type;
    typedef std::map<wpExtension_type, index_type>        extension_ptr_index_type;
    typedef typename extensions_type::iterator            iterator;
    /// @}

    /// @name Manager implementation
    /// @{
public:
    /// Get the extension index by index_type
    /// @return the extension; if the extension has not yet been created then create it and cache
    ///         it, otherwise return the cached extension.
    pExtension_type getExtension(index_type _type);

private:
    /// Get the factory based on index_type
    Factory_type* getFactory(index_type _type);

    /// Get the extension index by index_type.
    /// @deprecated
    /// @return the extension on a cache hit, otherwise NULL
    pExtension_type getCachedExtension(index_type _type);


    /// Cache the extension for later use.  The lifetime of the cached extension will
    /// expire after the last reference goes out of scope.  This template only
    /// retains a weak pointer to the extension to prevent a dangling reference.
    /// @deprecated
    pExtension_type cacheExtension(index_type, pExtension_type _pExtension, const std::string& _instanceName = "default");

    // This is a bad pattern; instead of requring a guard around begin/end then
    // some other iterator pattern (visitor?) should be used.

    /// Get resource guard
    /// @deprecated
    // std::mutex& getGuard() const;

    /// @deprecated
    // iterator begin();

    /// @deprecated
    // iterator end();

private:
    /// This method is called when the extension is destroyed.
    void onDestroy(wpExtension_type _pExtension);
    void installParticipant(pExtension_type _pExtension, const std::string& _instanceName, const std::true_type&);
    void installParticipant(pExtension_type _pExtension, const std::string& _instanceName, const std::false_type&);
    /// @}

    /// @name 'Structors
    /// @{
public:
             ExtensionCache();
    virtual ~ExtensionCache();
    /// @}

    /// @name Member Variables
    /// @{
protected:
    std::mutex                  m_mutex;
    extensions_type             m_extensions;
    extension_ptr_index_type    m_extensionIndex;
    // connections_type         m_connections;
    /// @}

};  // template class ExtensionCache

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename ExtensionPoint_type>
inline
ExtensionCache<ExtensionPoint_type>::ExtensionCache()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename ExtensionPoint_type>
inline
ExtensionCache<ExtensionPoint_type>::~ExtensionCache()
{
    // Loop through all of the connections and disconnect them
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        // for(typename ExtensionCache<ExtensionPoint_type>::connections_type::iterator iter = m_connections.begin(); iter != m_connections.end(); iter++)
        // {
        //     iter->second->disconnect();
        // }
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename ExtensionPoint_type>
inline
typename ExtensionCache<ExtensionPoint_type>::pExtension_type
ExtensionCache<ExtensionPoint_type>::getExtension(index_type _type)
{
    // TODO If supporting read/write locks, this should just be a read lock
    std::lock_guard<std::mutex> lock(m_mutex);

    // Look for the cached extension
    typename ExtensionCache<ExtensionPoint_type>::extensions_type::iterator iter = m_extensions.find(_type);

    // If found, return it.
    if (iter != m_extensions.end())
    {
        return iter->second;
    }

    // If not found, create it.
    // TODO If supporting read/write locks, promote to a write lock;
    auto pFactory = getFactory(_type);
    if (pFactory)
    {
        return pFactory->create();
    }
    return pExtension_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename ExtensionPoint_type>
inline
typename ExtensionPoint_type::Factory_type*
ExtensionCache<ExtensionPoint_type>::getFactory(index_type _type)
{
    // Create an extension query
    const I_ExtensionRegistry::pExtensionQuery_type pQuery = I_ExtensionRegistry::getSingleton().createQuery();

    pQuery->setNamespace(Extension_type::getNamespace());
    pQuery->setExtensionPoint(Extension_type::getExtensionPointName());
    pQuery->setType(_type);

    // Get the extensions
    I_ExtensionRegistry::pExtension_type pExtension;
    
    I_ExtensionRegistry::getSingleton().getExtensions(pQuery, 
        [pExtension](I_ExtensionRegistry::pExtension_type _pExtension)
        {
            // Grab the last extension; if there are more installed then eventually we can
            // deal with that but for now just grab one.
            pExtension = _pExtension;
        }
    );
    
    if (pExtension)
    {
        I_ClassFactory&
            classFactory = I_ExtensionRegistry::getSingleton().getClassFactory(pExtension);

        return dynamic_cast<Factory_type*>(&classFactory);
    }
    else
    {
        return NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename ExtensionPoint_type>
inline
void
ExtensionCache<ExtensionPoint_type>::onDestroy(wpExtension_type _pExtension)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    typename ExtensionCache<ExtensionPoint_type>::extension_ptr_index_type::iterator index = m_extensionIndex.find(_pExtension);

    if (index != m_extensionIndex.end())
    {
        typename ExtensionCache::extensions_type::iterator extension = m_extensions.find(index->second);

        if (extension != m_extensions.end())
        {
            m_extensionIndex.erase(index);
            m_extensions.erase(extension);
            
            // m_connections[_pExtension]->disconnect();
            // m_connections.erase(_pExtension);
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

// //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// template<typename ExtensionPoint_type>
// inline
// std::mutex&
// ExtensionCache<ExtensionPoint_type>::getGuard() const
// {
//     return m_mutex;
// }

// //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// template<typename ExtensionPoint_type>
// inline
// typename ExtensionCache<ExtensionPoint_type>::iterator
// ExtensionCache<ExtensionPoint_type>::begin()
// {
//     return m_extensions.begin();
// }

// //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// template<typename ExtensionPoint_type>
// inline
// typename ExtensionCache<ExtensionPoint_type>::iterator
// ExtensionCache<ExtensionPoint_type>::end()
// {
//     return m_extensions.end();
// }

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_EXTENSION_CACHE_HPP_INCLUDED
