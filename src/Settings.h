#pragma once

#include "DbusHelpers.h"

class Settings
{
public:
    Settings();
    std::shared_ptr<class Connection> createConnection(const ConnectionData&);
private:
    ForwardProxy<class SettingsProxy> m_proxy;
};