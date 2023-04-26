#pragma once


#include <memory>
#include "simppl/objectpath.h"
#include <simppl/vector.h>
#include <simppl/map.h>
#include <variant>
#include <simppl/variant.h>

#define CONNECTION_DATA_CONNECTION_SECTION "connection"
#define CONNECTION_DATA_WIRELESS_SECTION "802-11-wireless"
#define CONNECTION_DATA_WIRELESS_SECURITY_SECTION  "802-11-wireless-security"

#define CONNECTION_DATA_WIFI_SSID "ssid"
#define CONNECTION_DATA_WIFI_UUID "uuid"

namespace nm
{
    typedef std::vector<unsigned char> SsidT;
    typedef std::map<std::string, std::variant<std::string,
                                               std::vector<std::string>,
                                               uint64_t,
                                               SsidT>
                    > ConnectionDataSection;
    typedef std::map<std::string, ConnectionDataSection > ConnectionData;
    using ObjectPath = simppl::dbus::ObjectPath;

    inline bool empty(const ObjectPath& path) { return path.path.size() == 0;}
}