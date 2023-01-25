#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * A class that listen to mouse clicks and run a function when a click is 
 * detected. good for the `HorizontalWindow` class.
 * this class is an abstract class, and should be inherited from.
 * the `on_click` function should be overridden.
 * the `on_hover` function should be overridden.
 * 
 */
class SubWindow
{
public:
    /**
     * what to do when the mouse is clicked.
     * @param position the relative position of the mouse click 
     *                 (or {-1,-1} if the mouse not in the sub-window).
     *                 
     * @return is the window needs to be redrawn.
     */
    virtual bool on_click(sf::Vector2f position);

    /**
     * what to do when the mouse is hovered.
     * @param position the relative position of the mouse.
     *                (or {-1,-1} if the mouse not in the sub-window).
     * @return is the window needs to be redrawn.
     */
    virtual bool on_hover(sf::Vector2f position);

    /**
     * Destructor (if needed, (its an abstract class)).
     */
    virtual ~SubWindow() = default;

    /**
     * draw the sub window.
     * @param draw_function a function that draw a drawable object.
     * the drawable object that is drawn need to be transformed by the 
     * transformable object.
     */
    virtual 
    void draw(std::function<void(sf::Drawable &, sf::Transformable &)>) = 0;
};