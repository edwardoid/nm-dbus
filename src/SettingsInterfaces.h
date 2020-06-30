#pragma once

#include "DbusHelpers.h"

namespace org
{
    namespace freedesktop
    {
        using simppl::dbus::in;
        using simppl::dbus::out;
        using simppl::dbus::oneway;

        namespace Settings
        {
            INTERFACE(Connection)
            {
                Method<out<ConnectionData> > GetSettings;
                Method<in<ConnectionData> > Update;
                Method<> Save;
                Connection()
                    : INIT(GetSettings)
                    , INIT(Update)
                    , INIT(Save)
                {}
            };
        }
    }
}

PROXY(Connection, org::freedesktop::Settings::Connection);