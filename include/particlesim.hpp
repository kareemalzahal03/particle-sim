#pragma once
#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "particle.hpp"
#include "particlemanager.hpp"

class ParticleSimulator {
private:
    // static const int numParticles;
    // static const float mass;
    // static const int blurRadius;
    ParticleManager particlemanager;
    Window& window;

public:
    // Constructor to initialize the simulator
    ParticleSimulator(Window& w);

    void simStep(float delta);

    void drawParticles();

    // float magnitude(sf::Vector2f v);

    // sf::Vector2f unit(sf::Vector2f v);

    // float influence(sf::Vector2f center, sf::Vector2f point);

    // float influenceVol();

    // float influencePrime(sf::Vector2f center, sf::Vector2f point);

    // sf::Vector2f influenceGradient(sf::Vector2f center, sf::Vector2f point);

    float density(Particle& particle);

    // sf::Vector2f densityGradient(Particle& particle);

    // float densityToPressure(float density);

    // float sharedPressure(float d1, float d2);

    sf::Vector2f pressureDirection(Particle& mainParticle);
};