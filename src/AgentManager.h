#pragma once

#include "DbusHelpers.h"

class AgentManager
{
public:
    AgentManager();
    ~AgentManager();
private:
    ForwardProxy<class AgentManagertProxy> m_proxy;
};