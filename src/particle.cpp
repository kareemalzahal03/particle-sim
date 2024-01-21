#include "particle.hpp"
#include "window.hpp"
#include <iostream>

const int radius = 3;

Particle::Particle() {
    
    // Set Random Position
    this->setPosition(sf::Vector2f(
        static_cast <float> (rand ()) / static_cast <float> (RAND_MAX) * WIDTH, 
        static_cast <float> (rand ()) / static_cast <float> (RAND_MAX) * HEIGHT));
    // this->setFillColor(sf::Color::Magenta);

    update();
}

std::size_t Particle::getPointCount() const {
    return 4;
}

sf::Vector2f Particle::getPoint(std::size_t index) const {
    if (index==1) {
        return sf::Vector2f(radius, -radius);
    } else if (index==2) {
        return sf::Vector2f(0,-2*radius);
    } else if (index==3) {
        return sf::Vector2f(-radius,-radius);
    }
    return sf::Vector2f(0,0);
}

void Particle::moveParticle(float delta) {
    const float collisionLoss = 0.75;
    sf::Vector2f pos = this->getPosition();
    sf::Vector2f move = delta * velocity;
    sf::Vector2f newpos = pos + move;

    if (0 > newpos.x) {
        newpos.x = -newpos.x;
        velocity.x = -collisionLoss * velocity.x;
    }

    if (0 > newpos.y) {
        newpos.y = -newpos.y;
        velocity.y = -collisionLoss * velocity.y;
    }

    if (newpos.x > WIDTH) {
        newpos.x = 2 * WIDTH - newpos.x;
        velocity.x = -collisionLoss * velocity.x;
    }

    if (newpos.y > HEIGHT) {
        newpos.y = 2 * HEIGHT - newpos.y;
        velocity.y = -collisionLoss * velocity.y;
    }

    this->setPosition(newpos);
}
