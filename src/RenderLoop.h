#pragma once

#include "Window.h"
#include "ParticleSimulation.h"
#include "RenderTimer.h"

class RenderLoop {
public:
    RenderLoop();

    RenderLoop(const Window &win, bool showFps, bool vSync);

    void runLoop(ParticleSimulation *particleSimulation);

    void setPauseSimulation(bool pause);

    bool getPauseSimulation();

    int getIteration();

    ~RenderLoop();

private:
    Window m_window;
    RenderTimer m_renderTimer;
    bool m_pauseSimulation;
};
