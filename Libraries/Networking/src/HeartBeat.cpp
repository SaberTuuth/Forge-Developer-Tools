
#include "HeartBeat.h"

HeartBeat::HeartBeat() {
	Reset();
}

void HeartBeat::Reset() {
	lastReceived = std::chrono::steady_clock::now();
	lastSent = std::chrono::steady_clock::now();
}

bool HeartBeat::IsExpired(float timeoutSeconds) const {
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - lastReceived).count();
	return elapsed > timeoutSeconds;
}

bool HeartBeat::ShouldSend(float intervalSeconds) const {
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - lastSent).count();
	return elapsed > intervalSeconds;
}