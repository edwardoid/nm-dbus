
#pragma once

#include <memory>
#include "DbusObject.h"
#include "DBusTypes.h"
#include "ForwardProxy.h"

namespace nm
{
    enum class Security
    {
        None = 0,
        WEP = 1,
        WPA = 2,
        WPA2 = 3,
        Enterprise = 4,
        Unknown = 5
    };

    class AccessPoint: public DBusObject
    {
    public:
        AccessPoint(const ObjectPath& path);
        uint32_t strength();
        std::string ssid();
        std::string bssid();
        Security security();
        bool encrypted();
    private:
        ForwardProxy<class AccessPointProxy> m_proxy;
    };
}
