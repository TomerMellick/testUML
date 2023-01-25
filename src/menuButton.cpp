#include "menuButton.h"
#include "resources.h"
MenuButton::MenuButton(const std::string &textureName,
                       std::function<void()> callback) :
        callback_(callback)
{
    buttonTexture_ = (sf::Texture *) Resources::loadResources(textureName);
    m_scale = 1.0f;


}

//------------------------------------------------------------------------------
void MenuButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sprite.setTexture(*buttonTexture_);
    sprite.setPosition(position_);
    sprite.setScale(m_scale, m_scale);
    target.draw(sprite, states);

}

//------------------------------------------------------------------------------
void MenuButton::setPosition(sf::Vector2f position)
{
    position_ = position;
}

//------------------------------------------------------------------------------
sf::FloatRect MenuButton::getBounds()
{
    sf::Sprite sprite;
    sprite.setTexture(*buttonTexture_);
    sprite.setPosition(position_);
    return sprite.getGlobalBounds();
}

//------------------------------------------------------------------------------
void MenuButton::handleClick(int x, int y)
{
    if (getBounds().contains(x, y))
    {
        callback_();
    }
}

//------------------------------------------------------------------------------
sf::Vector2f MenuButton::getSize()
{
    return sf::Vector2f(buttonTexture_->getSize().x, buttonTexture_->getSize().y);
}

//------------------------------------------------------------------------------
void MenuButton::handleHover(int x, int y)
{
    if (getBounds().contains(x, y))
    {
        m_scale = 1.2;
    }
    else
    {
        m_scale = 1;
    }
}
//------------------------------------------------------------------------------