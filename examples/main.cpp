#include <nmdbus/NetworkManager.h>
#include <nmdbus/Device.h>
#include <nmdbus/WirelessDevice.h>
#include <nmdbus/ActiveConnection.h>
#include <nmdbus/AccessPoint.h>
#include <nmdbus/Ip4Config.h>
#include <iostream>
#include <cstdio>

int main()
{
    try {
    NetworkManager nm;
    auto dev = nm.getDevice("wlp4s0");

    if (dev == nullptr) {
        std::cerr << "Device can't be found";
        return -1;
    }

    auto ac = dev->activeConnection();
    if (ac == nullptr) {
        std::cerr << "Active connection cannot be found";
        return -1;
    }

    auto ipv4 = ac->ipv4Configuration();

    if (ipv4 == nullptr) {
        std::cerr << "IPV4 configuration not found";
        return -1;
    }

    auto wifi = dev->asWireless();
    if (wifi == nullptr) {
        std::cerr << "Device is not wireless!";
        return -1;
    }

    std::cout << "State: " << wifi->bitrate() << "\n";

    for(auto ap : wifi->accessPoints()) {
        std::cout << "OLD AP: " << ap->ssid() << "\n";
    }

    wifi->scan();

    for(auto ap : wifi->accessPoints()) {
        std::cout << "NEW AP: " << ap->ssid() << " Signal: " << ap->strength() << "%\n";
    }

    nm.connect("wlp4s0", "Aquabox", "azazello");
    } catch(std::exception e) {
        std::cerr << "Exception: " << e.what();
    } catch(...) {
        std::cerr << "Unknown exception";
    }
    return 0;
}