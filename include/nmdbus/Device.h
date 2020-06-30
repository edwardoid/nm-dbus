#pragma once

#include <memory>
#include "ForwardProxy.h"
#include "DbusObject.h"

namespace nm
{
    class Device: public DBusObject
    {
    public:
        Device(const simppl::dbus::ObjectPath& path);
        std::string interface();
        std::shared_ptr<class ActiveConnection> activeConnection();
        std::shared_ptr<class WirelessDevice> asWireless();
        std::shared_ptr<class Ip4Config> ipv4Configuration();
    private:
        ForwardProxy<class DeviceProxy> m_proxy;
    };
}
