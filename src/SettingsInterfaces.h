#pragma once

#include "DbusHelpers.h"

using namespace nm;

namespace org
{
    namespace freedesktop
    {
        using simppl::dbus::in;
        using simppl::dbus::out;
        using simppl::dbus::oneway;

        namespace NetworkManager
        {
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
}

PROXY(Connection, org::freedesktop::NetworkManager::Settings::Connection);