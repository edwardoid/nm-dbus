#pragma once

#include "DbusHelpers.h"

namespace org
{
    namespace freedesktop
    {
        using simppl::dbus::in;
        using simppl::dbus::out;
        using simppl::dbus::oneway;

        namespace NetworkManager
        {
            INTERFACE(AgentManager)
            {
                Method<in<std::string>> Register;
                Method<> Unregister;
                AgentManager()
                    : INIT(Register)
                    , INIT(Unregister)
                {}
            };

            INTERFACE(Settings)
            {
                Method<out<std::vector<simppl::dbus::ObjectPath>>> ListConnections;
                Method<in<std::string>, out<simppl::dbus::ObjectPath>> GetConnectionByUuid;
                Method<in<ConnectionData>, out<simppl::dbus::ObjectPath>> AddConnection;
                Signal<simppl::dbus::ObjectPath> NewConnection;
                Signal<simppl::dbus::ObjectPath> ConnectionRemoved;
                Settings()
                    : INIT(ListConnections)
                    , INIT(GetConnectionByUuid)
                    , INIT(AddConnection)
                    , INIT(NewConnection)
                    , INIT(ConnectionRemoved)
                {}
            };

            INTERFACE(Device)
            {
                Property<std::string> Driver;
                Property<std::string> Interface;
                Property<ObjectPath> ActiveConnection;
                Device()
                    : INIT(Driver)
                    , INIT(Interface)
                    , INIT(ActiveConnection)
                {}
            };

            namespace Connection
            {
                INTERFACE(Active)
                {
                    Property<std::string> Uuid;
                    Property<std::string> Id;
                    Property<ObjectPath> Ip4Config;

                    Active()
                        : INIT(Uuid)
                        , INIT(Id)
                        , INIT(Ip4Config)
                    {}
                };
            }

            INTERFACE(IP4Config)
            {
                typedef std::vector<
                    std::map <
                        std::string, 
                        simppl::Variant<std::string, uint32_t>
                    >
                > AdressDataT;

                Property<AdressDataT> AddressData;
                IP4Config()
                    : INIT(AddressData)
                {}
            };

            INTERFACE(AccessPoint)
            {
                Property<SsidT> Ssid;
                Property<std::string> HwAddress;
                Property<unsigned char> Strength;
                AccessPoint()
                    : INIT(Ssid)
                    , INIT(HwAddress)
                    , INIT(Strength)
                {}
            };
        }
    }
}

struct AgentManagertProxy : simppl::dbus::Stub<org::freedesktop::NetworkManager::AgentManager>
{
    AgentManagertProxy()
     : simppl::dbus::Stub<org::freedesktop::NetworkManager::AgentManager>(Dispatcher::dispatcher(), "org.freedesktop.NetworkManager.AgentManager", "/org/freedesktop/NetworkManager/AgentManager")
    {}
};


struct SettingsProxy : simppl::dbus::Stub<org::freedesktop::NetworkManager::Settings>
{
    SettingsProxy()
     : simppl::dbus::Stub<org::freedesktop::NetworkManager::Settings>(Dispatcher::dispatcher(), "org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager/Settings")
    {}
};

PROXY(Device, org::freedesktop::NetworkManager::Device);
PROXY(ActiveConnection, org::freedesktop::NetworkManager::Connection::Active)
PROXY(Ip4Config, org::freedesktop::NetworkManager::IP4Config);
PROXY(AccessPoint, org::freedesktop::NetworkManager::AccessPoint);
