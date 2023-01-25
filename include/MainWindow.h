#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "GameObject.h"
#include "HorizontalWindow.h"
#include "CharMatrix.h"
#include "GridSubWindow.h"
#include "ToolsSubWindow.h"
#include "Button.h"


// (for big board with small screen the CELL_WIDTH and CELL_HEIGHT 
//  should be smaller)
const int CELL_WIDTH = 60;
const int MAX_GRID_HEIGHT = 900;
const int MAX_GRID_WIDTH = 1500;
/**
 * The main window of the editor.
 * Contains the grid (matrix) and the tools (right side) sub windows.
 * the class inherits from HorizontalWindow (the grid and the tools is 2 
 * horizontal sub-windows of this window).
 */
class MainWindow : public HorizontalWindow
{
public:
    /**
     * Constructor.
     * @param grid the starting grid.
     * @param game_objects the optionals game objects.
     * @param start_new function to run when the user press the start new button
     * @param save function to run when the user press the save button
     */
    MainWindow(const CharMatrix &grid,
               const std::vector<GameObject> &game_objects,
               const std::function<void()> &start_new,
               std::function<void(const CharMatrix &matrix)> save);
private:
    /**
     * run the save function that was given in the constructor with the right 
     * parameter.
     */
    void save();

    
    
    /**
     * The save function that was given in the constructor.
     */
    std::function<void(const CharMatrix &matrix)> m_save;
};
