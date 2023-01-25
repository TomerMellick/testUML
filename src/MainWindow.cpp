#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <utility>
#include "MainWindow.h"
#include "GridSubWindow.h"
#include "GameObject.h"
#include "ToolsSubWindow.h"
#include <algorithm>

MainWindow::MainWindow(const CharMatrix &grid,
                       const std::vector<GameObject> &game_objects,
                       const std::function<void()> &start_new,
                       std::function<void(const CharMatrix &matrix)> save_func)
        :
// make the window
        HorizontalWindow(sf::VideoMode(std::min(std::min(CELL_WIDTH,MAX_GRID_WIDTH/grid.getRows()), MAX_GRID_HEIGHT/ grid.getCols()) * grid.getCols() + 150,
                                       std::min(std::min(CELL_WIDTH,MAX_GRID_WIDTH/grid.getRows()), MAX_GRID_HEIGHT/ grid.getCols()) * grid.getRows()),
                         "Pacman Editor"),

        // save the save function
        m_save(std::move(save_func))
{

    int cell_width = std::min(std::min(CELL_WIDTH,MAX_GRID_WIDTH/grid.getRows()), MAX_GRID_HEIGHT/ grid.getCols());
    
    // make the grid sub window
    add_sub_window(new GridSubWindow(grid,
                                     sf::Vector2f(cell_width * grid.getCols(),
                                                  cell_width * grid.getRows()),
                                     game_objects),
                   0, cell_width * grid.getCols());

    // make the tools sub window
    
    
    // make the functions for the tools sub window
    std::function<void(char)> set_char = [this](char c) {
        ((GridSubWindow *) get_sub_window(0))->set_current_char(c);
    };
    
    std::function<void()> save_copy = [this]() {
        save();
    };
    
    std::function<void()> start_new_copy = [this, start_new]() {
        close();
        start_new();
    };
    
    std::vector<Button> buttons={
        Button(save_copy, "save.png"),
        Button(start_new_copy, "new_file.png")
    };
        
    
    
    add_sub_window(
            new ToolsSubWindow(
                    sf::Vector2f(150, cell_width * grid.getRows()),
                    game_objects,
                    set_char,
				buttons
                
            ),
            cell_width * grid.getCols(), cell_width * grid.getCols() + 150);

}


void MainWindow::save()
{
    m_save(((GridSubWindow *) get_sub_window(0))->get_board());
}