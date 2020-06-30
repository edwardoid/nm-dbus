#pragma once

#include <functional>

namespace nm
{
    template<class... Args>
    struct Signal
    {
    public:
        void connect(std::function<void(const Args&...)> slot)
        {
            m_slot = std::move(slot);
        }

        void operator() (const Args&... args)
        {
            emit(args...);
        }

        void emit(const Args&... args)
        {
            if (m_slot)
                m_slot(args...);
        }
    private:
        std::function<void(const Args&...)> m_slot;
    };
}