//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  Tony Richards trichards@indiezen.com
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#ifndef ZEN_PLUGIN_EXTENSION_QUERY_HPP_INCLUDED
#define ZEN_PLUGIN_EXTENSION_QUERY_HPP_INCLUDED

#include <Zen/Plugin/I_ExtensionQuery.hpp>

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ExtensionQuery
:   public I_ExtensionQuery
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ExtensionQuery implementation
    /// @{
public:
    virtual void setNamespace(const std::string& _namespace);
    virtual void setExtensionPoint(const std::string& _extensionPoint);
    virtual void setType(const std::string& _type);
    virtual const std::string& toString() const;
    /// @}

    /// @name ExtensionQuery implementation
    /// @{
public:
    const std::string& getNamespace() const;
    const std::string& getExtensionPoint() const;
    const std::string& getType() const;

private:
    /// Convert the values to a string used in toString()
    void convertToString();
    /// @}

    /// @name 'Structors
    /// @{
public:
			 ExtensionQuery();
	virtual ~ExtensionQuery();
    /// @}

    /// @name Member variables
    /// @{
private:
    std::string             m_namespace;
    std::string             m_extensionPoint;
    std::string             m_type;

    std::string             m_string;
    /// @}

};	// class ExtensionQuery

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_EXTENSION_QUERY_HPP_INCLUDED
