#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "VertexFragmentShader.h"
#include "Camera.h"
#include "Bloom.h"

struct Texture {
    glm::vec3 position;
    glm::vec2 texCoords;
};

class ParticleDrawer {
public:
    ~ParticleDrawer();

    ParticleDrawer(glm::vec3 worldDim, glm::vec2 windowDim);

    void draw(size_t particlesCount);

    Camera *getCamera() const;

    void updateWindowDimension(glm::vec2 window);

    Bloom *getBloom() const;

    bool getPointSize() const;

    void setPointSize(bool point);

protected:
    GLuint m_screenVAO, m_screenVBO;
    Shader *m_renderShader, *m_finalRenderShader;
    Bloom *m_bloom;
    Camera *m_camera;
    bool m_pointSize;

    Texture m_frameBufferTexture[4] = {
        {glm::vec3(-1.0F, 1.0F, 0.0F), glm::vec2(0.0F, 1.0F)},
        {glm::vec3(-1.0F, -1.0F, 0.0F), glm::vec2(0.0F, 0.0F)},
        {glm::vec3(1.0F, 1.0F, 0.0F), glm::vec2(1.0F, 1.0F)},
        {glm::vec3(1.0F, -1.0F, 0.0F), glm::vec2(1.0F, 0.0F)}
    };

    void drawBloomScene(size_t particlesCount) const;

    void drawNormalScene(size_t particlesCount) const;

    void blurBrightParticles() const;

    void combineBlurAndNormalScene() const;
};
