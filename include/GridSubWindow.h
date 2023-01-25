#pragma once

#include "SubWindow.h"
#include "GameObject.h"
#include "CharMatrix.h"

/***
 * the class that represents the grid sub window of the game editor
 */
class GridSubWindow : public SubWindow
{
public:
    GridSubWindow(const CharMatrix &matrix,
                  sf::Vector2f sub_window_size,
                  std::vector<GameObject> game_objects);
    //used for click events
    bool on_click(sf::Vector2f position) override;
    //used for mouse move events
    bool on_hover(sf::Vector2f position) override;
    //draws the grid sub window
    void draw(std::function<void(sf::Drawable &,
                                 sf::Transformable &)> draw_func) override;
    //sets the current game object in use
    void set_current_char(char current_char);
    //returns the board in char matrix form
    const CharMatrix &get_board() const;

private:
    sf::Vector2f m_sub_window_size;
    sf::Vector2i m_current_position_hover;
    CharMatrix m_matrix;
    std::vector<GameObject> m_game_objects;
    char m_current_char;
    sf::Vector2i m_pacman_position;
};