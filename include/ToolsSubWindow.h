#pragma once

#include "SubWindow.h"
#include "GameObject.h"
#include <functional>
#include "Button.h"

/**
 * the const of number of buttons of characters in one row
 */
const int NUM_IN_ROW = 3;

/**
 * the sub window that contains the buttons of the characters.
 *
 */
class ToolsSubWindow : public SubWindow
{
public:
    /**
     * Constructor.
     * @param sub_window_size the size of the sub window.
     * @param game_objects the game objects that exists.
     * @param set_char the function that sets the current char.
     * @param start_new the function that starts a new board.
     * @param save the function that saves the board.
     */
    ToolsSubWindow(sf::Vector2f sub_window_size,
        std::vector<GameObject> game_objects,
        std::function<void(char)> set_char,
        std::vector<Button> buttons_vector);

    /**
     * draw the sub window.
     */
    virtual void
    draw(std::function<void(sf::Drawable &, sf::Transformable &)>) override;

    /**
     * handle the event.
     * @param position the position of the mouse in the sub window.
     * @return true if need to redraw, false otherwise.
     */
    virtual bool on_click(sf::Vector2f position) override;

private:
    /**
     * the size of the sub window.
     */
    sf::Vector2f m_sub_window_size;
    /**
     * the game objects that exists.
     */
    std::vector<GameObject> m_game_objects;
    /**
     * the function that sets the current char.
     */
    std::function<void(char)> m_set_char;
    /**
     * the function that starts a new board.
     */
	std::vector <Button> m_buttons_vector;
    /**
     * the current char that is selected.
     */
    char m_current_char;
};