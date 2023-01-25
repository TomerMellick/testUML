#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
/***
 * a class  to create a matrix of characters
 * the game board
 */
class CharMatrix{
private:
    char** m_matrix;
    int m_rows;
    int m_cols;
public:
    CharMatrix();
    CharMatrix(int rows, int cols, char fill = ' ');
    CharMatrix(const CharMatrix& other);
    CharMatrix& operator=(const CharMatrix& other);
    ~CharMatrix();
    int getRows() const;
    int getCols() const;
    char& operator()(int row, int col);
    char& operator[](sf::Vector2i);
    char operator()(int row, int col) const;
    char operator[](sf::Vector2i) const;    
};

std::ostream& operator<<(std::ostream& os,const CharMatrix& matrix);
std::istream& operator>>(std::istream& os, CharMatrix& matrix);