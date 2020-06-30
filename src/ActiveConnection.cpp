#include "nmdbus/ActiveConnection.h"
#include "nmdbus/Connection.h"
#include "nmdbus/Device.h"
#include "NetworkManagerInterfaces.h"
#include "nmdbus/Ip4Config.h"
#include "DbusHelpers.h"

using namespace nm;

ActiveConnection::ActiveConnection(ObjectPath& path)
    : m_proxy(path)
{}

std::string ActiveConnection::uuid()
{
    SAFETY_FIRST_BEGIN
    return m_proxy->Uuid.get();
    SAFETY_FIRST_END
    return "";
}

std::shared_ptr<Connection> ActiveConnection::connection()
{
    SAFETY_FIRST_BEGIN
    auto cref = m_proxy->Connection.get();
    if (cref.empty()) {
        return nullptr;
    }
    return std::make_shared<Connection>(cref);
    SAFETY_FIRST_END
    return nullptr;
} 

std::shared_ptr<Ip4Config> ActiveConnection::ipv4Configuration()
{
    SAFETY_FIRST_BEGIN
    auto path = m_proxy->Ip4Config.get();
    if (path.empty()) {
        return nullptr;
    }
    return std::make_shared<Ip4Config>(path);
    SAFETY_FIRST_END
    return nullptr;
}

std::vector<std::shared_ptr<Device>> ActiveConnection::devices()
{
    std::vector<std::shared_ptr<Device>> devs;
    SAFETY_FIRST_BEGIN
    for(auto od : m_proxy->Devices.get())
    {
        devs.emplace_back(std::make_shared<Device>(od));
    }
    SAFETY_FIRST_END
    return devs;
}