#pragma once

#include "DBusTypes.h"
#include "ForwardProxy.h"

namespace nm
{
    class ActiveConnection
    {
    public:
        ActiveConnection(ObjectPath& path);
        std::string uuid();
        std::shared_ptr<class Connection> connection();
        std::shared_ptr<class Ip4Config> ipv4Configuration();
        std::vector<std::shared_ptr<class Device>> devices();
    private:
        ForwardProxy<class ActiveConnectionProxy> m_proxy;
    };
}