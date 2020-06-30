#include "Ip4Config.h"
#include "NetworkManagerInterfaces.h"

Ip4Config::Ip4Config(ObjectPath& path)
    : m_proxy(path)
{}

std::vector<std::string> Ip4Config::ipAdresses()
{
    std::vector<std::string> adresses;
    for(auto& data : m_proxy->AddressData.get()) {
        for (auto key : data) {
            if (key.first == "address") {
                auto p = key.second.get<std::string>();
                if (p != nullptr) {
                    adresses.push_back(*p);
                }
            }
        }
    }

    return adresses;
}

std::string Ip4Config::ip()
{
    auto all = ipAdresses();
    if (all.empty()) {
        return "";
    }
    return *all.begin();
}