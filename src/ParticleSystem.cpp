#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::vector<Particle> &particles) {
    m_numParticles = particles.size();
    m_velocities = new glm::vec4[m_numParticles]();
    m_accelerations = new glm::vec4[m_numParticles]();
    m_positions = new glm::vec4[m_numParticles]();
    m_masses = new glm::vec4[m_numParticles]();
    m_forces = new glm::vec4[m_numParticles]();

    for (int i = 0; i < m_numParticles; i++) {
        m_velocities[i] = particles[i].velocity;
        m_accelerations[i] = particles[i].acceleration;
        m_positions[i] = particles[i].position;
        m_masses[i] = glm::vec4(particles[i].mass, 0, 0, 0);
        m_forces[i] = glm::vec4(0.f);
    }
}

ParticleSystem::ParticleSystem(ParticleSystem *other) {
    m_numParticles = other->size();
    m_velocities = new glm::vec4[m_numParticles]();
    m_accelerations = new glm::vec4[m_numParticles]();
    m_positions = new glm::vec4[m_numParticles]();
    m_masses = new glm::vec4[m_numParticles]();
    m_forces = new glm::vec4[m_numParticles]();

    for (int i = 0; i < m_numParticles; i++) {
        m_velocities[i] = other->getVelocities()[i];
        m_accelerations[i] = other->getAccelerations()[i];
        m_positions[i] = other->m_positions[i];
        m_masses[i] = other->m_masses[i];
        m_forces[i] = other->m_forces[i];
    }
}


/**
 * Updates a particle position
 * Performs the leapfrog integration
 * Link: https://en.wikipedia.org/wiki/Leapfrog_integration
 * @param particleId
 * @param deltaTime
 */
void ParticleSystem::updateParticlePosition(unsigned int particleId, float deltaTime) const {
    const float dtDividedBy2 = deltaTime * 0.5f;

    // Compute velocity (i + 1/2)
    m_velocities[particleId] += m_accelerations[particleId] * dtDividedBy2;

    // Compute next position (i+1)
    m_positions[particleId] += m_velocities[particleId] * deltaTime;

    // Update acceleration (i+1)
    // F = MA;
    // A = F/M;  M is cancelled when calculating gravity force
    m_accelerations[particleId] = m_forces[particleId];

    // Compute next velocity (i+1)
    m_velocities[particleId] += m_accelerations[particleId] * dtDividedBy2;
}


unsigned int ParticleSystem::size() const {
    return m_numParticles;
}

glm::vec4 *ParticleSystem::getMasses() const {
    return m_masses;
}

glm::vec4 *ParticleSystem::getPositions() const {
    return m_positions;
}

glm::vec4 *ParticleSystem::getVelocities() const {
    return m_velocities;
}

glm::vec4 *ParticleSystem::getAccelerations() const {
    return m_accelerations;
}

glm::vec4 *ParticleSystem::getForces() const {
    return m_forces;
}

void ParticleSystem::setAccelerations(glm::vec4 *newAccelerations) {
    delete [] m_accelerations;
    m_accelerations = newAccelerations;
}

void ParticleSystem::setMasses(glm::vec4 *newMasses) {
    delete [] m_masses;
    m_masses = newMasses;
}

void ParticleSystem::setPositions(glm::vec4 *newPositions) {
    delete [] m_positions;
    m_positions = newPositions;
}

void ParticleSystem::setVelocities(glm::vec4 *newVelocities) {
    delete [] m_velocities;
    m_velocities = newVelocities;
}

std::ostream &operator<<(std::ostream &os, const ParticleSystem &system) {
    os << "Particle System with " << system.m_numParticles << " particles:" << std::endl;
    for (unsigned int i = 0; i < system.m_numParticles; ++i) {
        os << "Particle ID: " << i << std::endl;
        os << "Position: (" << system.m_positions[i].x << ", " << system.m_positions[i].y << ", " << system.m_positions[
                    i].z
                << ")" << std::endl;
        os << "Velocity: (" << system.m_velocities[i].x << ", " << system.m_velocities[i].y << ", " << system.
                m_velocities[i].
                z << ")" << std::endl;
        os << "Acceleration: (" << system.m_accelerations[i].x << ", " << system.m_accelerations[i].y << ", " << system.
                m_accelerations[i].z << ")" << std::endl;
        os << "Mass: " << system.m_masses[i].x << std::endl;
    }
    return os;
}
