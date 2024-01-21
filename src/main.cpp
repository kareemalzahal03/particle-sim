// © 2024 KAREEM ALZAHAL

#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "particlesim.hpp"

int main()
{
    Window window("Particles");
    ParticleSimulator particlesim(window);

    while (window.isOpen()) {

        float delta = window.calculateDelta();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Run Logic
        particlesim.simStep(delta);

        // Draw
        window.clear(sf::Color::Black);

        particlesim.drawParticles();
        window.drawFPS();
        
        window.display();
    }

    return 0;
}