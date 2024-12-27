#pragma once

#include "Window.h";

class RenderTimer {
public:
    RenderTimer();

    RenderTimer(bool showFPS, bool vSync);

    void setDeltaTime(double time);

    double getDeltaTime() const;

    void updateTime(Window &window, bool paused);

    void printFinalStats() const;

    double getTotalElapsedTime() const;

    int getIteration() const;

private:
    double m_deltaTime;
    bool m_showFPS;
    double m_previousTime;
    size_t m_frameCount;
    size_t m_totalIterations;
    double m_totalElapsedTime;
    double m_lastFrameTime;

    void updateFPS(Window &window);

    void updateDeltaTime(bool paused);
};
