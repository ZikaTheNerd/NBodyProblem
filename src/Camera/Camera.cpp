
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

//====================================================
// Konstructor
//====================================================

/**
 * Konstruktor, postavlja podrazumevane vrednosti za kameru
 * @param window
 * @param worldDim
 */
Camera::Camera(glm::vec2 window, glm::vec3 worldDim) {
    this->worldDimensions = worldDim;
    this->isDragging = false;
    this->prevMousePos = glm::vec2(0.0f);

    // Pocetna pozicija kamere u 3D prostoru
    this->position = glm::vec3(worldDimensions.x / 2.0f, worldDimensions.y / 2.0f, (this->worldDimensions.x + this->worldDimensions.y + this->worldDimensions.z) / 2.f);

    // Centar prostora na koji kamera gleda
    this->worldCenter = glm::vec3(worldDimensions.x / 2.0f, worldDimensions.y / 2.0f, worldDimensions.z / 2.f);

    // Vektor ka gore, sluzi za definisanje orjentacije kamere
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Senzitivnost kamere na pomeraj misa
    this->sensitivity = 0.005f;

    // Ugao vidljivosti kamere izrazen u stepenima
    this->fov = 90.0f;

    // Odnos visine i sirine pogleda kamere
    this->aspectRatio = static_cast<float>(window.x) / static_cast<float>(window.y);

    // Distanca od kamere do near clipping plane-a, sluzi da sakrije objekte koji su preblizu
    this->nearClipPlane = 0.1f;

    // Distanca od kamere do far clipping plane, sluzi da sakrije objekte koji su predaleko
    this->farClipPlane = worldDimensions.z * 100.0f;
}
//====================================================


//====================================================
// Seteri
//====================================================

/**
 * Seter za odnos visine i duzine prozora
 * @param winWidth
 * @param winHeight
 */
void Camera::setAspectRatio(glm::vec2 window) {
    this->aspectRatio = static_cast<float>(window.x) / static_cast<float>(window.y);
}

/**
 * Seter za isDragging (poziva se kada korisnik klikne ili pusti levo dugme na misu)
 * @param dragging
 */
void Camera::setIsDragging(bool dragging) {
    this->isDragging = dragging;
}

/**
 * Seter za prethodnu poziciju misa (poziva se kada korisnik klikne)
 * @param prevPos
 */
void Camera::setPreviousMousePos(glm::vec2 prevPos) {
    this->prevMousePos = prevPos;
}
//====================================================


//====================================================
// Geteri
//====================================================

/**
 * Get the view matrix == Camera
 * @return
 */
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(this->position, this->worldCenter, this->up);
}

/**
 * Geter za matricu projektovanja.
 * @return
 */
glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearClipPlane, this->farClipPlane);
}

/**
 * Geter za model matricu
 * @return
 */
glm::mat4 Camera::getModelMatrix() const{
    return glm::mat4(1.f);
}

/**
 * Geter za the model view projection matricu
 * @return
 */
glm::mat4 Camera::getModelViewProjection() const {
    return this->getProjectionMatrix() * this->getViewMatrix() * this->getModelMatrix();
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

//====================================================


//====================================================
// Callback functions - funkcije koje se prosledjuju drugima kao argument kako bi se pozivale unutar njih
//====================================================

/**
 * Zoom in i zoom out kamere
 * @param mouseWheelYOffset
 */
void Camera::zoomCallback(float mouseWheelYOffset) {

    this->fov -= (float)mouseWheelYOffset;
    if (this->fov < 1.0f){
        this->fov = 1.0f;
    }
    if (this->fov > 100.0f){
        this->fov = 100.0f;
    }


    // Definise dimenzije novog sveta u odnosu na pomeraj MouseWheel-a
    const float zoomFactor = 1.0f + mouseWheelYOffset * 0.1f;
    glm::vec3 newWorldDimensions = this->worldDimensions * zoomFactor;

    // Definise brzinu kamere u odnosu na odnos izmedju dimenzija novog i starog sveta
    const float cameraSpeed = 0.04f * glm::length(newWorldDimensions) / glm::length(this->worldDimensions);

    // Menja poziciju kamere prema pomeraju MouseWheel-a i brzine kamere
    if (mouseWheelYOffset > 0.f) {
        // Zoom in
        // Menja poziciju kamere blize centru
        this->position += cameraSpeed * (this->worldCenter - this->position);
    } else {
        // Zoom out
        // Menja poziciju kamere dalje od centra
        this->position -= cameraSpeed * (this->worldCenter - this->position);
    }

    // Menja near i far clip plane-ove na osnovu pozicije kamere
    float distanceToCenter = glm::distance(this->position, this->worldCenter+this->worldCenter*3.f);
    //this->nearClipPlane = distanceToCenter * 0.001f;
    this->farClipPlane = distanceToCenter * 3.f;

    // Menja dimenzije sveta
    this->worldDimensions = newWorldDimensions;
}

/**
 * Rotira kameru zavismo od prevlacenja misem
 * @param mousePos
 */
void Camera::rotateCallback(glm::vec2 mousePos) {
    if (!isDragging) {
        // Korisnik ne prevlaci
        return;
    }

    // Racuna promenu pozicije misa
    glm::vec2 delta = glm::vec2(mousePos.x, mousePos.y) - this->prevMousePos;
    this->prevMousePos = glm::vec2(mousePos.x, mousePos.y);

    // Racuna ugao rotacije
    float pitch = delta.y * this->sensitivity;
    float yaw = -delta.x * this->sensitivity;

    // Racuna vektor pravca i desni vektor
    glm::vec3 direction = glm::normalize(worldCenter - position);
    glm::vec3 right = glm::normalize(glm::cross(direction, up));

    // Rotira oko vektora ka gore - to je vektor koji pokazuje na gore, ne rotira na gore
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, up);
    direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    right = glm::normalize(glm::cross(direction, up));
    rotation = glm::rotate(glm::mat4(1.0f), pitch, right);
    direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));

    // Menja poziciju kamere i centar sveta
    position = worldCenter - direction * glm::length(worldCenter - position);
    up = glm::normalize(glm::cross(right, direction));
}
