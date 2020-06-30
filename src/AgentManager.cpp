#include "AgentManager.h"
#include "NetworkManagerInterfaces.h"

AgentManager::AgentManager()
{
    m_proxy->Register("org.gnome.nm-applet");
}

AgentManager::~AgentManager()
{
    m_proxy->Unregister();
}