//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED
#define ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Plugin/I_ConfigurationElement.hpp>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @author Tony Richards
/// @since 1.0
/// @brief Startup / Shutdown Participant
///
/// Services implementing this interface participate in the application
/// startup and shutdown sequence.
/// TODO: Why are the "prepare" methods asynchronous and not the start/stop
/// methods?
class PLUGIN_DLL_LINK I_StartupShutdownParticipant
{
    /// @name Types
    /// @{
public:
    typedef std::shared_ptr<I_StartupShutdownParticipant>  pParticipant_type;
    /// @}

    /// @name I_StartupShutdownParticipant interface
    /// @{ 
public:
    /// On the subject of the startup / shutdown, the configuration is
    /// set first, then the startup procedure is invoked.
    virtual void setConfiguration(const I_ConfigurationElement& _config) = 0;

    /// Get the configuration of the startup/shutdown participant
    virtual const I_ConfigurationElement* getConfiguration() const = 0;

    /// Prepare the service for starting.  If the service cannot start
    /// immediately, the service should start a worker thread and resolve the 
    /// returned future when the startup preparation has completed.  If the 
    /// service can start immediately then it it should start and then return a 
    /// future that has already been resolved.
    ///
    /// @return std::future<void> that is resolved once the service is prepared to
    ///             start.
    virtual std::future<void> prepareToStart() = 0;

    /// Start the service.  The service should not return from this method until
    /// the service is fully started.
    virtual void start() = 0;

    /// Prepare the service for stopping.
    /// The future that is returned will signal when the service is ready to be
    /// stopped.
    ///
    /// @return std::future<void> that is resolved once the service is ready to stop.
    virtual std::future<void> prepareToStop() = 0;

    /// Stop the service.  The service should not return from this method until
    /// the service is fully stopped.
    virtual void stop() = 0;
    /// @}

    /// @{ 'Structors
protected:
             I_StartupShutdownParticipant();
    virtual ~I_StartupShutdownParticipant();
    /// @}

};  // interface I_StartupShutdownParticipant

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED

