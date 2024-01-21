#include <SFML/Graphics.hpp>
#include <cmath>

extern const int numParticles;
extern const int smoothingRadius;
extern const float mass;
extern const float targetDensity;
extern const float pressureMultiplier;

float SpikyKernelPow2(float dst);

float DerivativeSpikyPow2(float dst);

float DensityToPressure(float density);

float SharedPressure(float density1, float density2);

float Magnitude(sf::Vector2f v);

sf::Vector2f Unit(sf::Vector2f v);