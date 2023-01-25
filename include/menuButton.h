#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
class MenuButton : public sf::Drawable {
public:
    MenuButton(const std::string &textureName, std::function<void()> callback);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setPosition(sf::Vector2f position);

    sf::FloatRect getBounds();
    /***
     * check if the button is pressed
     * @param mousePos the position of the mouse
     * @return true if the button is pressed
     */
    void handleClick(int x, int y);
    /***
     * check if the muse is hovering over the button
     * @param mousePos the position of the mouse
     * @return true if the button is pressed
     */
    void handleHover(int x, int y);

    sf::Vector2f getSize();

private:
    const sf::Texture *buttonTexture_;
    //function to call when the button is pressed
    std::function<void()> callback_;
	sf::Vector2f position_;
    float m_scale;
};
