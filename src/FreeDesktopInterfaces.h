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

        INTERFACE(NetworkManager)
        {
            Method<out<uint32_t>> state;
            Method<in<std::string>, out<ObjectPath>> GetDeviceByIpIface;

            Method<in<ConnectionData>, in<ObjectPath>, in<ObjectPath>, out<ObjectPath>, out<ObjectPath>> AddAndActivateConnection;
            Method<in<ObjectPath>, in<ObjectPath>, in<ObjectPath>, out<ObjectPath>> ActivateConnection;
            Property<uint32_t> Connectivity;
            Property<uint32_t> State;
            Property<std::vector<ObjectPath>> ActiveConnections;
            Signal<uint32_t> StateChanged;
            NetworkManager()
                : INIT(state)
                , INIT(GetDeviceByIpIface)
                , INIT(AddAndActivateConnection)
                , INIT(ActivateConnection)
                , INIT(Connectivity)
                , INIT(State)
                , INIT(ActiveConnections)
                , INIT(StateChanged)
                {}
        };
    }
}

namespace nm
{
    struct NetworkManagerProxy : simppl::dbus::Stub<org::freedesktop::NetworkManager>
    {
        NetworkManagerProxy()
        : simppl::dbus::Stub<org::freedesktop::NetworkManager>(Dispatcher::dispatcher(), "org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager")
        {
        }
    };
}