#include "nmdbus/Settings.h"
#include "NetworkManagerInterfaces.h"
#include "nmdbus/Connection.h"

Settings::Settings()
{}

std::shared_ptr<Connection> Settings::createConnection(const ConnectionData& data)
{
    try {
        auto p = m_proxy->AddConnection(data);
        return p.path.empty() ? nullptr : std::make_shared<Connection>(p);
    }
    catch(simppl::dbus::Error e)
    {
        LOG_ERROR(e);
    }
    return nullptr;
}
