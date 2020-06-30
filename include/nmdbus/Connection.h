#pragma once

#include "DbusObject.h"
#include <nmdbus/DBusTypes.h>
#include <nmdbus/ConnectionSettings.h>
#include <nmdbus/ForwardProxy.h>

namespace nm
{
    class Connection: public DBusObject
    {
    public:
        Connection(const ObjectPath& path);
        ConnectionSettings settings();
    private:
        ForwardProxy<class ConnectionProxy> m_proxy;
    };
}