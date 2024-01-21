#include <SFML/Graphics.hpp>
#include <cmath>
#include "mathfunctions.hpp"

const int numParticles = 1000;
const int smoothingRadius = 30;
const float mass = 1;
const float targetDensity =  0;
const float pressureMultiplier = 100.0f;

const float SpikyPow2ScalingFactor = 6 / (M_PI * std::pow(smoothingRadius, 4));
const float SpikyPow2DerivativeScalingFactor = - 12 / (M_PI * std::pow(smoothingRadius, 4));

float SpikyKernelPow2(float dst) {

    if (dst > smoothingRadius) { return 0; }

    float v = smoothingRadius - dst;
    return v * v * SpikyPow2ScalingFactor;
}

float DerivativeSpikyPow2(float dst) {

    if (dst > smoothingRadius) { return 0; }

    float v = smoothingRadius - dst;
    return v * SpikyPow2DerivativeScalingFactor;
}

float DensityToPressure(float density) {

    return (density - targetDensity) * pressureMultiplier;
}

float SharedPressure(float density1, float density2) {

    return (DensityToPressure(density1) + DensityToPressure(density2)) / 2;
}

float Magnitude(sf::Vector2f v) {

    return std::sqrt(v.x*v.x+v.y*v.y);
}

sf::Vector2f Unit(sf::Vector2f v) {
    
    float mag = Magnitude(v);
    if (mag == 0) {return sf::Vector2f(0,0);}
    return v / mag;
}