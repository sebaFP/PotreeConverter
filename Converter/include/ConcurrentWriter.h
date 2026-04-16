
#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <atomic>

#include "unsuck/unsuck.hpp"
#include "converter_utils.h"

using std::shared_ptr;
using std::string;
using std::fstream;
using std::ios;

// Synchronous ConcurrentWriter for Emscripten/WASM: flushes data immediately,
// no threads created.
struct ConcurrentWriter {

	std::atomic<int64_t> writtenBytes = 0;

	ConcurrentWriter(size_t numThreads, State& state) {}

	~ConcurrentWriter() {}

	void waitUntilMemoryBelow(int64_t maxMegabytesOutstanding) {}

	void write(string path, shared_ptr<Buffer> data) {
		fstream fout;
		fout.open(path, ios::out | ios::app | ios::binary);
		fout.write(data->data_char, data->size);
		fout.close();
		writtenBytes += data->size;
	}

	void join() {}
};
