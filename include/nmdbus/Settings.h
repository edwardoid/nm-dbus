#pragma once

#include "DBusTypes.h"
#include "ForwardProxy.h"

namespace nm
{
    class Settings
    {
    public:
        Settings();
        std::shared_ptr<class Connection> createConnection(const ConnectionData&);
        std::shared_ptr<class Connection> getConnectionByUuid(const std::string& uuid);
    private:
        ForwardProxy<class SettingsProxy> m_proxy;
    };
}