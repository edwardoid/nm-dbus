#include "nmdbus/Dispatcher.h"

using namespace nm;

Dispatcher::Dispatcher()
    : m_dispatcher("bus:system")
{}

Dispatcher::~Dispatcher()
{

    m_dispatcher.stop();
}

simppl::dbus::Dispatcher& Dispatcher::dispatcher()
{
    static Dispatcher instance;
    return instance.m_dispatcher;
}