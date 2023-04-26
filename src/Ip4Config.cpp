#include "nmdbus/Ip4Config.h"
#include "NetworkManagerInterfaces.h"

using namespace nm;

Ip4Config::Ip4Config(ObjectPath& path)
    : m_proxy(path)
{}

std::vector<std::string> Ip4Config::ipAdresses()
{
    std::vector<std::string> adresses;
    SAFETY_FIRST_BEGIN
    for(auto& data : m_proxy->AddressData.get()) {
        for (auto key : data) {
            if (key.first == "address") {
                try {
                    adresses.push_back(std::get<std::string>(key.second));
                } catch (std::bad_variant_access const& ex)
                {
                    LOGGER_ERROR_STREAM << ex.what();
                }
            }
        }
    }
    SAFETY_FIRST_END

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