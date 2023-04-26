#pragma once

#include <simppl/string.h>
#include <simppl/variant.h>
#include <simppl/vector.h>
#include <simppl/serialization.h>
#include <simppl/struct.h>
#include <variant>

namespace nm
{
    struct ConnectionSettings
    {
        typedef simppl::dbus::Codec<ConnectionSettings> serializer_type;
        
        typedef unsigned long long timestamp_t;
        typedef std::vector<unsigned char> byte_array_t;
        typedef std::vector<std::string> string_array_t;

        typedef std::vector<std::map<std::string, std::variant<uint> > > adress_data_t;

        typedef std::map<std::string, std::variant<
                                            std::string,
                                            string_array_t,
                                            timestamp_t
                                                    >
                        > ConnectionSectionT;

        typedef std::map<std::string, std::variant<
                                            byte_array_t,
                                            std::string,
                                            string_array_t,
                                            uint32_t,
                                            bool
                                                    >
                        > WirelessSectionT;
        typedef std::map<std::string, std::variant<
                                            std::string,
                                            string_array_t
                                                    >
                        > WirelessSecuritySectionT;
        typedef std::map<std::string, std::variant<
                                            std::string,
                                            string_array_t,
                                            std::vector<uint32_t>,
                                            std::vector<std::vector<uint32_t> >,
                                            adress_data_t
                                                    >
                        > IPV4SectionT;

        typedef std::vector<unsigned char> ip_t;
        typedef uint ip_prefix;
        typedef std::vector<unsigned char> ip_gateway_t;
        struct ipv6_address_t
        {
            typedef simppl::dbus::make_serializer<ip_t, ip_prefix, ip_gateway_t>::type serializer_type;
            ip_t ip;
            ip_prefix prefix;
            ip_gateway_t gateway;
        };

        struct route_entry_t
        {
            typedef simppl::dbus::make_serializer<ip_t, ip_prefix, ip_gateway_t, uint>::type serializer_type;
            ip_t dest;
            ip_prefix prefix;
            ip_gateway_t gateway;
            uint metric;
        };

        typedef std::vector<ipv6_address_t> ipv6_address_array_t;
        typedef std::vector<route_entry_t> routedata_t;


        typedef std::map<std::string, std::variant<
                                            std::string,
                                            string_array_t,
                                            std::vector<byte_array_t>,
                                            ipv6_address_array_t,
                                            routedata_t,
                                            adress_data_t
                                                    >
                        > IPV6SectionT;

        ConnectionSectionT connection;
        WirelessSectionT wireless;
        WirelessSecuritySectionT security;
        IPV4SectionT ipv4;
        IPV6SectionT ipv6;
    };
}

namespace simppl
{

namespace dbus
{

template<>
struct Codec<nm::ConnectionSettings>
{
    static 
    void encode(DBusMessageIter& iter, nm::ConnectionSettings& m)
    {
    //   std::ostringstream buf;
    //   Codec<std::pair<KeyT, ValueT>>::make_type_signature(buf);

    //   DBusMessageIter _iter;
    //   dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, buf.str().c_str(), &_iter);

    //   for (auto& e : m) {
    //      Codec<std::pair<KeyT, ValueT>>::encode(_iter, e);
    //   }

    //   dbus_message_iter_close_container(&iter, &_iter);
    }

    static 
    void decode(DBusMessageIter& iter, nm::ConnectionSettings& m)
    {
        DBusMessageIter _iter;
        simppl_dbus_message_iter_recurse(&iter, &_iter, DBUS_TYPE_ARRAY);
        while(dbus_message_iter_get_arg_type(&_iter) != 0)
        {
            DBusMessageIter item_iterator;
            simppl_dbus_message_iter_recurse (&_iter, &item_iterator, DBUS_TYPE_DICT_ENTRY);

            std::string propertyName;
            Codec<std::string>::decode(item_iterator, propertyName);

            if (propertyName == "connection")
            {
                Codec<nm::ConnectionSettings::ConnectionSectionT>::decode(item_iterator, m.connection);
            } else if (propertyName == "802-11-wireless") {
                Codec<nm::ConnectionSettings::WirelessSectionT>::decode(item_iterator, m.wireless);
            } else if (propertyName == "802-11-wireless-security") {
                Codec<nm::ConnectionSettings::WirelessSecuritySectionT>::decode(item_iterator, m.security);
            } else if (propertyName == "ipv4") {
                Codec<nm::ConnectionSettings::IPV4SectionT>::decode(item_iterator, m.ipv4);
            } else if (propertyName == "ipv6") {
                Codec<nm::ConnectionSettings::IPV6SectionT>::decode(item_iterator, m.ipv6);
            }
            
            // advance to next element
            dbus_message_iter_next(&_iter);
        }

        // advance to next element
        dbus_message_iter_next(&iter);
   }
   
   
   static inline
   std::ostream& make_type_signature(std::ostream& os)
   {
        os << DBUS_TYPE_ARRAY_AS_STRING
            << DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
                << DBUS_TYPE_VARIANT_AS_STRING
            << DBUS_DICT_ENTRY_END_CHAR_AS_STRING;
        return os;
   }
};

   
}   // namespace dbus

}   // namespace simppl