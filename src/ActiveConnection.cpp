#include "ActiveConnection.h"
#include "NetworkManagerInterfaces.h"
#include "Ip4Config.h"

ActiveConnection::ActiveConnection(ObjectPath& path)
    : m_proxy(path)
{}

std::string ActiveConnection::uuid()
{
    return m_proxy->Uuid.get();
}

std::shared_ptr<Ip4Config> ActiveConnection::ipv4Configuration()
{
    auto path = m_proxy->Ip4Config.get();
    if (path.path.empty()) {
        return nullptr;
    }
    return std::make_shared<Ip4Config>(path);
}