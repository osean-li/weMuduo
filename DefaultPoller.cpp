//
// Created by HW on 2021/5/16.
//
#include "Poller.h"
#include "EPollPoller.h"

Poller* Poller::newDefaultPoller(EventLoop *loop)
{
    if(::getenv("MUDO_USE_POLL"))
    {
        return nullptr;//生产poll的实例
    }
    else
    {
        return new EPollPoller(loop);
    }
}