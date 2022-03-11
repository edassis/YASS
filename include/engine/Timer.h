#ifndef __TIMER_H_
#define __TIMER_H_

class Timer {
    private:
        float time;
        bool isRunning;

    public:
        Timer(bool play = true);
        ~Timer();

        float GetTime();
        void Start();
        void Stop();
        void Restart();
        void Update(float dt);
};

#endif