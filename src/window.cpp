#include <SFML/Graphics.hpp>
#include "window.hpp"

const sf::Time Window::maxFrameTime = sf::seconds(1.0f / 240.0f);

Window::Window(const sf::String& title) 
: sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), title) {

    fpsTextFont.loadFromFile("static/ttf/Arial.ttf");
    fpsText.setFont(fpsTextFont);
    fpsText.setCharacterSize(20);
    fpsText.setOutlineColor(sf::Color::Black);
    fpsText.setOutlineThickness(0.5);
    fpsText.setFillColor(sf::Color::Green);
}

float Window::calculateDelta() {

    sf::sleep(maxFrameTime - fpsClock.getElapsedTime());
    deltaTime = fpsClock.restart();
    fpsText.setString(std::to_string(static_cast<int>(
        1000000.0f/deltaTime.asMicroseconds())));
    return deltaTime.asSeconds();
}

void Window::drawFPS() {

    this->draw(fpsText);
}