#pragma once

#include "Device.h"

class WirelessDevice: public Device
{
public:
    WirelessDevice(const ObjectPath& device);
    uint32_t mode();
    uint32_t bitrate();
    std::vector<std::shared_ptr<class AccessPoint>> accessPoints();
    bool scan();
private:
    ForwardProxy<class WirelessDeviceProxy> m_proxy;
};