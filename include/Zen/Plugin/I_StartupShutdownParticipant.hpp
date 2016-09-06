//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED
#define ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED

#include "Configuration.hpp"

#include <Zen/Core/Memory/managed_ptr.hpp>

#include <Zen/Core/Threading/ThreadPool.hpp>
#include <Zen/Plugin/I_ConfigurationElement.hpp>

#include <boost/noncopyable.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
;

/// @author Tony Richards
/// @since 1.0
/// @brief Startup / Shutdown Participant
///
/// Services implementing this interface participate in the application
/// startup and shutdown sequence.
class PLUGIN_DLL_LINK I_StartupShutdownParticipant
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<I_StartupShutdownParticipant>  pParticipant_type;
    /// @}

    /// @name I_StartupShutdownParticipant interface
    /// @{ 
public:
    /// On the subject of the startup / shutdown, the configuration is
    /// set first, then the startup procedure is invoked.
    virtual void setConfiguration(const Plugins::I_ConfigurationElement& _config) = 0;

    /// Get the configuration of the startup/shutdown participant
    virtual const Plugins::I_ConfigurationElement* getConfiguration() const = 0;

    /// Prepare the service for starting.  If the service cannot start
    /// immediately, the service should return a condition variable that 
    /// will be asserted once the service is prepared to start.  If startup
    /// takes a long time (i.e. more than a millisecond) then the service 
    /// should start a thread and return a condition variable.
    /// @param _threadPool Thread Pool that the service should use if it requires
    ///         a thread pool.  Threads in the pool can also be used for service
    ///         initialization, but MUST NOT be used for tasks that need to
    ///         execute for the duration of the application.
    /// @return I_Condition that is asserted once the service is prepared to
    ///             start.  If NULL is returned then the service is already prepared
    ///             to start immediately.
    virtual Threading::I_Condition* prepareToStart(Threading::ThreadPool& _threadPool) = 0;

    /// Start the service.  The service should not return from this method until
    /// the service is fully started.
    virtual void start() = 0;

    /// Prepare the service for stopping.  If a service can stop immediately then
    /// it should return NULL, otherwise it should return a condition variable that
    /// will be asserted once the service is prepared to stop.
    /// @return I_Condition that is asserted once the service is ready to stop.
    ///             If NULL is returned then the service is already prepared to stop.
    virtual Threading::I_Condition* prepareToStop() = 0;

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
}   // namespace Plugin
namespace Memory {
    /// I_StartupShutdownParticipant is managed by a factory
    template<>
    struct is_managed_by_factory<Plugins::I_StartupShutdownParticipant> : public boost::true_type{};
}   // namespace Memory
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // ZEN_PLUGIN_I_STARTUP_SHUTDOWN_PARTICIPANT_HPP_INCLUDED

