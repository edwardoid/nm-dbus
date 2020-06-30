#pragma once

#include <memory>
#include "DbusHelpers.h"
#include "DbusObject.h"

class Device: public DBusObject
{
public:
    Device(const ObjectPath& path);
    std::string interface();
    std::string state();
    std::shared_ptr<class ActiveConnection> activeConnection();
    std::shared_ptr<class WirelessDevice> asWireless();
private:
    ObjectPath m_path;
    ForwardProxy<class DeviceProxy> m_proxy;
};
