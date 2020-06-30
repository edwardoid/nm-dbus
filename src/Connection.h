#pragma once

#include "DbusObject.h"
#include "DbusHelpers.h"

class Connection: public DBusObject
{
public:
    Connection(const ObjectPath& path);
private:
    ForwardProxy<class ConnectionProxy> m_proxy;
};