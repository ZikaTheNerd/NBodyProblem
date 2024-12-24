#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <ostream>

#include "Particle.h"

class ParticleSystem {
public:
    explicit ParticleSystem(const std::vector<Particle> &particles);

    explicit ParticleSystem(ParticleSystem *other);

    void updateParticlePosition(unsigned int particleId, float deltaTime) const;

    unsigned int size() const;

    glm::vec4 *getPositions() const;

    glm::vec4 *getVelocities() const;

    glm::vec4 *getAccelerations() const;

    glm::vec4 *getMasses() const;

    glm::vec4 *getForces() const;

    void setMasses(glm::vec4 *newMasses);

    void setPositions(glm::vec4 *newPositions);

    void setAccelerations(glm::vec4 *newAccelerations);

    void setVelocities(glm::vec4 *newVelocities);

    friend std::ostream &operator<<(std::ostream &os, const ParticleSystem &system);

protected:
    unsigned int m_numParticles;
    glm::vec4 *m_positions;
    glm::vec4 *m_accelerations;
    glm::vec4 *m_velocities;
    glm::vec4 *m_masses;
    glm::vec4 *m_forces;

    // Declare ParticleSimulation as a friend class
    friend class ParticleSimulation;
};
