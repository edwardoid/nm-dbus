#pragma once

#include "ForwardProxy.h"

namespace nm
{
    class AgentManager
    {
    public:
        AgentManager();
        ~AgentManager();
    private:
        ForwardProxy<class AgentManagertProxy> m_proxy;
    };
}