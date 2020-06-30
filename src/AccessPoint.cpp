#include "nmdbus/AccessPoint.h"
#include "NetworkManagerInterfaces.h"

enum class NM80211ApSecurityFlags: uint32_t {
    NM_802_11_AP_SEC_NONE            = 0x00000000,
    NM_802_11_AP_SEC_PAIR_WEP40      = 0x00000001,
    NM_802_11_AP_SEC_PAIR_WEP104     = 0x00000002,
    NM_802_11_AP_SEC_PAIR_TKIP       = 0x00000004,
    NM_802_11_AP_SEC_PAIR_CCMP       = 0x00000008,
    NM_802_11_AP_SEC_GROUP_WEP40     = 0x00000010,
    NM_802_11_AP_SEC_GROUP_WEP104    = 0x00000020,
    NM_802_11_AP_SEC_GROUP_TKIP      = 0x00000040,
    NM_802_11_AP_SEC_GROUP_CCMP      = 0x00000080,
    NM_802_11_AP_SEC_KEY_MGMT_PSK    = 0x00000100,
    NM_802_11_AP_SEC_KEY_MGMT_802_1X = 0x00000200,
    NM_802_11_AP_SEC_KEY_MGMT_SAE    = 0x00000400
};

enum class NM80211ApFlags: uint32_t
{
    NM_802_11_AP_FLAGS_NONE    = 0x00000000,
    NM_802_11_AP_FLAGS_PRIVACY = 0x00000001,
    NM_802_11_AP_FLAGS_WPS     = 0x00000002,
    NM_802_11_AP_FLAGS_WPS_PBC = 0x00000004,
    NM_802_11_AP_FLAGS_WPS_PIN = 0x00000008,
};

using namespace nm;

AccessPoint::AccessPoint(const ObjectPath& path)
    : DBusObject(path)
    , m_proxy(path)
{}

uint32_t AccessPoint::strength()
{
    SAFETY_FIRST_BEGIN
    return m_proxy->Strength.get();
    SAFETY_FIRST_END
    return 0;
}

std::string AccessPoint::ssid()
{
    SAFETY_FIRST_BEGIN
    auto raw = m_proxy->Ssid.get();
    raw.push_back('\0');
    return (const char*)(raw.data());
    SAFETY_FIRST_END
    return "";
}

std::string AccessPoint::bssid()
{
    SAFETY_FIRST_BEGIN
    return m_proxy->HwAddress.get();
    SAFETY_FIRST_END
    return "";
}

Security AccessPoint::security()
{
    SAFETY_FIRST_BEGIN

    auto flags = m_proxy->Flags.get();
    auto wpa_flags = m_proxy->WpaFlags.get();
    auto rsn_flags = m_proxy->RsnFlags.get();

    if ((flags & (uint32_t) NM80211ApFlags::NM_802_11_AP_FLAGS_PRIVACY) &&
        ((NM80211ApSecurityFlags) wpa_flags == NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE) &&
        ((NM80211ApSecurityFlags) rsn_flags == NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE)) {
        return Security::WEP;
    }

    if ((NM80211ApSecurityFlags) wpa_flags != NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE) {
        return Security::WPA;
    }

    if ((NM80211ApSecurityFlags) rsn_flags != NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE) {
        return Security::WPA2;
    }

    if ((wpa_flags & (uint32_t) NM80211ApSecurityFlags::NM_802_11_AP_SEC_KEY_MGMT_802_1X) ||
        (rsn_flags & (uint32_t) NM80211ApSecurityFlags::NM_802_11_AP_SEC_KEY_MGMT_802_1X)) {
        return Security::Enterprise;
    }
    SAFETY_FIRST_END
    return Security::Unknown;
}

bool AccessPoint::encrypted()
{
    SAFETY_FIRST_BEGIN
    auto flags = m_proxy->Flags.get();
    auto wpa_flags = (NM80211ApSecurityFlags) m_proxy->WpaFlags.get();
    auto rsn_flags = (NM80211ApSecurityFlags) m_proxy->RsnFlags.get();

    return  !(flags & (uint32_t) NM80211ApFlags::NM_802_11_AP_FLAGS_PRIVACY) &&
            (wpa_flags != NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE) &&
            (rsn_flags != NM80211ApSecurityFlags::NM_802_11_AP_SEC_NONE);

    SAFETY_FIRST_END
    return false;
}