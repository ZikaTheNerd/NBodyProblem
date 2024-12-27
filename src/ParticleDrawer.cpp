

#include "ParticleDrawer.h"


ParticleDrawer::~ParticleDrawer() {
    delete m_renderShader;
    delete m_finalRenderShader;
    delete m_bloom;
    delete m_camera;
}

ParticleDrawer::ParticleDrawer(const glm::vec3 worldDim, glm::vec2 windowDim) {
    m_camera = new Camera(windowDim, worldDim);
    m_bloom = new Bloom(windowDim);

    m_renderShader = new VertexFragmentShader("../src/shaders/vertexShader.glsl",
                                              "../src/shaders/fragmentShader.glsl");
    m_renderShader->use();
    m_renderShader->setFloat("worldSize", glm::length(worldDim));
    m_pointSize = false;


    m_finalRenderShader = new VertexFragmentShader("../src/shaders/finalRender_vs.glsl",
                                                   "../src/shaders/finalRender_fs.glsl");
    m_finalRenderShader->use();
    m_finalRenderShader->setInt("normalScene", 0);
    m_finalRenderShader->setInt("blurScene", 1);
    m_finalRenderShader->setFloat("intensity", m_bloom->getIntensity());


    glGenVertexArrays(1, &m_screenVAO);
    glGenBuffers(1, &m_screenVBO);
    glBindVertexArray(m_screenVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_frameBufferTexture), m_frameBufferTexture, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Texture), (void *) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Texture), (void *) offsetof(Texture, texCoords));
}

void ParticleDrawer::draw(const size_t particlesCount) {
    if (!m_bloom->isActivated()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        drawNormalScene(particlesCount);
    } else {
        drawBloomScene(particlesCount);
    }
}

void ParticleDrawer::drawNormalScene(const size_t particlesCount) const {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.F, 0.F, 0.F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_renderShader->use();
    m_renderShader->setMat4("modelViewProjection", m_camera->getModelViewProjection());
    m_renderShader->setVec3("cameraPos", m_camera->getPosition());
    m_renderShader->setBool("pointSize", m_pointSize);
    glDrawArrays(GL_POINTS, 0, particlesCount);
}

void ParticleDrawer::drawBloomScene(const size_t particlesCount) const {
    m_bloom->useFrameBuffer();
    drawNormalScene(particlesCount);

    blurBrightParticles();

    combineBlurAndNormalScene();
}

void ParticleDrawer::blurBrightParticles() const {
    bool horizontal = true;
    bool first_iteration = true;
    constexpr unsigned int Amount = 2;
    m_bloom->getBlurShader()->use();
    for (unsigned int i = 0; i < Amount; i++) {
        m_bloom->bindPingPongBuffer(static_cast<unsigned int>(horizontal));
        m_bloom->getBlurShader()->setInt("horizontal", static_cast<int>(horizontal));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, first_iteration
                                         ? m_bloom->getBrightPointsScene()
                                         : m_bloom->getPingPongTexture(static_cast<unsigned int>(!horizontal)));
        glBindVertexArray(m_screenVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        horizontal = !horizontal;
        if (first_iteration) {
            first_iteration = false;
        }
    }
}

void ParticleDrawer::combineBlurAndNormalScene() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    m_finalRenderShader->use();
    m_finalRenderShader->setFloat("intensity", m_bloom->getIntensity());

    glBindVertexArray(m_screenVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_bloom->getNormalScene());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_bloom->getPingPongTexture(0U));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

Camera *ParticleDrawer::getCamera() const {
    return m_camera;
}

void ParticleDrawer::updateWindowDimension(glm::vec2 window) {
    m_camera->setAspectRatio(window);
    delete m_bloom;
    m_bloom = new Bloom(window);
}

Bloom *ParticleDrawer::getBloom() const {
    return m_bloom;
}

bool ParticleDrawer::getPointSize() const {
    return m_pointSize;
}

void ParticleDrawer::setPointSize(const bool point) {
    m_pointSize = point;
}
