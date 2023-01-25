#include <iostream>
#include <SFML/Graphics.hpp>
#include "HorizontalWindow.h"

HorizontalWindow::HorizontalWindow(sf::VideoMode video_mode,
                                   const std::string &title)
        : m_window(video_mode, title)
{

}

void HorizontalWindow::add_sub_window(SubWindow *sub_window, float start_x,
                                      float end_x)
{
    m_subWindowDatas.push_back({sub_window, start_x, end_x});
}

void HorizontalWindow::run()
{
    // draw all the sub windows
    rerender();
    while (m_window.isOpen())
    {
        // the needs_redraw flag is used to know if we need to redraw the
        // window.
        // good for performance.
        bool needs_redraw = false;
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            sf::Vector2f pos;
            switch (event.type)
            {
                case sf::Event::Closed:
                    // close the window
                    m_window.close();
                    break;
                case sf::Event::MouseMoved:
                    pos = m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                    needs_redraw |= on_hover(pos);
                    break;
                case sf::Event::MouseButtonPressed:
                    // if the mouse is clicked (left click), 
                    // run the on_click function of all the sub windows.
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        pos = m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                        needs_redraw |= on_click(pos);
                    }
                    break;
                case sf::Event::MouseLeft:
                    // if the mouse is out of the window, run the on_hover 
                    // function of all the sub windows with {-1, -1}.
                    needs_redraw |= on_hover({-1, -1});
                    break;
                case sf::Event::Resized:
                    // if the window is resized, rerender the window.
                    needs_redraw = true;
                    break;
                default:
                    // add the default case to avoid warnings.
                    break;
            }
        }
        if (needs_redraw)
        {
            // if the window needs to be redrawn, rerender the window.
            rerender();
        }
    }
}

HorizontalWindow::~HorizontalWindow()
{
    // delete all the sub windows.
    for (auto sub_window_data: m_subWindowDatas)
    {
        delete sub_window_data.sub_window;
    }
}

void HorizontalWindow::rerender()
{
    // clear the window (with a good dark mode background color).
    m_window.clear(sf::Color(0x3e3e3eff));
    for (auto sub_window_data: m_subWindowDatas)
    {
        // draw each sub window.
        sub_window_data.sub_window->
                draw(
                [=](sf::Drawable &drawable, sf::Transformable &transformable)
                {
                    // set relative position
                    transformable.setPosition(
                            transformable.getPosition() +
                            sf::Vector2f(sub_window_data.start_x, 0));

                    // draw
                    m_window.draw(drawable);

                    // reset position
                    transformable.setPosition(
                            transformable.getPosition() -
                            sf::Vector2f(sub_window_data.start_x, 0));
                });
    }
    m_window.display();
}

SubWindow *HorizontalWindow::get_sub_window(int index)
{
    return m_subWindowDatas[index].sub_window;
}

bool HorizontalWindow::on_hover(sf::Vector2f location)
{
    bool needs_redraw = false;
    for (auto sub_window_data: m_subWindowDatas)
    {
        // run the on_hover function of each sub window.
        if (location.x >= sub_window_data.start_x &&
            location.x < sub_window_data.end_x)
        {
            // if the mouse is in the sub window, run the on_hover function.
            // with the relative position.
            needs_redraw |= sub_window_data.sub_window->on_hover(
                    {location.x - sub_window_data.start_x, location.y});
        }
        else
        {
            // if the mouse is not in the sub window, run the on_hover function
            // with {-1, -1}.
            needs_redraw |= sub_window_data.sub_window->on_hover({-1, -1});
        }
    }
    return needs_redraw;
}

bool HorizontalWindow::on_click(sf::Vector2f location)
{
    bool needs_redraw = false;
    for (auto sub_window_data: m_subWindowDatas)
    {
        // run the on_click function of each sub window.
        if (location.x >= sub_window_data.start_x &&
            location.x < sub_window_data.end_x)
        {
            // if the mouse is in the sub window, run the on_click function.
            // with the relative position.
            needs_redraw |= sub_window_data.sub_window->on_click(
                    {location.x - sub_window_data.start_x, location.y});
        }
        else
        {
            // if the mouse is not in the sub window, run the on_click function
            // with {-1, -1}.
            needs_redraw |= sub_window_data.sub_window->on_click({-1, -1});
        }
    }
    return needs_redraw;
}

void HorizontalWindow::close()
{
    m_window.close();
}
