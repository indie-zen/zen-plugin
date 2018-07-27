//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
// Copyright (C) 2008 - 2009 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED
#define ZEN_PLUGIN_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED

#include <Zen/Plugin/I_StartupShutdownManager.hpp>

#include <Zen/Plugin/I_Configuration.hpp>

#include <set>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {

class StartupShutdownManager
:   public I_StartupShutdownManager
{
    /// @name Types
    /// @{
public:
    typedef std::set<pParticipant_type>     Participants_type;
    /// @}

    /// @name Enums
    /// @{
public:
    enum ManagerStates
    {
        INITIALIZED,
        STARTING,
        STARTED,
        STOPPING,
        STOPPED
    };
    /// @}

    /// @name I_StartupShutdownManager implementation
    /// @{
public:
    virtual std::future<void> start();
    virtual void stop();
    virtual void installParticipant(pParticipant_type _pParticipant);
    /// @}

    /// @name StartupShutdownManager implementation
    /// @{
public:
    /// Install a participant.
    ///
    /// This is called by an InstallParticipantTask that is queued into m_installQueue
    ///
    /// @note Internal use only
    void handleInstallParticipant(pParticipant_type);

    /// Return the manager's shared thread pool
    ///
    /// This is called during the startup process for installed participants.
    ///
    /// @note Internal use only
    // Threading::ThreadPool& getSharedThreadPool() { return m_sharedThreadPool; }
    /// @}

    /// @name Events
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
public:
             StartupShutdownManager();
    virtual ~StartupShutdownManager();
    /// @}

    /// @name Member variables
    /// @{
private:
    ManagerStates   m_currentState;

    /// ThreadPool that's shared among all of the participants.
    // Threading::ThreadPool   m_sharedThreadPool;

    /// Queue of items that require installation
    /// plus the thread that is used to perform
    /// the installation.
    // Threading::ThreadPool   m_installQueue;

    /// Queue of items that require graceful shutdown
    /// plus the thread that is use to perform
    /// the shutdown.
    // Threading::ThreadPool   m_shutdownQueue;

    /// Guard for m_participants consistency
    std::mutex     m_participantGuard;

    /// Collection of installed participants
    Participants_type       m_participants;
    /// @}

};  // class StartupShutdownManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_STARTUP_SHUTDOWN_MANAGER_HPP_INCLUDED
