#include "nmdbus/Settings.h"
#include "NetworkManagerInterfaces.h"
#include "nmdbus/Connection.h"

using namespace nm;

Settings::Settings()
{}

std::shared_ptr<Connection> Settings::createConnection(const ConnectionData& data)
{
    try {
        auto p = m_proxy->AddConnection(data);
        return empty(p) ? nullptr : std::make_shared<Connection>(p);
    }
    catch(const simppl::dbus::Error& e)
    {
        LOG_ERROR(e);
    }
    return nullptr;
}

std::shared_ptr<class Connection> Settings::getConnectionByUuid(const std::string& uuid)
{
    try {
        auto p = m_proxy->GetConnectionByUuid(uuid);
        return empty(p) ? nullptr : std::make_shared<Connection>(p);
    }
    catch(const simppl::dbus::Error& e)
    {
        LOG_ERROR(e);
    }
    return nullptr;
}
