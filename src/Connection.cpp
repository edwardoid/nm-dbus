#include "nmdbus/Connection.h"
#include "SettingsInterfaces.h"

using namespace nm;

Connection::Connection(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}

ConnectionSettings Connection::settings()
{
    SAFETY_FIRST_BEGIN
    return m_proxy->GetSettings();
    SAFETY_FIRST_END

    return ConnectionSettings();
}