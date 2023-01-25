#pragma once

#include <vector>
#include "SubWindow.h"
/***
 * @brief A struct that represents a sub window
 */
struct SubWindowData
{
    SubWindow *sub_window;
    float start_x;
    float end_x;
};

/**
 * A window that can contain multiple sub windows horizontal.
 */
class HorizontalWindow
{
public:
    /**
     * run the window. (will end only when the window is closed).
     */
    void run();

protected:
    /**
     * Constructor.
     * @param video_mode the video mode of the window.
     * @param title the title of the window.
     */
    HorizontalWindow(sf::VideoMode video_mode, const std::string &title);

    /**
     * Add a sub window to the window.
     * must be allocated on the heap (the destructor will `delete` it).
     * @param sub_window the sub window to add.
     * @param start_x the start x of the sub window.
     * @param end_x the end x of the sub window.
     */
    void add_sub_window(SubWindow *sub_window, float start_x, float end_x);

    /**
     * get sub window by index.
     * @param index the index of the sub window.
     * @return the sub window.
     */
    SubWindow *get_sub_window(int index);

    /**
     * close the window.
     */
    void close();

    /**
     * Destructor.
     */
    ~HorizontalWindow();

private:
    /**
     * all the sub-windows with there start and end x.
     */
    std::vector<SubWindowData> m_subWindowDatas;

    /**
     * the window.
     */
    sf::RenderWindow m_window;

    /**
     * run the on_click function of all the sub windows (with adjusted location).
     * if the click is out of a sub window, the on_click
     * function of the sub window will be called with {-1, -1}.
     * 
     * @param position the position of the mouse.
     * @return true if the window needs to be redrawn.
     */
    bool on_click(sf::Vector2f position);
    
    /**
    * run the on_hover function of all the sub windows (with adjusted location).
    * if the click is out of a sub window, the on_click
    * function of the sub window will be called with {-1, -1}.
    * 
    * @param position the position of the mouse.
    * @return true if the window needs to be redrawn.
    */
    bool on_hover(sf::Vector2f position);

    /**
     * rerender the window.
     * ask each sub window to draw itself.
     * the positions of the sub windows shapes are adjusted to the real window.
     */
    void rerender();
};