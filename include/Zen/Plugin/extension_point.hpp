//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_EXTENSION_POINT_HPP_INCLUDED
#define ZEN_PLUGIN_EXTENSION_POINT_HPP_INCLUDED

#include <Zen/Plugin/I_ClassFactory.hpp>
#include <Zen/Plugin/I_ExtensionQuery.hpp>
#include <Zen/Plugin/I_ExtensionPoint.hpp>
#include <Zen/Plugin/I_ExtensionRegistry.hpp>

#include <memory>
#include <string>

// for debugging
#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename tExtension_type, typename tFactory_type, typename tIndex_type = std::string>
class extension_point
: public I_ExtensionPoint
{
public:
    typedef tIndex_type                     index_type;
    typedef tExtension_type                 Extension_type;
    typedef tFactory_type                   Factory_type;
    
    typedef std::shared_ptr<Extension_type> pExtension_type;
public:
    extension_point(const char* _namespace, const char* _extensionPointName)
    :   m_namespace(_namespace)
    ,   m_extensionPointName(_extensionPointName)
    {
    }
    
    virtual ~extension_point() = default;
    
    const std::string& getNamespace()
    {
        return m_namespace;
    }

    const std::string& getExtensionPointName()
    {
        return m_extensionPointName;
    }

    template<class... Types>
    pExtension_type create(index_type _type, Types... args);

protected:
    Factory_type* getFactory(index_type _type);
    
private:
    const std::string m_namespace;
    const std::string m_extensionPointName;
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename tExtension_type, typename tFactory_type, typename tIndex_type>
tFactory_type*
extension_point<tExtension_type, tFactory_type, tIndex_type>::getFactory(tIndex_type _type)
{
    // Create an extension query
    const I_ExtensionRegistry::pExtensionQuery_type pQuery = I_ExtensionRegistry::getSingleton().createQuery();

    pQuery->setNamespace(getNamespace());
    pQuery->setExtensionPoint(getExtensionPointName());
    pQuery->setType(_type);

    // Get the extensions
    I_ExtensionRegistry::pExtension_type pExtension =
        I_ExtensionRegistry::getSingleton().findExtension(pQuery, 
            [](I_ExtensionRegistry::pExtension_type _pExtension) -> bool
            {
                // Indicate that the first one is the correct one
                // (we'll deal with any actual filtering a later date)
                return true;
            }
    );
    
    // if (pExtension)
    // {
    //     I_ClassFactory&
    //         classFactory = I_ExtensionRegistry::getSingleton().getClassFactory(pExtension);

    //     return dynamic_cast<Factory_type*>(&classFactory);
    // }
    // else
    {
        return NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<typename tExtension_type, typename tFactory_type, typename tIndex_type>
template<class... Types>
typename extension_point<tExtension_type, tFactory_type, tIndex_type>::pExtension_type
extension_point<tExtension_type, tFactory_type, tIndex_type>::create(index_type _type, 
    Types... args)
{
    std::cout << "extension_point::create" << std::endl;
    auto* pFactory = getFactory(_type);
    std::cout << "Got factory" << std::endl;
    return pFactory->create(&args...);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Plugin
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // !ZEN_PLUGIN_EXTENSION_POINT_HPP_INCLUDED
