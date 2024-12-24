#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#ifndef N_BODY_WINDOW_H
#define N_BODY_WINDOW_H


class Window {
public:
    Window();

    Window(glm::vec2 window, const std::string &title);

    void updateWindowSize(const int width, const int height);

    GLFWwindow *getWindow();

    void updateWindowTitle(const std::string &title);

private:
    GLFWwindow *window;
    std::string windowTitle;
    unsigned int windowWidth, windowHeight;

    void initGlfw();

    void initGlad();

    void createWindow();
};


#endif //N_BODY_WINDOW_H
