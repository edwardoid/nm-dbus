#include "nmdbus/Device.h"
#include "NetworkManagerInterfaces.h"
#include "nmdbus/ActiveConnection.h"
#include "nmdbus/WirelessDevice.h"
#include "nmdbus/Ip4Config.h"

using namespace nm;

Device::Device(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{
    m_proxy->connected >> [this](const simppl::dbus::ConnectionState st){

        if (st == simppl::dbus::ConnectionState::Connected)
        {
            m_proxy->StateChanged.attach() >> [this] (uint32_t newState, uint32_t oldState, uint32_t) {
                StateChanged(static_cast<NMDeviceState>(newState), static_cast<NMDeviceState>(oldState));
            };
        } else {
            m_proxy->StateChanged.detach();
        }
    };

    if (m_proxy->is_connected()) {
        m_proxy->StateChanged.attach() >> [this] (uint32_t newState, uint32_t oldState, uint32_t) {
            StateChanged(static_cast<NMDeviceState>(newState), static_cast<NMDeviceState>(oldState));
        };
        StateChanged(state(), NMDeviceState::NM_DEVICE_STATE_UNKNOWN);
    }
}

std::shared_ptr<WirelessDevice> Device::asWireless()
{
    return std::make_shared<WirelessDevice>(path());
}

std::string Device::interface()
{
    SAFETY_FIRST_BEGIN
    return m_proxy->Interface.get();
    SAFETY_FIRST_END
    return "";
}

std::shared_ptr<ActiveConnection> Device::activeConnection()
{
    SAFETY_FIRST_BEGIN
    auto path = m_proxy->ActiveConnection.get();
    if (path.empty()) {
        return nullptr;
    }
    return std::make_shared<ActiveConnection>(path);
    SAFETY_FIRST_END
    return nullptr;
}

std::shared_ptr<Ip4Config> Device::ipv4Configuration()
{
    SAFETY_FIRST_BEGIN
    auto path = m_proxy->Ip4Config.get();
    if (path.empty()) {
        return nullptr;
    }
    return std::make_shared<Ip4Config>(path);
    SAFETY_FIRST_END
    return nullptr;
}

NMDeviceState Device::state()
{
    SAFETY_FIRST_BEGIN
    return static_cast<NMDeviceState>(m_proxy->State.get());
    SAFETY_FIRST_END
    return NMDeviceState::NM_DEVICE_STATE_UNKNOWN;
}