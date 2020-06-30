#include "nmdbus/NetworkManager.h"
#include "nmdbus/Dispatcher.h"
#include "FreeDesktopInterfaces.h"
#include "nmdbus/UUID.h"
#include "nmdbus/Device.h"
#include "nmdbus/WirelessDevice.h"
#include "nmdbus/AccessPoint.h"
#include "nmdbus/Connection.h"
#include "nmdbus/ActiveConnection.h"
#include "nmdbus/Settings.h"


using namespace nm;

NetworkManager::NetworkManager()
{
    m_proxy->connected >> [this](const simppl::dbus::ConnectionState st){

        if (st == simppl::dbus::ConnectionState::Connected)
        {
            m_proxy->ActiveConnections.attach() >> [this] (simppl::dbus::CallState, const std::vector<ObjectPath>& acs) {
                std::vector<std::shared_ptr<ActiveConnection>> acp;
                for(auto c : acs)
                {
                    acp.push_back(std::make_shared<ActiveConnection>(c));
                }
                ActiveConnectionsChanged(acp);
            };

            m_proxy->StateChanged.attach() >> [this] (uint32_t newState) {
                this->StateChanged((NetworkingState)newState);
            };
        } else {
            m_proxy->ActiveConnections.detach();

        }
    };
    std::thread m_dispatcherThread([this]() {
        if(!Dispatcher::dispatcher().is_running()) {
            Dispatcher::dispatcher().run();
        }
    });
    m_dispatcherThread.detach();
}

NetworkManager::~NetworkManager()
{
}

NetworkingState NetworkManager::state()
{
    SAFETY_FIRST_BEGIN
    return (NetworkingState) m_proxy->State.get();
    SAFETY_FIRST_END

    return NetworkingState::Unknown;
}


ConnectivityState NetworkManager::getConnectivity()
{
    SAFETY_FIRST_BEGIN
    return (ConnectivityState) m_proxy->Connectivity.get();
    SAFETY_FIRST_END

    return ConnectivityState::Unknown;
}

std::shared_ptr<Device> NetworkManager::getDevice(std::string ifname)
{
    SAFETY_FIRST_BEGIN
    auto path = m_proxy->GetDeviceByIpIface(ifname);
    if (path.path.empty()) {
        return nullptr;
    }

    return std::make_shared<Device>(path);
    SAFETY_FIRST_END
    return nullptr;
}


bool NetworkManager::createHotspot(std::string interface, std::string ssid, std::string password)
{
    SAFETY_FIRST_BEGIN
    auto iFace = m_proxy->GetDeviceByIpIface(interface);
    ConnectionDataSection _connection = {
                { "type", std::string("802-11-wireless") },
                { CONNECTION_DATA_WIFI_UUID, uuid::generate_uuid_v4() },
                { "id", ssid },
    };

    ConnectionDataSection _802_11_wireless = {
                { CONNECTION_DATA_WIFI_SSID , std::vector<unsigned char>(ssid.cbegin(), ssid.cend()) },
                { "mode" , std::string("ap") },
                { "band", std::string("bg") },
                { "channel", uint64_t(1) }
    };

    ConnectionDataSection _ipv4 = {
                { "method", std::string("shared") }
    };

    ConnectionDataSection _ipv6 = {
                { "method", std::string("ignore") }
    };

    ConnectionDataSection _802_11_wireless_security = {
                { "key-mgmt" , std::string("wpa-psk") },
                { "auth-alg" , std::string("open") },
                { "psk", password }
    };

    ConnectionData connection = {
                { CONNECTION_DATA_CONNECTION_SECTION, _connection },
                { CONNECTION_DATA_WIRELESS_SECTION, _802_11_wireless },
                { CONNECTION_DATA_WIRELESS_SECURITY_SECTION, _802_11_wireless_security },
                { "ipv4", _ipv4 },
                { "ipv6", _ipv6 }
    };
    auto c = createConnection(connection);

    return c != nullptr;
    SAFETY_FIRST_END
    return false;
}

bool NetworkManager::connect(std::string ifname,
                             std::string ssid, std::string password)
{
    SAFETY_FIRST_BEGIN
    ConnectionDataSection _connection = {
                    { "type", std::string("802-11-wireless") },
                    { "uuid", uuid::generate_uuid_v4() },
                    { "id", ssid },
                    { "autoconnect", uint64_t(1) },
                };

    
    ConnectionDataSection _802_11_wireless_security = {
                    { "key-mgmt" , std::string("wpa-psk") },
                    { "auth-alg" , std::string("open") },
                    { "psk", password }
                };

    ConnectionDataSection _ipv4 = {
                    { "method", std::string("auto") }
                };

    ConnectionDataSection _ipv6 = {
                    { "method", std::string("ignore") }
                };

    auto dev = getDevice(ifname);

    if (dev == nullptr) {
        return false;
    }

    auto wifiDev = dev->asWireless();

    if (wifiDev == nullptr) {
        return false;
    }

    for(auto ap : wifiDev->accessPoints()) {
        if (ap->ssid() == ssid) {
            auto bssid = ap->bssid();
            ConnectionDataSection _802_11_wireless = {
                { "ssid" , std::vector<unsigned char>(ssid.cbegin(), ssid.cend()) },
                { "mode" , std::string("infrastructure") },
                { "band", std::string("bg") }
            };

            ConnectionData connection = {
                { "connection", _connection },
                { "802-11-wireless", _802_11_wireless },
                { "802-11-wireless-security", _802_11_wireless_security },
                { "ipv4", _ipv4 },
                { "ipv6", _ipv6 }
            };

            auto c = createConnection(connection);

            if (c != nullptr) {
                auto ac = m_proxy->ActivateConnection(c->path(), dev->path(), ap->path());

                return !ac.path.empty();
            }

            return false;
        }
    }
    LOGGER_ERROR_STREAM << "Network \"" << ssid << "\" was not found";
    SAFETY_FIRST_END
    return false;
}

bool NetworkManager::activate(std::shared_ptr<Connection> connection,
                              std::shared_ptr<Device> device)
{
    SAFETY_FIRST_BEGIN
    auto wifiDev = device->asWireless();

    if (wifiDev == nullptr) {
        return false;
    }

    ConnectionSettings settings = connection->settings();

    auto ssidEntry = settings.wireless.find("ssid");

    if (ssidEntry == settings.wireless.cend()) { return false; }

    std::string* ssid = ssidEntry->second.get<std::string>();

    if (ssid == nullptr) {
        return false;
    }

    for(auto ap : wifiDev->accessPoints()) {
        if (ap->ssid() == *ssid) {
            auto ac = m_proxy->ActivateConnection(connection->path(),
                                            device->path(), ap->path());

            return !ac.path.empty();
        }
    }

    SAFETY_FIRST_END

    return false;
}

std::vector<std::shared_ptr<ActiveConnection>> NetworkManager::activeConnections()
{
    std::vector<std::shared_ptr<ActiveConnection>> acp;

    SAFETY_FIRST_BEGIN
    auto all = m_proxy->ActiveConnections.get();
    for(auto c : all)
    {
        acp.push_back(std::make_shared<ActiveConnection>(c));
    }
    SAFETY_FIRST_END

    return acp;
}
