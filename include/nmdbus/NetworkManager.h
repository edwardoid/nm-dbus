#pragma once

#include "ForwardProxy.h"
#include "Settings.h"
#include "Signal.h"
#include <memory>
#include <thread>

namespace nm
{
    enum class ConnectivityState: uint32_t
    {
        Unknown = 0,
        None = 1,
        Portal = 2,
        Limited = 3,
        Full = 4
    };

    enum class NetworkingState: uint32_t
    {
        Unknown = 0,
        Asleep = 10,
        Disconnected = 20,
        Connecting = 40,
        ConnectedLocal = 50,
        ConnectedSite = 60,
        ConnectedGlobal = 70
    };

    class NetworkManager: public Settings
    {
    public:
        NetworkManager();
        ~NetworkManager();

        NetworkingState state();

        ConnectivityState getConnectivity();

        std::shared_ptr<class Device> getDevice(std::string ifname);

        bool createHotspot(std::string interface, std::string ssid, std::string passwd);

        bool connect(std::string ifname,
                    std::string ssid,
                    std::string password);

        bool activate(std::shared_ptr<class Connection> connection,
                      std::shared_ptr<class Device> device);

        Signal<std::vector<std::shared_ptr<class ActiveConnection> >> ActiveConnectionsChanged;

        Signal<NetworkingState> StateChanged;

        std::vector<std::shared_ptr<class ActiveConnection>> activeConnections();
    private:
        ForwardProxy<class NetworkManagerProxy> m_proxy;
    };
}