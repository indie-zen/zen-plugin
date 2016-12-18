//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C) 2008 - 2009 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED
#define ZEN_PLUGIN_I_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

// Events aren't implemented in 2.0 yet
//#include <Zen/Core/Event/Event.hpp>

#include <Zen/Plugin/I_Configuration.hpp>

#include <future>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_StartupShutdownParticipant;

/// @brief Base StartupShutdown Manager
class PLUGIN_DLL_LINK I_StartupShutdownManager
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_StartupShutdownParticipant>   pParticipant_type;
    // typedef Zen::Event::Event<const std::string&>           instanceEvent_type;
    /// @}

    /// @name I_StartupShutdownManager interface
    /// @{
public:
    /// Start the installed participants.
    virtual std::future<void> start() = 0;

    /// @brief Stop the installed participants
    ///
    /// This method will return when the manager is fully stopped and destroyed.
    /// Do not reference this object after stop() is called.
    virtual void stop() = 0;

    /// Install a participant into this manager.
    /// @param _name The name of the participant. This name must be unique to this manager.
    virtual void installParticipant(pParticipant_type _pParticipant) = 0;
    /// @}

    /// @name Static Methods
    /// @{
public:
    /// Get a startup-shutdown manager by name.
    ///
    /// The lifetime of a manager is from the time that getInstance()
    /// returns to the time that I_StartupShutdownManager::stop() is called and the 
    /// manager is fully stopped.
    static I_StartupShutdownManager& getInstance(const std::string& _instanceName);

    /// Start all initialized instances
    static void startAll();

    /// Stop and destroy all initialized instances
    static void stopAll();
    /// @}

    /// @name Events
    /// @{
public:
    // TODO Zen Plugin 2.0 does not support events yet
    // instanceEvent_type      onStart;
    // instanceEvent_type      onStop;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_StartupShutdownManager();
    virtual ~I_StartupShutdownManager();
    /// @}

    // Not copyable nor assignable
    I_StartupShutdownManager(const I_StartupShutdownManager&) = delete;
    void operator=(const I_StartupShutdownManager&) = delete;

};  // interface I_StartupShutdownManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen
}   // namespace Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED
