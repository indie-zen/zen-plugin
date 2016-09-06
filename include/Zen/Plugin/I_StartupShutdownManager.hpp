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

#include <Zen/Core/Threading/I_Condition.hpp>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_StartupShutdownParticipant;

/// @brief Base StartupShutdown Manager
class PLUGIN_DLL_LINK I_StartupShutdownManager
:   boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_StartupShutdownParticipant>   pParticipant_type;
    typedef Zen::Event::Event<const std::string&>           instanceEvent_type;
    /// @}

    /// @name I_StartupShutdownManager interface
    /// @{
public:
    /// Start the installed participants.
    virtual Zen::Threading::I_Condition* start() = 0;

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
    instanceEvent_type      onStart;
    instanceEvent_type      onStop;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_StartupShutdownManager();
    virtual ~I_StartupShutdownManager();
    /// @}

    
};  // interface I_StartupShutdownManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen
}   // namespace Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED
