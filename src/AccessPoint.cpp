#include "nmdbus/AccessPoint.h"
#include "NetworkManagerInterfaces.h"

AccessPoint::AccessPoint(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}

uint32_t AccessPoint::strength()
{
    return m_proxy->Strength.get();
}

std::string AccessPoint::ssid()
{
    auto raw = m_proxy->Ssid.get();
    raw.push_back('\0');
    return (const char*)(raw.data());
}

std::string AccessPoint::bssid()
{
    return m_proxy->HwAddress.get();
}