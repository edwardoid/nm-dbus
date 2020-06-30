#pragma once

#include "DBusTypes.h"
#include "ForwardProxy.h"

class ActiveConnection
{
public:
    ActiveConnection(ObjectPath& path);
    std::string uuid();
    std::shared_ptr<class Ip4Config> ipv4Configuration();
private:
    ForwardProxy<class ActiveConnectionProxy> m_proxy;
};