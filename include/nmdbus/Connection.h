#pragma once

#include "DbusObject.h"
#include "DBusTypes.h"
#include "ForwardProxy.h"

class Connection: public DBusObject
{
public:
    Connection(const ObjectPath& path);
private:
    ForwardProxy<class ConnectionProxy> m_proxy;
};