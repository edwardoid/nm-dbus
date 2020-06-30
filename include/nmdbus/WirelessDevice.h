#pragma once

#include "Device.h"
#include <vector>

namespace nm
{
    class WirelessDevice: public Device
    {
    public:
        WirelessDevice(const simppl::dbus::ObjectPath& device);
        uint32_t mode();
        uint32_t bitrate();
        std::vector<std::shared_ptr<class AccessPoint>> accessPoints();
        std::shared_ptr<class AccessPoint> activeAccessPoint();
        bool scan(bool force = true);
    private:
        ForwardProxy<class WirelessDeviceProxy> m_proxy;
    };
}