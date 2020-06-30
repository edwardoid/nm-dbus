#pragma once

#include "DbusHelpers.h"

namespace org
{
    namespace freedesktop
    {
        using simppl::dbus::in;
        using simppl::dbus::out;
        using simppl::dbus::oneway;

        INTERFACE(NetworkManager)
        {
            Method<out<uint32_t>> state;
            Method<in<std::string>, out<ObjectPath>> GetDeviceByIpIface;

            Method<in<ConnectionData>, in<ObjectPath>, in<ObjectPath>, out<ObjectPath>, out<ObjectPath>> AddAndActivateConnection;
            Method<in<ObjectPath>, in<ObjectPath>, in<ObjectPath>, out<ObjectPath>> ActivateConnection;
            NetworkManager()
                : INIT(state)
                , INIT(GetDeviceByIpIface)
                , INIT(AddAndActivateConnection)
                , INIT(ActivateConnection)
                {}
        };
    }
}

struct NetworkManagerProxy : simppl::dbus::Stub<org::freedesktop::NetworkManager>
{
    NetworkManagerProxy()
     : simppl::dbus::Stub<org::freedesktop::NetworkManager>(Dispatcher::dispatcher(), "org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager")
    {
        connected >> [this](const simppl::dbus::ConnectionState st){

            if (st == simppl::dbus::ConnectionState::Connected)
            {
                std::cout << "[Manager] Connected!";
            }
        };
    }
};