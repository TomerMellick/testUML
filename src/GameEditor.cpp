#include "Inputs.h"
#include "GameEditor.h"
const char *FILE_NAME = "board.txt";

void GameEditor::start_new()
{

    m_re_run = true;
}

void GameEditor::save(const CharMatrix &matrix)
{

    std::ofstream file(FILE_NAME);
    std::ofstream file2("my_map.txt", std::ios::app);
    file2.seekp(0, std::ios::end);
    file << matrix;
    file2 << "200 "<<matrix;
    file.close();
    file2.close();
}

GameEditor::GameEditor()
{
    //init the game objects
    m_game_objects.emplace_back('a', "pacman.png");
    m_game_objects.emplace_back('&', "ghost.png");
    m_game_objects.emplace_back('%', "key.png");
    m_game_objects.emplace_back('*', "cake.png");
    m_game_objects.emplace_back('D', "door.png");
    m_game_objects.emplace_back('#', "wall.png");
    m_game_objects.emplace_back('$', "gift.png");
    m_game_objects.emplace_back(' ', "empty.png", "eraser.png");


}

void GameEditor::run()
{
    //lambads to pass as parameters to the main window
    auto save_lambada = [this](const CharMatrix &matrix) { save(matrix); };
    auto start_new_lambada = [this]() { start_new(); };

    //create the main window
    std::ifstream myFile(FILE_NAME);
    CharMatrix matrix;
    if (myFile.fail())
    {

        int rows, cols;
        get_window_size(cols, rows);
        matrix = CharMatrix(rows, cols);
    }
    else
    {
        myFile >> matrix;
    }
    m_re_run = false;
    MainWindow window(matrix, m_game_objects, start_new_lambada, save_lambada);
    window.run();
    while (m_re_run)
    {
        m_re_run = false;
        int cols, rows;
        get_window_size(rows, cols);
        matrix = CharMatrix(rows, cols);
        MainWindow window(matrix, m_game_objects, start_new_lambada,
                          save_lambada);
        window.run();
    }
}
