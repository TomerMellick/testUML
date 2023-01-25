#include "CharMatrix.h"
//default constructor
CharMatrix::CharMatrix():
    m_matrix(nullptr),
    m_rows(0),
    m_cols(0)
{
    
}
//  constructor with parameters
CharMatrix::CharMatrix(int rows, int cols, char fill):
        m_rows(rows),
        m_cols(cols),
        m_matrix(new char*[rows])
{
    for (int i = 0; i < rows; i++)
    {
        m_matrix[i] = new char[cols];
        for (int j = 0; j < cols; j++)
        {
            m_matrix[i][j] = fill;
        }
    }
}
//copy constructor
CharMatrix::CharMatrix(const CharMatrix& other):
        m_rows(other.m_rows),
        m_cols(other.m_cols),
        m_matrix(new char*[other.m_rows])
{
    for (int i = 0; i < other.m_rows; i++)
    {
        m_matrix[i] = new char[other.m_cols];
        for (int j = 0; j < other.m_cols; j++)
        {
            m_matrix[i][j] = other.m_matrix[i][j];
        }
    }
}
/***
 * operator = overload for CharMatrix
 * @param other
 * @return
 */
CharMatrix& CharMatrix::operator=(const CharMatrix& other)
{
    if (this != &other)
    {
        if(m_matrix != nullptr)
        {
            for (int i = 0; i < m_rows; i++)
            {
                delete[] m_matrix[i];
            }
            delete[] m_matrix;
        }
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_matrix = new char*[m_rows];
        for (int i = 0; i < m_rows; i++)
        {
            m_matrix[i] = new char[m_cols];
            for (int j = 0; j < m_cols; j++)
            {
                m_matrix[i][j] = other.m_matrix[i][j];
            }
        }
    }
    return *this;
}
//destructor
CharMatrix::~CharMatrix()
{
    for (int i = 0; i < m_rows; i++)
    {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}

int CharMatrix::getRows() const
{
    return m_rows;
}

int CharMatrix::getCols() const
{
    return m_cols;
}

char& CharMatrix::operator()(int row, int col)
{
    return m_matrix[row][col];
}

char& CharMatrix::operator[](sf::Vector2i pos)
{
    return m_matrix[pos.y][pos.x];
}

char CharMatrix::operator()(int row, int col) const
{
    return m_matrix[row][col];
}

char CharMatrix::operator[](sf::Vector2i pos) const
{
    return m_matrix[pos.y][pos.x];
}

std::ostream& operator<<(std::ostream& os,const CharMatrix& matrix)
{
    os << matrix.getCols() << " " << matrix.getRows() << std::endl;
    for (int i = 0; i < matrix.getRows(); i++)
    {
        for (int j = 0; j < matrix.getCols(); j++)
        {
            os << matrix(i, j);
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, CharMatrix& matrix)
{
    int rows, cols;
    is >> cols >> rows;
    matrix = CharMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char c;
            do
            {
                c = (char)is.get();
            } while (c == '\n' || c == '\r');
            matrix(i, j)  = c;
        }
    }
    return is;
}