#pragma once

#include <map>
#include <string>
#include "converter_utils.h"

using std::map;
using std::string;

// No-op Monitor for Emscripten/WASM: no threads, no background reporting.
struct Monitor {
	bool stopRequested = false;
	State* state = nullptr;
	map<string, string> messages;

	Monitor(State* state) {
		this->state = state;
	}

	void _print() {}

	void start() {}

	void print(string key, string message) {}

	void stop() {
		stopRequested = true;
	}
};
