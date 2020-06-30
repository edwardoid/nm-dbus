#include "nmdbus/Device.h"
#include "NetworkManagerInterfaces.h"
#include "nmdbus/ActiveConnection.h"
#include "nmdbus/WirelessDevice.h"
#include "nmdbus/Ip4Config.h"

using namespace nm;

Device::Device(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}

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
    if (path.path.empty()) {
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
    if (path.path.empty()) {
        return nullptr;
    }
    return std::make_shared<Ip4Config>(path);
    SAFETY_FIRST_END
    return nullptr;
}