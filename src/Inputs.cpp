#include "Inputs.h"
#include <SFML/Graphics.hpp>
#include <string>

bool get_window_size(int &cols, int &rows)
{

    sf::RenderWindow window(sf::VideoMode(200, 90), "Pacman Editor");
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    int index = 0;
    cols = 0;
    rows = 0;

    sf::RectangleShape shape(sf::Vector2f(200, 30));
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Transparent);
    
    sf::Text text("Enter", font, 20);
    text.setPosition(0, 65);
    while (window.isOpen())
    {
        window.clear(sf::Color(0x3e3e3eff));

        shape.setPosition(0, 0);
        window.draw(shape);
        shape.setPosition(0, 30);
        window.draw(shape);
        shape.setPosition(0, 60);
        window.draw(shape);
        
        window.draw(text);
        
        sf::Text text1("rows: " + std::to_string(rows), font, 20);
        text1.setPosition(0, 5);
        sf::Text text2("cols: " + std::to_string(cols), font, 20);
        text2.setPosition(0, 35);
        window.draw(text1);
        window.draw(text2);
        window.display();
        if (sf::Event event; window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return false;
                }
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (index == 1)
                    {
                        rows /= 10;
                    }
                    else if (index == 2)
                    {
                        cols /= 10;
                    }
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    window.close();
                    return true;
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= '0' && event.text.unicode <= '9')
                {
                    if (index == 1)
                    {
                        rows = rows * 10 + event.text.unicode - '0';
                    }
                    else if (index == 2)
                    {
                        cols = cols * 10 + event.text.unicode - '0';
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (event.mouseButton.y >= 0 && event.mouseButton.y <= 30)
                    {
                        index = 1;
                    }
                    else if (event.mouseButton.y >= 30 &&
                             event.mouseButton.y <= 60)
                    {
                        index = 2;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}