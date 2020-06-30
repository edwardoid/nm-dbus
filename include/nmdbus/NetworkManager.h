#pragma once

#include "ForwardProxy.h"
#include "Settings.h"
#include <memory>
#include <thread>

class NetworkManager: public Settings
{
public:
    NetworkManager();
    ~NetworkManager();


    std::shared_ptr<class Device> getDevice(std::string ifname);

    bool createHotspot(std::string interface, std::string ssid, std::string passwd);

    bool connect(std::string ifname,
                 std::string ssid,
                 std::string password);

private:
    ForwardProxy<class NetworkManagerProxy> m_proxy;
};