#include <iostream>
#include <utility>
#include "GridSubWindow.h"
/**
 * @brief Construct a new GridSubWindow object.
 *
 * @param matrix The character matrix representing the grid.
 * @param sub_window_size The size of the sub-window.
 * @param game_objects A vector of game objects to be drawn in the sub-window.
 */
GridSubWindow::GridSubWindow(const CharMatrix &matrix,
                             sf::Vector2f sub_window_size,
                             std::vector<GameObject> game_objects)
        : m_sub_window_size(sub_window_size),
          m_matrix(matrix),
          m_game_objects(std::move(game_objects)),
          m_current_position_hover(-1, -1),
          m_current_char(' '),
          m_pacman_position(-1, -1)
{// Find the position of pacman in the matrix
    for (int i = 0; i < matrix.getRows(); ++i)
    {
        for (int j = 0; j < matrix.getRows(); ++j)
        {
            if (matrix(i, j) == 'a')
            {
                m_pacman_position = sf::Vector2i(j, i);
                return;
            }

        }
    }
}
/**
 * @brief Handle a mouse click event at the given position.
 *
 * @param position The position of the mouse click.
 * @return true if the event was handled within this sub-window, false otherwise.
 */
bool GridSubWindow::on_click(sf::Vector2f position)
{
    if (position == sf::Vector2f(-1, -1)) // not this subWindow
    {
        return false;
    }

    int x = (int) (position.x /
                   (m_sub_window_size.x / (float) m_matrix.getCols()));
    int y = (int) (position.y /
                   (m_sub_window_size.y / (float) m_matrix.getRows()));

    if (m_current_char == 'a')
    {
        if(m_pacman_position.x != -1&&m_pacman_position.y != -1)
        {
            m_matrix(m_pacman_position.y, m_pacman_position.x) = ' ';

        }


        m_pacman_position = sf::Vector2i(x, y);
    }
    m_matrix(y, x) = m_current_char;
    return true;
}
/**
 * @brief Handle a mouse hover event at the given position.
 *
 * @param position The position of the mouse hover.
 * @return true if the event was handled within this sub-window, false otherwise.
 */
bool GridSubWindow::on_hover(sf::Vector2f position)
{
    if (position == sf::Vector2f(-1, -1)) // not this subWindow
    {
        if (m_current_position_hover != sf::Vector2i(-1, -1))
        {
            m_current_position_hover = sf::Vector2i(-1, -1);
            return true;
        }
        return false;
    }
    int x = (int) (position.x /
                   (m_sub_window_size.x / (float) m_matrix.getCols()));
    int y = (int) (position.y /
                   (m_sub_window_size.y / (float) m_matrix.getRows()));
    if (m_current_position_hover.x != x || m_current_position_hover.y != y)
    {
        m_current_position_hover.x = x;
        m_current_position_hover.y = y;
        return true;
    }
    return false;
}

/**
 * @brief Set the current character.
 *
 * @param current_char The current character.
 */
void GridSubWindow::set_current_char(char current_char)
{
    m_current_char = current_char;

}
/**
 * @brief Draw the GridSubWindow using the provided draw function.
 *
 * @param draw_func The function to use for drawing.
 */
void GridSubWindow::draw(
        std::function<void(sf::Drawable &, sf::Transformable &)> draw_func)
{
    float thickness = 2;
    sf::RectangleShape empty_rect(
            sf::Vector2f(
                    m_sub_window_size.x / (float) m_matrix.getCols() -
                    thickness,
                    m_sub_window_size.y / (float) m_matrix.getRows() -
                    thickness));

    empty_rect.setFillColor(sf::Color::Transparent);
    empty_rect.setOutlineColor(sf::Color::Black);
    empty_rect.setOutlineThickness(thickness);
    for (int i = 0; i < m_matrix.getRows(); i++)
    {
        for (int j = 0; j < m_matrix.getCols(); j++)
        {
            empty_rect.setPosition(sf::Vector2f(
                    (float) j * m_sub_window_size.x /
                    (float) m_matrix.getCols() + thickness / 2,
                    (float) i * m_sub_window_size.y /
                    (float) m_matrix.getRows() + thickness / 2));
            draw_func(empty_rect, empty_rect);
            for (auto &m_game_object: m_game_objects)
            {
                if (m_game_object.m_symbol == m_matrix(i, j))
                {
                    sf::Sprite sprite;
                    sprite.setTexture(m_game_object.m_texture_board);
                    float scale_width = ((float) empty_rect.getSize().x) /
                                        sprite.getTextureRect().width;
                    float scale_height = ((float) empty_rect.getSize().y) /
                                         sprite.getTextureRect().height;
                    sprite.setScale(scale_width, scale_height);
                    sprite.setPosition(empty_rect.getPosition());
                    draw_func(sprite, sprite);
                }
                if (m_current_position_hover.x == j &&
                    m_current_position_hover.y == i)
                {
                    sf::Sprite sprite;
                    for (auto &game_object: m_game_objects)
                    {
                        if (game_object.m_symbol == m_current_char)
                        {
                            sprite.setTexture(game_object.m_texture_tool);
                            break;
                        }
                    }
                    float scale_width = ((float) empty_rect.getSize().x) /
                                        sprite.getTextureRect().width;
                    float scale_height = ((float) empty_rect.getSize().y) /
                                         sprite.getTextureRect().height;
                    sprite.setScale(scale_width, scale_height);
                    sprite.setPosition(empty_rect.getPosition());
                    sprite.setColor(sf::Color(255, 255, 255, 20));
                    draw_func(sprite, sprite);
                }
            }
        }
    }
}

const CharMatrix &GridSubWindow::get_board() const
{
    return m_matrix;
}