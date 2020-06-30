#pragma once


#include "simppl/dispatcher.h"

class Dispatcher
{
public:
    Dispatcher();
    ~Dispatcher();
    static simppl::dbus::Dispatcher& dispatcher();
private:
    simppl::dbus::Dispatcher m_dispatcher;
};