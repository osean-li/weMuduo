#pragma once

/*
* noncopyable 被继承以后，派生类对象可以正常的构造和析构，但是派生类对象无法进行拷贝狗改造和赋值操作
  你是否想到了使用继承的方法？
*/
class noncopyable
{
    public:
        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;
    private:
        noncopyable() = default;
        ~noncopyable() = default;

}