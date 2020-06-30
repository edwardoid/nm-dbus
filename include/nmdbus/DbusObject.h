#pragma once

#include <simppl/objectpath.h>

namespace nm
{
    class DBusObject
    {
    public:
        DBusObject(const simppl::dbus::ObjectPath& path)
        : m_path(path) {}
        simppl::dbus::ObjectPath path() { return m_path; }
    protected:
        simppl::dbus::ObjectPath m_path;
    };
}