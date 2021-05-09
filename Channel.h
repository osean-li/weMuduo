#pragma once

#include "noncopyable.h"
#include <functional>  
#include "Timestamp.h"
#include <memory>
//Ϊ�˲���¶�������Ϣ����Ҫ����ͷ�ļ�
class EventLoop
class Timestamp
/*
* Channel ���Ϊͨ������װ��socketfd �������Ȥ��event����EPOLLIN��EPOLLOUT�¼�
* ������poller���صľ����¼�
*/
class Channel: noncopyable
{
public:
	using EventCallback = std::function<void()>;
	using ReadEventCallback = std::function<void(Timestamp)>;
	Channel(EventLoop *loop��int fd);
	~Channel();

	//fd�õ�poll֪ͨ�󣬴����¼���
	void handleEvent(Timestamp receiveTime);
	//���ûص���������
	void setReadCallback(ReadEventCallback cb) { readCallback = std:; move(cb); }
	void setWriteCallback(EventCallback cb) { writeCallback = std:; move(cb); }
	void setCloseCallback(EventCallback cb) { closeCallback = std:; move(cb); }
	void setErrorCallback(EventCallback cb) { errorCallback = std:; move(cb); }

	//��ֹ��channel ���ֶ�remove �� channel����ִ�лص�����
	void tie(const std::shared_ptr<void>&);

	int fd() const { return fd_; }
	int events() const { return events_; }
	//�����ṩ�ӿ����� ��˼��Ϊʲô��
	int set_revent(int revt) { revents_ = revt; }
	bool isNoneEnvent() const { return events_ == kNoneEvent; }

private:
	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventLoop *loop_; //�¼�ѭ��
	const int fg_; //fd,poller �����Ķ���
	int events_; //ע��fd����Ȥ���¼�
	int revents_; // poller���صľ��巢�����¼�
	int index_;
	// ������ָ��
	std::weak_ptr<void> tie_;
	bool tied_;

	//��Ϊchannel ͨ�������ܹ���֪fd���շ����ľ�����¼���������������þ����¼��Ļص�����
	ReadEventCallback readCallback;
	EventCallback writeCallback;
	EventCallback closeCallback;
	EventCallback errorCallback;

};

