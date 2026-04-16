
#pragma once

#include <deque>
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <mutex>

using std::deque;
using std::vector;
using std::function;
using std::shared_ptr;
using std::atomic;
using std::mutex;
using std::lock_guard;

// Single-threaded TaskPool for Emscripten/WASM builds.
// Tasks are executed synchronously in addTask() — no worker threads created.
template<class Task>
class TaskPool {
public:
	size_t numThreads = 0;
	using TaskProcessorType = function<void(shared_ptr<Task>)>;
	TaskProcessorType processor;
	atomic<bool> isClosed = false;
	mutex mtx_task;

	TaskPool(size_t numThreads, TaskProcessorType processor) {
		this->numThreads = numThreads;
		this->processor = processor;
	}

	~TaskPool() {
		close();
	}

	void addTask(shared_ptr<Task> t) {
		// Execute immediately — no background threads in WASM build
		this->processor(t);
	}

	void close() {
		isClosed = true;
	}

	bool isWorkDone() {
		return true;
	}

	void waitTillEmpty() {
		// All tasks run synchronously; nothing to wait for
	}
};
