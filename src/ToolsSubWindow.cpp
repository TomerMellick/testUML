#include "ToolsSubWindow.h"
#include <iostream>
#include <utility>



ToolsSubWindow::ToolsSubWindow(sf::Vector2f sub_window_size,
    std::vector<GameObject> game_objects,
    std::function<void(char)> set_char,
    std::vector<Button> buttons_vector
):
    
    m_sub_window_size(sub_window_size),
    m_game_objects(std::move(game_objects)),
    m_set_char(std::move(set_char)),
    m_current_char(m_game_objects[0].m_symbol),
	m_buttons_vector(std::move(buttons_vector))
{
    m_set_char(m_current_char);
}


void ToolsSubWindow::draw(
        std::function<void(sf::Drawable &, sf::Transformable &)> draw_func)
{
    float thickness = 1;
    float wanted_width = m_sub_window_size.x / NUM_IN_ROW;
    float wanted_height = m_sub_window_size.x / NUM_IN_ROW;
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(wanted_width, wanted_height));
//    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(thickness);
    //draw the chars objects
    for (int i = 0; i < m_game_objects.size(); i++)
    {
        sf::Sprite sprite;

        if (m_current_char == m_game_objects[i].m_symbol)
        {
            rect.setFillColor(sf::Color(0, 0, 0, 50));
        }
        else
        {
            rect.setFillColor(sf::Color::Transparent);
        }
        sprite.setTexture(m_game_objects[i].m_texture_tool);
        float scale_width = (wanted_width - thickness) /
                            (float) sprite.getTextureRect().width;
        float scale_height = (wanted_height - thickness) /
                             (float) sprite.getTextureRect().height;
       
        sprite.setScale(scale_width, scale_height);

        sprite.setPosition(i % NUM_IN_ROW * wanted_width + thickness / 2,
                           i / NUM_IN_ROW * wanted_height + thickness / 2);
        rect.setPosition(i % NUM_IN_ROW * wanted_width + thickness / 2,
                         i / NUM_IN_ROW * wanted_height + thickness / 2);

        draw_func(rect, rect);
        draw_func(sprite, sprite);
    }

    for (size_t i = m_game_objects.size(); i < m_buttons_vector.size() + m_game_objects.size(); i++)
    {
        sf::Sprite sprite;


        sprite.setTexture(m_buttons_vector[i-m_game_objects.size()].m_texture);
        float scale_width = (wanted_width - thickness) /
            (float)sprite.getTextureRect().width;
       
        float scale_height = (wanted_height - thickness) /
            (float)sprite.getTextureRect().height;
        sprite.setScale(scale_width, scale_height);

        sprite.setPosition(i % NUM_IN_ROW * wanted_width + thickness / 2,
            i / NUM_IN_ROW * wanted_height + thickness / 2);
        rect.setPosition(i % NUM_IN_ROW * wanted_width + thickness / 2,
            i / NUM_IN_ROW * wanted_height + thickness / 2);

        draw_func(rect, rect);
        draw_func(sprite, sprite);


    }
}

bool ToolsSubWindow::on_click(sf::Vector2f position)
{
    if (position == sf::Vector2f(-1, -1)) // not this subWindow
    {
        return false;
    }
    int index =
            (int) (position.x / (m_sub_window_size.x / (float) NUM_IN_ROW)) +
            (int) (position.y / (m_sub_window_size.x / (float) NUM_IN_ROW)) *
            NUM_IN_ROW;
    if (index < m_game_objects.size())
    {
        if (m_current_char != m_game_objects[index].m_symbol)
        {
            m_current_char = m_game_objects[index].m_symbol;
            m_set_char(m_current_char);
            // need to redraw
            return true;
        }
    }
	index -= m_game_objects.size();
    if (index < m_buttons_vector.size())
    {
		m_buttons_vector[index].m_function();
		return true;
    }
    return false;
}