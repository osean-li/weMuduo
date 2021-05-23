//
// Created by HW on 2021/5/16.
//

#ifndef WEMUDUO_CURRENTTHREAD_H
#define WEMUDUO_CURRENTTHREAD_H


#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread
{
    extern __thread int t_cachedTid;

    void cacheTid();

    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }
}

#endif //WEMUDUO_CURRENTTHREAD_H
