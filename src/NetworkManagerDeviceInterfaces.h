#pragma once

#include "DbusHelpers.h"

using namespace nm;

namespace org
{
    namespace freedesktop
    {
        using simppl::dbus::in;
        using simppl::dbus::out;
        using simppl::dbus::oneway;

        namespace NetworkManager
        {
            namespace Device
            {
                INTERFACE(Wireless)
                {
                    Property<uint32_t> Mode;
                    Property<uint32_t> Bitrate;
                    Property<ObjectPath> ActiveAccessPoint;
                    Method<out<std::vector<ObjectPath>>> GetAllAccessPoints;
                    typedef std::map<
                                    std::string,
                                    std::variant<
                                        std::vector<
                                            simppl::dbus::FixedSizeBuffer<32>
                                        >
                                    >
                                >  ScanOptions;
                    Method<in<ScanOptions>> RequestScan;
                    Signal<> ScanDone;
                    Wireless()
                        : INIT(Mode)
                        , INIT(Bitrate)
                        , INIT(ActiveAccessPoint)
                        , INIT(GetAllAccessPoints)
                        , INIT(RequestScan)
                        , INIT(ScanDone)
                    {}
                };
            }
        }
    }
}

PROXY(WirelessDevice, org::freedesktop::NetworkManager::Device::Wireless);