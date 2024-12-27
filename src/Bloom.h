#pragma once

#include <glm/glm.hpp>
#include "VertexFragmentShader.h"

class Bloom {
public:
    ~Bloom();

    Bloom(const glm::vec2 &windowDim);

    void useFrameBuffer() const;

    unsigned int getNormalScene() const;

    unsigned int getBrightPointsScene() const;

    unsigned int getPingPongTexture(unsigned int pos) const;

    bool isActivated() const;

    void setIsActive(const bool active);

    float getIntensity() const;

    void setIntensity(float newIntensity);

    void bindPingPongBuffer(unsigned int pos) const;

    VertexFragmentShader *getBlurShader() const;

private:
    unsigned int m_hdrFrameBuffer;
    unsigned int m_renderBuffer;
    unsigned int m_scene[2];
    unsigned int m_sceneTextures[2];
    unsigned int m_pingpongFBO[2];
    unsigned int m_pingPongTextures[2];
    float m_intensity;
    bool m_activated;
    VertexFragmentShader *m_blurShader;
};
