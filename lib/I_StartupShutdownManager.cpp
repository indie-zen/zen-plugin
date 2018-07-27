//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Zen Plugin Framework
//
// Copyright (C) 2001 - 2018 Raymond A. Richards
// Copyright (C) 2008 - 2009 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include <Zen/Plugin/I_StartupShutdownManager.hpp>

#include "StartupShutdownManager.hpp"

#include <map>
#include <mutex>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen::Plugin {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static std::map< std::string, I_StartupShutdownManager* > sm_managers;
static std::mutex sm_managerGuard;
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_StartupShutdownManager&
I_StartupShutdownManager::getInstance(const std::string& _name)
{
    std::lock_guard<std::mutex> lock(sm_managerGuard);

    std::map<std::string, I_StartupShutdownManager*>::iterator iter = sm_managers.find(_name);
    if( iter == sm_managers.end() )
    {
        I_StartupShutdownManager* pManager = new StartupShutdownManager();
        sm_managers[_name] = pManager;
        return *pManager;
    }
    else
    {
        return *iter->second;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
I_StartupShutdownManager::startAll()
{
    std::lock_guard<std::mutex> lock(sm_managerGuard);

    std::map<std::string, I_StartupShutdownManager*>::iterator iter = sm_managers.begin();
    while( iter != sm_managers.end() )
    {
        // TODO Instead of serially starting and waiting for each participant,
        // start all of them and then wait for all of them to be started?
        auto started = iter->second->start();
        started.wait();
        iter++;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
I_StartupShutdownManager::stopAll()
{
    std::lock_guard<std::mutex> lock(sm_managerGuard);

    std::map<std::string, I_StartupShutdownManager*>::iterator iter = sm_managers.end();
    while( iter != sm_managers.end() )
    {
        iter->second->stop();
        iter++;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace Zen::Plugin
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
