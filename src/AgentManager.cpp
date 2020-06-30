#include "nmdbus/AgentManager.h"
#include "NetworkManagerInterfaces.h"

using namespace nm;

AgentManager::AgentManager()
{
    m_proxy->Register("org.gnome.nm-applet");
}

AgentManager::~AgentManager()
{
    m_proxy->Unregister();
}