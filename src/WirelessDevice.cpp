#include "nmdbus/WirelessDevice.h"
#include "nmdbus/AccessPoint.h"
#include "NetworkManagerDeviceInterfaces.h"
#include <iostream>
#include <mutex>

WirelessDevice::WirelessDevice(const ObjectPath& path)
    : Device(path)
    , m_proxy(path)
{
    m_proxy->ScanDone.attach() >> [this]() {
            std::cout << "Scan done!";
    };
}

uint32_t WirelessDevice::mode()
{
    return m_proxy->Mode.get();
}

uint32_t WirelessDevice::bitrate()
{
    return m_proxy->Bitrate.get();
}

std::vector<std::shared_ptr<AccessPoint>> WirelessDevice::accessPoints()
{
    std::vector<std::shared_ptr<AccessPoint>> points;

    try {
        for (auto op : m_proxy->GetAllAccessPoints())
        {
            points.push_back(std::make_shared<AccessPoint>(op));
        }
    }
    catch(simppl::dbus::Error e)
    {
        LOG_ERROR(e);
    }
    return points;
}

bool WirelessDevice::scan()
{
    try
    {
        std::string forceScanCommand = "iwlist ";
        forceScanCommand += interface();
        forceScanCommand += " scan >> /dev/null";
        system(forceScanCommand.c_str());

        m_proxy->RequestScan(WirelessDeviceProxy::ScanOptions());
        return true;
    }
    catch(simppl::dbus::Error e)
    {
        LOG_ERROR(e);
    }
    return false;
}