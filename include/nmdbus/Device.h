#pragma once

#include <memory>
#include "ForwardProxy.h"
#include "DbusObject.h"

class Device: public DBusObject
{
public:
    Device(const simppl::dbus::ObjectPath& path);
    std::string interface();
    std::string state();
    std::shared_ptr<class ActiveConnection> activeConnection();
    std::shared_ptr<class WirelessDevice> asWireless();
private:
    simppl::dbus::ObjectPath m_path;
    ForwardProxy<class DeviceProxy> m_proxy;
};
