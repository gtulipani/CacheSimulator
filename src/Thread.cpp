#include "Thread.h"

Thread::Thread() = default;

void Thread::start() {
	thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	thread.join();
}

Thread::~Thread() = default;

Thread::Thread(Thread &&other) noexcept {
	this->thread = std::move(other.thread);
}

Thread &Thread::operator=(Thread &&other) noexcept {
	this->thread = std::move(other.thread);
	return *this;
}
