#include "Bloom.h"
#include <glad/glad.h>
#include <iostream>

Bloom::Bloom(const glm::vec2 &windowDim) {
    m_activated = true;
    m_intensity = 0.4F;

    glGenFramebuffers(1, &m_hdrFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFrameBuffer);


    glGenTextures(2, m_sceneTextures);
    for (unsigned int i = 0; i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, m_sceneTextures[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, windowDim.x, windowDim.y, 0, GL_RGBA, GL_FLOAT, nullptr
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_sceneTextures[i], 0);
    }

    m_scene[0] = GL_COLOR_ATTACHMENT0;
    m_scene[1] = GL_COLOR_ATTACHMENT1;
    glDrawBuffers(2, m_scene);


    glGenRenderbuffers(1, &m_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowDim.x, windowDim.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glGenFramebuffers(2, m_pingpongFBO);
    glGenTextures(2, m_pingPongTextures);
    for (unsigned int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, m_pingPongTextures[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, windowDim.x, windowDim.y, 0, GL_RGBA, GL_FLOAT, nullptr
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pingPongTextures[i], 0
        );
    }

    m_blurShader = new VertexFragmentShader("../src/shaders/blur_vs.glsl", "../src/shaders/blur_fs.glsl");
    m_blurShader->use();
    m_blurShader->setInt("image", 0);
}


Bloom::~Bloom() {
    delete m_blurShader;
}

void Bloom::useFrameBuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFrameBuffer);
}


unsigned int Bloom::getNormalScene() const {
    return m_sceneTextures[0];
}

unsigned int Bloom::getBrightPointsScene() const {
    return m_sceneTextures[1];
}


unsigned int Bloom::getPingPongTexture(const unsigned int pos) const {
    return m_pingPongTextures[pos];
}

float Bloom::getIntensity() const {
    return m_intensity;
}

bool Bloom::isActivated() const {
    return m_activated;
}

void Bloom::bindPingPongBuffer(const unsigned int pos) const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[pos]);
}

VertexFragmentShader *Bloom::getBlurShader() const {
    return m_blurShader;
}

void Bloom::setIsActive(const bool active) {
    m_activated = active;
}

void Bloom::setIntensity(float newIntensity) {
    m_intensity = newIntensity;
}
