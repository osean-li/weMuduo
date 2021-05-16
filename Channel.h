#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <functional>
#include <memory>

class EventLoop;

/**
 * �����  EventLoop��Channel��Poller֮��Ĺ�ϵ   ��= Reactorģ���϶�Ӧ Demultiplex
 * Channel ���Ϊͨ������װ��sockfd�������Ȥ��event����EPOLLIN��EPOLLOUT�¼�
 * ������poller���صľ����¼�
 */
class Channel : noncopyable
{
public:
	using EventCallback = std::function<void()>;
	using ReadEventCallback = std::function<void(Timestamp)>;

	Channel(EventLoop *loop, int fd);
	~Channel();

	// fd�õ�poller֪ͨ�Ժ󣬴����¼���
	void handleEvent(Timestamp receiveTime);

	// ���ûص���������
	void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
	void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
	void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
	void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

	// ��ֹ��channel���ֶ�remove����channel����ִ�лص�����
	void tie(const std::shared_ptr<void>&);

	int fd() const { return fd_; }
	int events() const { return events_; }
	int set_revents(int revt) { revents_ = revt; }

	// ����fd��Ӧ���¼�״̬
	void enableReading() { events_ |= kReadEvent; update(); }
	void disableReading() { events_ &= ~kReadEvent; update(); }
	void enableWriting() { events_ |= kWriteEvent; update(); }
	void disableWriting() { events_ &= ~kWriteEvent; update(); }
	void disableAll() { events_ = kNoneEvent; update(); }

	// ����fd��ǰ���¼�״̬
	bool isNoneEvent() const { return events_ == kNoneEvent; }
	bool isWriting() const { return events_ & kWriteEvent; }
	bool isReading() const { return events_ & kReadEvent; }

	int index() { return index_; }
	void set_index(int idx) { index_ = idx; }

	// one loop per thread
	EventLoop* ownerLoop() { return loop_; }
	void remove();
private:

	void update();
	void handleEventWithGuard(Timestamp receiveTime);

	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	EventLoop *loop_; // �¼�ѭ��
	const int fd_;    // fd, Poller�����Ķ���
	int events_; // ע��fd����Ȥ���¼�
	int revents_; // poller���صľ��巢�����¼�
	int index_;

	std::weak_ptr<void> tie_;
	bool tied_;

	// ��Ϊchannelͨ�������ܹ���֪fd���շ����ľ�����¼�revents��������������þ����¼��Ļص�����
	ReadEventCallback readCallback_;
	EventCallback writeCallback_;
	EventCallback closeCallback_;
	EventCallback errorCallback_;
};

