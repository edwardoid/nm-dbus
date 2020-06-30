#pragma once

#include "DbusHelpers.h"
#include <memory>

class Ip4Config
{
public:
    Ip4Config(ObjectPath& path);
    std::string ip();
    std::vector<std::string> ipAdresses();
private:
    ForwardProxy<class Ip4ConfigProxy> m_proxy;
};