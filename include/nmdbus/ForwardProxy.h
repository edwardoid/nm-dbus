#pragma once

#include <memory>

namespace nm
{
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
}
