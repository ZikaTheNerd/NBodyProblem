#include <glm/glm.hpp>

#ifndef N_BODY_CAMERA_H
#define N_BODY_CAMERA_H

class Camera {
public:
    // Konstruktor, postavlja podrazumevane vrednosti za kameru
    Camera(glm::vec2 window, glm::vec3 worldDim);

    // Seter za odnos visine i duzine prozora
    void setAspectRatio(glm::vec2 window);

    // Geter za model view projection matricu
    glm::mat4 getModelViewProjection() const;

    // Zoom in/Zoom out
    void zoomCallback(float mouseWheelYOffset);

    // Rotacija kamere prema kretanju misa
    void rotateCallback(glm::vec2 mousePos);

    void setIsDragging(bool dragging);

    void setPreviousMousePos(glm::vec2 prevPos);

    glm::vec3 getPosition();
private:
    glm::vec3 worldDimensions;
    glm::vec3 position;
    glm::vec3 worldCenter;
    glm::vec3 up;
    float sensitivity;
    float fov;
    float aspectRatio;
    float nearClipPlane;
    float farClipPlane;
    bool isDragging;     // Da li mis vuce kameru
    glm::vec2 prevMousePos;     // Prethodna pozicija misa

    // Geter za view matricu
    glm::mat4 getViewMatrix() const;

    // Geter za matricu projektovanja.
    glm::mat4 getProjectionMatrix() const;

    // Geter za model matricu
    glm::mat4 getModelMatrix() const;

};

#endif //N_BODY_CAMERA_H