#pragma once

#include "DbusObject.h"
#include "DBusTypes.h"
#include "ForwardProxy.h"

namespace nm
{
    class Connection: public DBusObject
    {
    public:
        Connection(const ObjectPath& path);
        ConnectionData settings();
    private:
        ForwardProxy<class ConnectionProxy> m_proxy;
    };
}