#pragma once

#include "noncopyable.h"
#include <functional>  
#include "Timestamp.h"
#include <memory>
//为了不暴露更多的信息；不要包含头文件
class EventLoop
class Timestamp
/*
* Channel 理解为通道，封装了socketfd 和其感兴趣的event，如EPOLLIN，EPOLLOUT事件
* 还绑定了poller返回的具体事件
*/
class Channel: noncopyable
{
public:
	using EventCallback = std::function<void()>;
	using ReadEventCallback = std::function<void(Timestamp)>;
	Channel(EventLoop *loop，int fd);
	~Channel();

	//fd得到poll通知后，处理事件的
	void handleEvent(Timestamp receiveTime);
	//设置回调函数对象
	void setReadCallback(ReadEventCallback cb) { readCallback = std:; move(cb); }
	void setWriteCallback(EventCallback cb) { writeCallback = std:; move(cb); }
	void setCloseCallback(EventCallback cb) { closeCallback = std:; move(cb); }
	void setErrorCallback(EventCallback cb) { errorCallback = std:; move(cb); }

	//防止当channel 被手动remove 掉 channel还在执行回调操作
	void tie(const std::shared_ptr<void>&);

	int fd() const { return fd_; }
	int events() const { return events_; }
	//对外提供接口设置 ，思考为什么？
	int set_revent(int revt) { revents_ = revt; }
	bool isNoneEnvent() const { return events_ == kNoneEvent; }

private:
	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventLoop *loop_; //事件循环
	const int fg_; //fd,poller 监听的对象
	int events_; //注册fd感兴趣的事件
	int revents_; // poller返回的具体发生的事件
	int index_;
	// 弱智能指针
	std::weak_ptr<void> tie_;
	bool tied_;

	//因为channel 通道里面能够获知fd最终发生的具体的事件，所以它负责调用具体事件的回调操作
	ReadEventCallback readCallback;
	EventCallback writeCallback;
	EventCallback closeCallback;
	EventCallback errorCallback;

};

