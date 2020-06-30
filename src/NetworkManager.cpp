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

NetworkManager::NetworkManager()
{
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

std::shared_ptr<Device> NetworkManager::getDevice(std::string ifname)
{
    auto path = m_proxy->GetDeviceByIpIface(ifname);
    if (path.path.empty()) {
        return nullptr;
    }

    return std::make_shared<Device>(path);
}


bool NetworkManager::createHotspot(std::string interface, std::string ssid, std::string password)
{
    try
    {
        auto iFace = m_proxy->GetDeviceByIpIface(interface);
        ConnectionDataSection _connection = {
                    { "type", std::string("802-11-wireless") },
                    { "uuid", uuid::generate_uuid_v4() },
                    { "id", ssid },
        };

        ConnectionDataSection _802_11_wireless = {
                    { "ssid" , std::vector<unsigned char>(ssid.cbegin(), ssid.cend()) },
                    { "mode" , std::string("ap") },
                    { "band", std::string("bg") },
                    { "channel", uint32_t(1) }
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
                    { "connection", _connection },
                    { "802-11-wireless", _802_11_wireless },
                    { "802-11-wireless-security", _802_11_wireless_security },
                    { "ipv4", _ipv4 },
                    { "ipv6", _ipv6 }
        };
        auto c = createConnection(connection);

        return c != nullptr;
    }
    catch(simppl::dbus::Error e)
    {
        LOG_ERROR(e);
    }
    return false;
}

bool NetworkManager::connect(std::string ifname,
                             std::string ssid, std::string password)
{
    ConnectionDataSection _connection = {
                    { "type", std::string("802-11-wireless") },
                    { "uuid", uuid::generate_uuid_v4() },
                    { "id", ssid },
                    { "autoconnect", uint32_t(1) },
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

    try
    {
        for(auto ap : wifiDev->accessPoints()) {
            if (ap->ssid() == ssid) {
                auto bssid = ap->bssid();
                std::map<std::string, simppl::Variant<std::string, uint32_t, std::vector<unsigned char>>> _802_11_wireless = {
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
        return false;
    }
    catch(simppl::dbus::Error e)
    {
        LOG_ERROR(e);
    }
    return false;
}
