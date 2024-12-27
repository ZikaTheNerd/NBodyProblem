#include "RenderLoop.h"

RenderLoop::RenderLoop(const Window &win, bool showFps, bool vSync) : m_window(win),
                                                                      m_renderTimer(RenderTimer(showFps, vSync)),
                                                                      m_pauseSimulation(true) {
}

RenderLoop::RenderLoop() = default;

void RenderLoop::runLoop(ParticleSimulation *particleSimulation) {
    while (!glfwWindowShouldClose(m_window.getWindow())) {
        m_renderTimer.updateTime(m_window, m_pauseSimulation);

        if (!m_pauseSimulation) {
            particleSimulation->update();
        }

        particleSimulation->draw();

        // ======================
        // Swap buffers: Front buffer(render) and back buffer (next render)
        glfwSwapBuffers(m_window.getWindow());
        // ======================

        // ======================
        // Checks if any events are triggered (keys pressed/released, mouse moved etc.) and calls the corresponding functions
        glfwPollEvents();
        // ======================
    }
}

void RenderLoop::setPauseSimulation(bool pause) {
    m_pauseSimulation = pause;
}

bool RenderLoop::getPauseSimulation() {
    return m_pauseSimulation;
}

int RenderLoop::getIteration() {
    return m_renderTimer.getIteration();
}


RenderLoop::~RenderLoop() {
    m_renderTimer.printFinalStats();
}
