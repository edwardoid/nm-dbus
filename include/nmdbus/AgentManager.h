#pragma once

#include "ForwardProxy.h"

class AgentManager
{
public:
    AgentManager();
    ~AgentManager();
private:
    ForwardProxy<class AgentManagertProxy> m_proxy;
};