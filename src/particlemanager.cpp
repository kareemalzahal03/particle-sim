#include "particle.hpp"
#include "particlemanager.hpp"
#include <vector>
#include <iostream>

ParticleManager::ParticleManager(int screenWidth, int screenHeight, int boxSize) 
: gridWidth(screenWidth/boxSize), gridHeight(screenHeight/boxSize), boxSize(boxSize) {

    headIndecies.resize(gridWidth*gridHeight, -1);
}

void ParticleManager::addParticle(Particle particle) {
    
    int newGridID = getGridID(particle);
    int newIndex = particles.size();

    if (headIndecies[newGridID] != -1) {
        particles[headIndecies[newGridID]].prev = newIndex;
    }

    particle.next = headIndecies[newGridID];
    particle.prev = -1;
    headIndecies[newGridID] = newIndex;
    particles.push_back(particle);
}

void ParticleManager::fixParticlePositions() {

    for (int currGridID = 0; currGridID < headIndecies.size(); currGridID++) {

        int currIndex = headIndecies[currGridID];

        while (currIndex != -1) {

            Particle& currParticle = particles[currIndex];
            int nextIndex = currParticle.next;
            int newGridID = getGridID(currParticle);

            if (currGridID != newGridID) {

                if (currParticle.prev != -1) {

                    particles[currParticle.prev].next = currParticle.next;

                } else {

                    headIndecies[currGridID] = currParticle.next;
                }

                if (currParticle.next != -1) {

                    particles[currParticle.next].prev = currParticle.prev;
                }

                // Insert currParticle to correct gridID

                if (headIndecies[newGridID] != -1) {

                    particles[headIndecies[newGridID]].prev = currIndex;
                }

                currParticle.next = headIndecies[newGridID];
                currParticle.prev = -1;
                headIndecies[newGridID] = currIndex;
            }

            currIndex = nextIndex;
        }
    }
}

int ParticleManager::getGridID(Particle& p) {

    int x = std::min(gridWidth-1,static_cast<int>(p.getPosition().x)/boxSize);
    int y = std::min(gridHeight-1,static_cast<int>(p.getPosition().y)/boxSize);
    return y * gridWidth + x; 
}
