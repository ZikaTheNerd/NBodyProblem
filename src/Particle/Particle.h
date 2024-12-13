#include <glm/glm.hpp>
#include <ostream>

#ifndef N_BODY_PARTICLE_H
#define N_BODY_PARTICLE_H


class Particle {
public:
    glm::vec4 position; //4 dimenzije jer je takav standard u grafickom programiranju zbog matrica transformacije
    glm::vec4 velocity; 
    glm::vec4 acceleration;  
    float mass;             
    Particle();
    Particle(glm::vec3 pos, glm::vec3 vel, float mass);
    Particle(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc, float mass);
    ~Particle();

    void setVelocity(glm::vec3 vel);

    //Da li ima smisla da ovde bude friend kada klasa nema private polja?
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
};


#endif //N_BODY_PARTICLE_H