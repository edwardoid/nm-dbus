#include "nmdbus/Connection.h"
#include "SettingsInterfaces.h"

Connection::Connection(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}