//
// Created by User81 on 18.09.2021.
//

#include "square_matrix.h"
namespace mymatrix
{
    double SquareMatrix:: max_random_value = 20.1;
    double SquareMatrix:: random_eps = 0.0000001;
    double SquareMatrix::det() {
        double res;
        if (size() == 1) res = container[0][0];
        else if (size() == 2) res = container[0][0]*container[1][1] - container[1][0]*container[0][1];
        else
        {
            res = 0;
            for (int j = 0; j < size(); j++)
            {
                SquareMatrix submatrix = create_submatrix(j);
                res += pow(-1.0, 1.0+j+1.0) * container[0][j] * submatrix.det();
            }
        }
        return res;
    }

    SquareMatrix SquareMatrix::create_submatrix(std::size_t index) {
        SquareMatrix new_matrix = SquareMatrix(size() - 1);
        for (std::size_t i = 1; i < size(); i++)
        {
            std::size_t index2=0;
            for (std::size_t j = 0; j < size(); j++)
            {
                if(j == index) continue;
                new_matrix[i-1][index2] = this->container[i][j];
                index2++;
            }
        }
        return new_matrix;
    }
    SquareMatrix::SquareMatrix(const std::vector<std::vector<double>> &matrix) : Matrix(matrix) {}
    SquareMatrix::SquareMatrix(size_t size) : Matrix(size, size) {}
    SquareMatrix::SquareMatrix():Matrix() {}

    std::size_t SquareMatrix::size() const {
        return get_row_size();
    }
    SquareMatrix SquareMatrix::create_gilbert_matrix(std::size_t size) {
        SquareMatrix matrix = SquareMatrix(size);
        for(std::size_t i = 0; i < size; i++)
        {
            for(std::size_t j = 0; j < size; j++)
            {
                matrix[i][j] = 1.0/(i+j+2);
            }
        }
        return matrix;
    }
    SquareMatrix SquareMatrix::create_advantage_matrix(std::size_t size) {
        SquareMatrix matrix = create_random_matrix(size, max_random_value);
        for (std::size_t i = 0; i < matrix.size(); i++)
        {
            double item_i_i = abs(matrix[i][i]);
            double sum = 0;
            for(std::size_t j = 0; j < matrix.size(); j++)
            {
                if(i!=j) sum += abs(matrix[i][j]);
            }
            if(item_i_i <= sum) matrix[i][i] = (sum + 1)*sgn(matrix[i][i]);
        }
        while (abs(matrix.det()) <= random_eps) matrix = SquareMatrix::create_advantage_matrix(size);
        return matrix;
    }
    SquareMatrix SquareMatrix::create_random_matrix(std::size_t size, double max_value) {
        SquareMatrix matrix = SquareMatrix(size);
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distribution(-1 * max_value, max_value);
        for (std::size_t i = 0; i < size; i++)
            for (std::size_t j = 0; j < size; j++)
                matrix[i][j] = round(distribution(eng));
        return matrix;
    }

    double SquareMatrix::sgn(double value) {
        if(value < 0) return -1;
        return 1;
    }

    SquareMatrix SquareMatrix::create_identity_matrix(std::size_t size) {
        SquareMatrix matrix = SquareMatrix(size);
        for(std::size_t i = 0; i < size; i++)
            matrix[i][i] = 1.0;
        return matrix;
    }

    void SquareMatrix::swap_lines(std::size_t index1, std::size_t index2) {
        if(index1 < size() && index2 < size())
        {
            auto line = container[index1];
            container[index1] = container[index2];
            container[index2] = line;
            return;
        }
        throw std::out_of_range{ "index1=" + std::to_string(index1) +" or index2=" + std::to_string(index2) +
                                 " larger than matrix size=" + std::to_string(size()) };
    }

    SquareMatrix SquareMatrix::operator*(const SquareMatrix& that) {
        std::size_t that_size = that.size();
        std::string message = "Matrices must have same size!";
        if (this->size() != that_size)
        {
            throw std::logic_error{ message };
            return SquareMatrix();
        }
        SquareMatrix res = SquareMatrix(that_size);
        for(std::size_t i = 0; i < that_size; i++)
            for(std::size_t j = 0; j < that_size; j++)
                for(std::size_t k = 0; k < that_size; k++)
                    res[i][j] += this->container[i][k]*that[k][j];

        return res;
    }

    SquareMatrix SquareMatrix::create_tridiagonal_matrix(std::size_t size) {
        SquareMatrix matrix = SquareMatrix::create_random_matrix(size,max_random_value);
        for(std::size_t i = 0; i < matrix.size(); i++)
        {
            for(std::size_t j = 0; j < matrix.size(); j++)
            {
                if( i != j && i != j + 1 && i != j - 1) matrix[i][j] = 0;
            }
        }
        while (abs(matrix.det()) <= random_eps) matrix = SquareMatrix::create_tridiagonal_matrix(size);
        return matrix;
    }

    SquareMatrix SquareMatrix::create_random_matrix(std::size_t size) {
        return SquareMatrix::create_random_matrix(size,max_random_value);
    }

    SquareMatrix SquareMatrix::operator+(const SquareMatrix &that) {
        std::size_t this_size = this->size();
        std::size_t that_size = that.size();
        std::string message = "Matrices must have same size!";
        if (this_size != that_size)
        {
            throw std::logic_error{ message };
            return SquareMatrix();
        }
        SquareMatrix res(this_size);
        for (std::size_t i = 0; i < this_size; i++)
        {
            for (std::size_t j = 0; j < this_size; j++)
            {
                res[i][j] = this->container[i][j] + that[i][j];
            }
        }
        return res;
    }

    void SquareMatrix::transpose() {
        for(std::size_t i = 0; i < size(); i++){
            for(std::size_t j = 0; j < i; j++){
                auto temp = container[i][j];
                container[i][j] = container[j][i];
                container[j][i] = temp;
            }
        }
    }

    bool SquareMatrix::operator==(const SquareMatrix &that) const{
        if(this->size() != that.size()) return false;
        for(std::size_t i = 0; i < size(); i++){
            for(std::size_t j = 0; j < size(); j++){
                if(container[i][j] != that[i][j]) return false;
            }
        }
        return true;
    }

    bool SquareMatrix::operator!=(const SquareMatrix &that) const{
        return !((*this) == that);
    }
}