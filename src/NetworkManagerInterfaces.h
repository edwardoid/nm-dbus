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
                Property<ObjectPath> Ip4Config;
                Property<uint32_t> State;
                Signal<uint32_t /* new */, uint32_t /* old */, uint32_t /* reason */> StateChanged;
                Device()
                    : INIT(Driver)
                    , INIT(Interface)
                    , INIT(ActiveConnection)
                    , INIT(Ip4Config)
                    , INIT(State)
                    , INIT(StateChanged)
                {}
            };

            namespace Connection
            {
                INTERFACE(Active)
                {
                    Property<std::string> Uuid;
                    Property<std::string> Id;
                    Property<ObjectPath> Ip4Config;
                    Property<ObjectPath> Connection;
                    Property<std::vector<ObjectPath>> Devices;
                    Method<out<ConnectionData>> GetSettings;

                    Active()
                        : INIT(Uuid)
                        , INIT(Id)
                        , INIT(Ip4Config)
                        , INIT(Connection)
                        , INIT(Devices)
                        , INIT(GetSettings)
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
                Property<uint32_t> Flags;
                Property<uint32_t> WpaFlags;
                Property<uint32_t> RsnFlags;
                Property<SsidT> Ssid;
                Property<uint32_t> Frequency;
                Property<std::string> HwAddress;
                Property<uint32_t> Mode;
                Property<uint32_t> MaxBitrate;
                Property<unsigned char> Strength;
                Property<int> LastSeen;
                AccessPoint()
                    : INIT(Flags)
                    , INIT(WpaFlags)
                    , INIT(RsnFlags)
                    , INIT(Ssid)
                    , INIT(Frequency)
                    , INIT(HwAddress)
                    , INIT(Mode)
                    , INIT(MaxBitrate)
                    , INIT(Strength)
                    , INIT(LastSeen)
                {}
            };
        }
    }
}

namespace nm
{
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
}

PROXY(Device, org::freedesktop::NetworkManager::Device);
PROXY(ActiveConnection, org::freedesktop::NetworkManager::Connection::Active)
PROXY(Ip4Config, org::freedesktop::NetworkManager::IP4Config);
PROXY(AccessPoint, org::freedesktop::NetworkManager::AccessPoint);
