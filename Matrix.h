#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{
public:
    Matrix(int r = 4, int c = 4);
    inline int nrows() {return rows;}
    inline int ncols() {return cols;}
    static Matrix identity(int dimensions);
    std::vector<float>& operator[](const int i);
    Matrix operator*(const Matrix& a);
    Matrix transpose();
    Matrix inverse();

    friend std::ostream& operator<<(std::ostream& s, Matrix& m);

private:
    int cols, rows;
    std::vector<std::vector<float> > m;
}

#endif //MATRIX_H