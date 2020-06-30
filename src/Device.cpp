#include "Device.h"
#include "NetworkManagerInterfaces.h"
#include "ActiveConnection.h"
#include "WirelessDevice.h"

Device::Device(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}

std::string Device::state()
{
    return m_proxy->Interface.get();
}

std::shared_ptr<WirelessDevice> Device::asWireless()
{
    return std::make_shared<WirelessDevice>(path());
}

std::string Device::interface()
{
    return m_proxy->Interface.get();
}

std::shared_ptr<ActiveConnection> Device::activeConnection()
{
    auto path = m_proxy->ActiveConnection.get();
    if (path.path.empty()) {
        return nullptr;
    }
    return std::make_shared<ActiveConnection>(path);
}