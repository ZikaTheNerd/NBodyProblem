#include <iostream>
#include <sstream>

#include "RenderTimer.h"

RenderTimer::RenderTimer() = default;

RenderTimer::RenderTimer(const bool showFPS, const bool vSync) : m_deltaTime(0), m_showFPS(showFPS),
                                                                 m_previousTime(glfwGetTime()),
                                                                 m_frameCount(0),
                                                                 m_totalIterations(0),
                                                                 m_totalElapsedTime(0),
                                                                 m_lastFrameTime(glfwGetTime()) {
    if (!vSync) {
        // Disable Vsync
        glfwSwapInterval(0);
    }
}

double RenderTimer::getDeltaTime() const {
    return m_deltaTime;
}

void RenderTimer::setDeltaTime(const double time) {
    m_deltaTime = time;
}

void RenderTimer::updateFPS(Window &window) {
    double currentTime = glfwGetTime();
    m_frameCount++;

    double elapsedTime = currentTime - m_previousTime;

    // If elapsed time is greater than or equal to 1 second
    if (elapsedTime >= 1.0) {
        // Compute the fps and the average frame time
        double fps = m_frameCount / elapsedTime;
        double ms_per_frame = 1000.0 / fps;

        if (m_showFPS) {
            // Update the window title
            std::ostringstream title;
            title << "N-body simulation | " << ms_per_frame << " ms/frame (" << fps << " FPS)";
            window.updateWindowTitle(title.str());
        }

        // Reset for the next update
        m_previousTime = currentTime;
        m_frameCount = 0;
    }
}

void RenderTimer::updateDeltaTime(bool paused) {
    double currentTime = glfwGetTime();
    setDeltaTime(currentTime - m_lastFrameTime);
    m_lastFrameTime = currentTime;

    if (!paused) {
        m_totalElapsedTime += m_deltaTime;
        m_totalIterations += 1;
    }
}

void RenderTimer::updateTime(Window &window, bool paused) {
    updateFPS(window);
    updateDeltaTime(paused);
}

/**
 *
 *  Print the final average frame time
*/
void RenderTimer::printFinalStats() const {
    std::cout << "===============================================\n";
    std::cout << "Simulation performance stats\n";
    std::cout << "===============================================\n";


    if (m_totalIterations > 0) {
        const double averageFrameTime = m_totalElapsedTime / m_totalIterations;
        const double averageFPS = 1.0 / averageFrameTime;

        std::cout << "Total elapsed time: " << m_totalElapsedTime << " seconds" << std::endl;
        std::cout << "Average FPS: " << averageFPS << " fps" << std::endl;
        std::cout << "Average Frame Time: " << averageFrameTime * 1000 << " ms" << std::endl;
    }
    std::cout << "Total iterations: " << m_totalIterations << " iterations" << std::endl;
    std::cout << "===============================================\n";
}

int RenderTimer::getIteration() const {
    return m_totalIterations;
}

double RenderTimer::getTotalElapsedTime() const {
    return m_totalElapsedTime;
}


