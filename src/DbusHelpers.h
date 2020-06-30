#pragma once

#include "simppl/interface.h"
#include "simppl/property.h"
#include "simppl/string.h"
#include "simppl/vector.h"
#include "simppl/map.h"
#include "simppl/tuple.h"
#include "simppl/bool.h"
#include "simppl/variant.h"
#include "simppl/stub.h"
#include "simppl/buffer.h"
#include "simppl/struct.h"
#include "simppl/serialization.h"
#include "simppl/objectpath.h"
#include "Dispatcher.h"
#include <memory>

typedef std::vector<unsigned char> SsidT;
typedef std::map<std::string, simppl::Variant<std::string, uint32_t, SsidT > > ConnectionDataSection;
typedef std::map<std::string, ConnectionDataSection > ConnectionData;

using ObjectPath = simppl::dbus::ObjectPath;

template<typename ProxyT>
class ForwardProxy
{
public:
    template <class... Args>
    ForwardProxy(Args&&... args) : p(std::make_shared<ProxyT>(args...))
    {}
    
    ProxyT* operator -> () {
        return p.get();
    }
private:
    std::shared_ptr<ProxyT> p;
};

#ifndef LOGGER_ERROR_STREAM

#include <iostream>

#define LOGGER_ERROR_STREAM std::cerr

#endif // LOGGER_ERROR_STREAM

#ifndef LOGGER_INFO_STREAM

#include <iostream>

#define LOGGER_INFO_STREAM std::cout

#endif // LOGGER_INFO_STREAM


#define LOG_ERROR(e) LOGGER_ERROR_STREAM << "In " << __FILE__ << ":" << __LINE__ << " error name = " << e.name() \
                                         << "\nMessage: " << e.message() \
                                         << "\nWhat: " << e.what() \
                                         << "\nSerial: " << e.serial() << '\n';

#define PROXY(Proxyof, Interface) \
struct Proxyof ## Proxy  : public simppl::dbus::Stub<Interface> \
{ \
    Proxyof ## Proxy (const ObjectPath& path) \
     : simppl::dbus::Stub<Interface>(Dispatcher::dispatcher(), "org.freedesktop.NetworkManager", path.path.c_str()) \
    {} \
};
