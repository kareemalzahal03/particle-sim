#include <SFML/Graphics.hpp>
#include <cmath>
#include "particlesim.hpp"
#include "window.hpp"
#include "particle.hpp"
#include "particlemanager.hpp"
#include <iostream>
#include "mathfunctions.hpp"

ParticleSimulator::ParticleSimulator(Window& w) 
: window(w), particlemanager(WIDTH, HEIGHT, 2*smoothingRadius) {

    for (int x = 0; x < numParticles; x++) {
        Particle p;
        particlemanager.addParticle(p);
    }
}

void ParticleSimulator::simStep(float delta) {

    particlemanager.iterateAllParticles([this](Particle& particle) {

        particle.density = density(particle);

        // float colorGradient = std::min(particle.density,2.0f)/2.0f;
        // particle.setFillColor(sf::Color(255*colorGradient,255*(1-std::abs(2*colorGradient-1)),255*(1-colorGradient)));
    });

    particlemanager.iterateAllParticles([this](Particle& particle) {

        particle.force = - pressureDirection(particle);

        const float max_speed = 100;
        float speed = Magnitude(particle.velocity);
        float colorGradient = std::min(speed,max_speed)/max_speed;
        particle.setFillColor(sf::Color(255*colorGradient,255*(1-std::abs(2*colorGradient-1)),255*(1-colorGradient)));
    });

    particlemanager.iterateAllParticles([this,&delta](Particle& particle) {
        
        // Apply gravity
        // const float gravityConst = 30;
        // particle.velocity.y += gravityConst * delta;

        // Apply pressure
        sf::Vector2f pressureAccel = particle.force / particle.density;
        particle.velocity += pressureAccel * delta;

        // Move particle and resolve collisions
        particle.moveParticle(delta);
    });

    particlemanager.fixParticlePositions();
}

void ParticleSimulator::drawParticles() {

    particlemanager.iterateAllParticles([this](Particle& particle) {

        window.draw(particle);
    });
}

float ParticleSimulator::density(Particle& particle) {
    float density = 0;

    particlemanager.iterateCloseParticles(particle,
    [this, &density, &particle] (Particle& otherParticle) {

        float dist = Magnitude(particle.getPosition() - otherParticle.getPosition());
        density += SpikyKernelPow2(dist);
    });

    return density;
}

sf::Vector2f ParticleSimulator::pressureDirection(Particle& particle) {
    sf::Vector2f pressureDirection(0, 0);

    particlemanager.iterateCloseParticles(particle,
    [this, &pressureDirection, &particle] (Particle& otherParticle) {

        float dist = Magnitude(particle.getPosition() - otherParticle.getPosition());
        sf::Vector2f dir = Unit(particle.getPosition() - otherParticle.getPosition());

        pressureDirection += dir * SharedPressure(particle.density, otherParticle.density) 
        * DerivativeSpikyPow2(dist) / otherParticle.density;
    });
    
    return pressureDirection;
}
