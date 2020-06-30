
#pragma once

#include <memory>
#include "DbusObject.h"
#include "DBusTypes.h"
#include "ForwardProxy.h"

class AccessPoint: public DBusObject
{
public:
    AccessPoint(const ObjectPath& path);
    uint32_t strength();
    std::string ssid();
    std::string bssid();
private:
    ForwardProxy<class AccessPointProxy> m_proxy;
};
