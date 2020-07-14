#include "DbusHelpers.h"

namespace nm
{
    std::string Helpers::busnameFromObjectPath(const simppl::dbus::ObjectPath& path)
    {
        std::string busname;
        for (const auto& c : path.path) {
            if(c == '/' && busname.empty()) {
                continue;
            }
            busname.push_back( c == '/' ? '.' : c); 
        }
        return busname;
    }
}