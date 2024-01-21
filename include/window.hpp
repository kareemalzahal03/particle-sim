#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#define WIDTH 500
#define HEIGHT 500

// An abstraction of the SFML window class, with added functionality for
// calculating, capping, and displaying FPS.
class Window : public sf::RenderWindow {
public:

    // Constructor
    Window(const sf::String& title);

    // To be called every iteration, returns time difference in seconds
    // between time last executed and updates the FPS text.
    float calculateDelta();

    // Draw the FPS to the top left of the screen.
    void drawFPS();

private:

    static const sf::Time maxFrameTime;
    sf::Time deltaTime;
    sf::Clock fpsClock;
    sf::Text fpsText;
    sf::Font fpsTextFont;
};