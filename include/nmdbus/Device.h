#pragma once

#include <memory>
#include "ForwardProxy.h"
#include "DbusObject.h"
#include "Signal.h"

namespace nm
{
    enum NMDeviceState
    {
        NM_DEVICE_STATE_UNKNOWN = 0,
        NM_DEVICE_STATE_UNMANAGED = 10,
        NM_DEVICE_STATE_UNAVAILABLE = 20,
        NM_DEVICE_STATE_DISCONNECTED = 30,
        NM_DEVICE_STATE_PREPARE = 40,
        NM_DEVICE_STATE_CONFIG = 50,
        NM_DEVICE_STATE_NEED_AUTH = 60,
        NM_DEVICE_STATE_IP_CONFIG = 70,
        NM_DEVICE_STATE_IP_CHECK = 80,
        NM_DEVICE_STATE_SECONDARIES = 90,
        NM_DEVICE_STATE_ACTIVATED = 100,
        NM_DEVICE_STATE_DEACTIVATING = 110,
        NM_DEVICE_STATE_FAILED = 120,
    };

    class Device : public DBusObject
    {
    public:
        Device(const simppl::dbus::ObjectPath &path);
        std::string interface();
        std::shared_ptr<class ActiveConnection> activeConnection();
        std::shared_ptr<class WirelessDevice> asWireless();
        std::shared_ptr<class Ip4Config> ipv4Configuration();
        Signal<NMDeviceState, NMDeviceState> StateChanged;
        NMDeviceState state();

    private:
        ForwardProxy<class DeviceProxy> m_proxy;
    };
} // namespace nm
