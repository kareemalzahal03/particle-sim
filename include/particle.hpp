#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Particle : public sf::Shape {
public:

    // sf::Vector2f direction;
    sf::Vector2f oldForce;
    sf::Vector2f force;
    sf::Vector2f velocity;
    float density;
    int prev, next = -1;

    explicit Particle();

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;

    void moveParticle(float delta);

private:

    static const int radius = 3;
};