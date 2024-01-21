#pragma once
#include "particle.hpp"
#include <vector>

class ParticleManager {
public:

    ParticleManager(int screenWidth, int screenHeight, int boxSize);

    void addParticle(Particle particle);

    template <typename Lambda>
    void iterateAllParticles(const Lambda& lambda);

    template <typename Lambda>
    void iterateCloseParticles(Particle& p, const Lambda& lambda);

    void fixParticlePositions();

private:
    
    const int boxSize;
    const int gridWidth;
    const int gridHeight;

    std::vector<Particle> particles;
    std::vector<int> headIndecies;

    int getGridID(Particle& p);

    template <typename Lambda>
    void iterateOverGrid(int gridID, const Lambda& lambda);
};

template <typename Lambda>
void ParticleManager::iterateAllParticles(const Lambda& lambda) {

    for (Particle& particle : particles) {
        lambda(particle);
    }
}

template <typename Lambda>
void ParticleManager::iterateCloseParticles(Particle& p, const Lambda& lambda) {

    int x = std::min(gridWidth-1,static_cast<int>(p.getPosition().x)/boxSize);
    int y = std::min(gridHeight-1,static_cast<int>(p.getPosition().y)/boxSize);

    int x_dir = 1 - 2 * (static_cast<int>(p.getPosition().x) % boxSize < boxSize/2);
    int y_dir = 1 - 2 * (static_cast<int>(p.getPosition().y) % boxSize < boxSize/2);

    bool add_x = ((0 <= x + x_dir) and (x + x_dir <= gridWidth - 1));
    bool add_y = ((0 <= y + y_dir) and (y + y_dir <= gridHeight - 1));

    iterateOverGrid(y * gridWidth + x, lambda);
    if (add_x) { iterateOverGrid(y * gridWidth + (x + x_dir), lambda); }
    if (add_y) { iterateOverGrid((y + y_dir) * gridWidth + x, lambda); }
    if (add_y and add_x) { iterateOverGrid((y + y_dir) * gridWidth + (x + x_dir), lambda); }         
}

template <typename Lambda>
void ParticleManager::iterateOverGrid(int gridID, const Lambda& lambda) {

    int currIndex = headIndecies[gridID];

    while (currIndex != -1) {

        lambda(particles[currIndex]);
        currIndex = particles[currIndex].next;
    }
}