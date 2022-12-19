#pragma once

class Timer {
public:
    Timer() {}

    void Update(float dt) { mTime += dt; }

    void Restart() { mTime = 0; }

    float Get() { return mTime; }

private:
    float mTime = 0;
};