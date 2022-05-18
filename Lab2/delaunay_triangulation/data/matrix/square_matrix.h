#pragma once

#include "my_matrix.h"
namespace mymatrix
{
    class SquareMatrix: public Matrix<double>{
    private:
        static double max_random_value;
        static double random_eps;
        SquareMatrix create_submatrix(std::size_t index);
        static double sgn(double value);
    public:
        explicit SquareMatrix(const std::vector<std::vector<double>> &matrix);
        explicit SquareMatrix(size_t size);
        SquareMatrix();
        double det();
        std::size_t size() const;
        void swap_lines(std::size_t index1, std::size_t index2);
        static SquareMatrix create_random_matrix(std::size_t size, double max_value);
        static SquareMatrix create_random_matrix(std::size_t size);
        static SquareMatrix create_advantage_matrix(std::size_t size);
        static SquareMatrix create_gilbert_matrix(std::size_t size);
        static SquareMatrix create_identity_matrix(std::size_t size);
        static SquareMatrix create_tridiagonal_matrix(std::size_t size);
        SquareMatrix operator* (const SquareMatrix& that);
        SquareMatrix operator+ (const SquareMatrix& that);
        bool operator==(const SquareMatrix& that) const;
        bool operator!=(const SquareMatrix& that) const;
        void transpose();
    };
}
