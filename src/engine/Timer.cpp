#include "engine/Timer.h"
#include <cmath>
#include <limits>

Timer::Timer(bool play) {
    time = 0.f;
    if(play) Start();
}

Timer::~Timer() {}

void Timer::Start() {
    isRunning = true;
}

void Timer::Stop() {
    isRunning = false;
}

void Timer::Restart() {
    time = 0.f;
}

void Timer::Update(float dt) {
    if(!isRunning) return;

    auto limitf = std::numeric_limits<float>::max();
    time = std::fmod(time+dt, limitf);
}

float Timer::GetTime() {
    return time;
}