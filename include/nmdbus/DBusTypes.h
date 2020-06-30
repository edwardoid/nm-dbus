#pragma once


#include <memory>
#include "simppl/objectpath.h"
#include <simppl/vector.h>
#include <simppl/map.h>
#include <simppl/variant.h>

typedef std::vector<unsigned char> SsidT;
typedef std::map<std::string, simppl::Variant<std::string, uint32_t, SsidT > > ConnectionDataSection;
typedef std::map<std::string, ConnectionDataSection > ConnectionData;
using ObjectPath = simppl::dbus::ObjectPath;