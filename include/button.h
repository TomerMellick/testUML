#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
/***
 * @brief A button class that can be used to create buttons
 */
struct Button
{
	Button(std::function<void()> function, const char* filename) :
		m_function(function)
	{
		m_texture.loadFromFile(filename);
	}
	// The function that will be called when the button is pressed
	std::function<void()> m_function;
    // The texture of the button
	sf::Texture m_texture;
};