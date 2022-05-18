#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>

/**
*	\brief Namespace for class Matrix
*/
namespace mymatrix
{
	/**
	*	\brief A class that represents a mathematical object written in the form of a rectangular table of elements. 
	*
	*	See [Matrix(mathematics)]( https://en.wikipedia.org/wiki/Matrix_(mathematics) "Information about matrix in Wikipedia")
	*	
	*	The following operations are implemented: 
	*	
	*	- adding and subtracting matrices;
	*	- increase and decrease of the matrix size;
	*	- creating an empty matrix;
	*	- etc.
	*	
	*	The following operations must be overrided for items:
	* 
	*	- operator+ ;
	*	- operator- ;
	*	- operator<< .
	* 
	*/
	template <typename T>
	class Matrix
	{
    protected:
		std::vector<std::vector<T>> container;/**<The space for items*/
		std::size_t row_size;/**<The number of rows*/
		std::size_t col_size;/**<The number of columns*/
		/**
		*	\brief Checks row and column sizes
		* 
		*	If All column sizes is not equal than return false else true.
		*/
		bool check_sizes();
	public:
		/**
		*	\brief Makes matrix by two-dimensional array
		* 
		*	All column sizes of two-dimensional array must be equal else will be error.
		* 
		*	\param matrix - two-dimensional array
		*/
		explicit Matrix(const std::vector<std::vector<T>>& matrix);
		/**
		*	\brief Creates matrix with row_size rows and col_size columns.
		* 
		*	All items will be equal zero.
		*/
		Matrix(std::size_t row_size, std::size_t col_size);
		/**
		*	\brief Creates empty matrix
		*/
		Matrix();
		/**
		*	\returns number of rows
		*/
		std::size_t get_row_size() const;
		/**
		*	\returns number of columns
		*/
		std::size_t get_col_size() const;
		/**
		*	\brief Adds other matrix to this matrix 
		*/
		Matrix<T> operator+ (const Matrix<T>& matrix);
		/**
		*	\brief Subtracts other matrix from this matrix 
		*/
		Matrix<T> operator- (const Matrix<T>& matrix);
		/**
		*	\brief Checks quals of matrices
		*/
		bool operator==(const Matrix<T>& matrix);
		/**
		*	\brief Adds matrix to ostream
		* 
		*	\param out - ostream
		*	\param matrix - matrix to output
		*/
		template <typename V>
		friend std::ostream& operator<< (std::ostream& out, const Matrix<V>& matrix);
		/**
		*	\brief Returns row by index
		* 
		*	If index will be greater than row numbers than will be error.
		* 
		*	\param index - index of row
		*	\returns row by index
		*/
		const std::vector<T>& operator[](std::size_t index) const;
        std::vector<T>& operator[](std::size_t index);
		/**
		*	\brief Adds rows_number rows to matrix
		* 
		*	All new items will be equal zero.
		*/
		void add_rows(std::size_t rows_number = 1);
		/**
		*	\brief Adds columns_number columns to matrix
		*
		*	All new items will be equal zero.
		*/
		void add_columns(std::size_t columns_number = 1);
		/**
		*	\brief Removes rows_number rows from matrix
		* 
		*	If rows_number will be greater than number of rows than will be error.
		*/
		void remove_rows(std::size_t rows_number = 1);
		/**
		*	\brief Removes columns_number columns from matrix
		*
		*	If columns_number will be greater than number of columns than will be error.
		*/
		void remove_columns(std::size_t columns_number = 1);
		/**
		*	\brief Returns item by i-index and j-index
		* 
		*	If index i will be greater than rows number 
		*	or index j will be greater than columns number than will be error.
		* 
		*	\param i - index of row
		*	\param j - index of column
		*	\returns item by indexes
		*/
		T get_item(std::size_t i, std::size_t j) const;
		/**
		*	\brief Creates matrix with random items
		* 
		*	\param row_size - number of rows
		*	\param col_size - number of columns
		*	\param max_value - maximum value of items
		*	\returns new matrix
		*/
		static Matrix<T> create_random_matrix(std::size_t row_size, std::size_t col_size, const T& max_value);
		/**
		*	\brief Creates square matrix
		* 
		*	\param size - number of rows and columns
		*	\param max_value - maximum value of items
		*	\returns new square matrix
		*/
		static Matrix<T> create_random_matrix(std::size_t size, const T& max_value);
	};
}
namespace mymatrix
{
	template<typename T>
	bool Matrix<T>::operator==(const Matrix<T>& matrix)
	{
		if (this->get_row_size() != matrix.get_row_size()) return false;
		if (this->get_col_size() != matrix.get_col_size()) return false;
		for (std::size_t i = 0; i < matrix.get_row_size(); i++)
			for (std::size_t j = 0; j < matrix.get_col_size(); j++)
				if (this->container[i][j] != matrix.get_item(i, j)) return false;
		return true;
	}
	template<typename T>
	Matrix<T> Matrix<T>::create_random_matrix(
		std::size_t row_size, std::size_t col_size, const T& max_value)
	{
		Matrix<T> matrix(row_size, col_size);
		if (max_value > 0)
		{
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_real_distribution<T> distr(-1*max_value, max_value);
			for (std::size_t i = 0; i < row_size; i++)
				for (std::size_t j = 0; j < col_size; j++)
					matrix[i][j] = distr(eng);
		}
		return matrix;
	}
	template<typename T>
	Matrix<T> Matrix<T>::create_random_matrix(
		std::size_t size, const T& max_value)
	{
		return create_random_matrix(size, size, max_value);
	}
	template<typename T>
	T Matrix<T>::get_item(std::size_t i, std::size_t j)
		const
	{
		if(i < this->get_row_size() && j < this->get_col_size())
			return this->container[i][j];
		throw std::out_of_range{ "The index=" + std::to_string(i) +
			" larger than rows number=" + std::to_string(this->get_row_size())+
			" or the index=" + std::to_string(j) +
			" larger than columns number=" + std::to_string(this->get_col_size()) };
	}
	template<typename T>
	void Matrix<T>::remove_rows(std::size_t rows_number)
	{
		if(rows_number <= this->get_row_size())
			for (std::size_t i = 0; i < rows_number; i++)
				container.erase(container.begin() + container.size() - 1);
		else throw std::out_of_range{"There are " + std::to_string(this->get_row_size())+
			" rows but need to remove " + std::to_string(rows_number) + " rows!"};
		row_size -= rows_number;
	}
	template<typename T>
	void Matrix<T>::remove_columns(std::size_t columns_number)
	{
		if(columns_number <= this->get_col_size())
			for (auto& item : container)
				for (std::size_t i = 0; i < columns_number; i++)
					item.erase(item.begin() + item.size() - 1);
		else throw std::out_of_range{ "There are " + std::to_string(this->get_col_size()) +
			" columns but need to remove " + std::to_string(columns_number) + " columns!" };
		col_size -= columns_number;
	}
	template<typename T>
	void Matrix<T>::add_rows(std::size_t rows_number)
	{
		row_size += rows_number;
		for (std::size_t i = 0; i < rows_number; i++)
			container.push_back(std::vector<T>(col_size));
	}
	template<typename T>
	void Matrix<T>::add_columns(std::size_t columns_number)
	{
		col_size += columns_number;
		for (auto& item : container)
		{
			for (std::size_t i = 0; i < columns_number; i++)
				item.push_back(T());
		}
	}
	template<typename T>
	bool Matrix<T>::check_sizes()
	{
		if (container.size() == 0) return true;
		std::size_t columns = container[0].size();
		for (std::size_t i = 1; i < container.size(); i++)
			if (container[i].size() != columns) return false;
		return true;
	}
	template<typename T>
	Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrix)
		: container{ matrix }, row_size{ matrix.size() }, col_size{ matrix.size() > 0 ? matrix[0].size() : 0 }
	{
		if (!check_sizes())
			throw std::logic_error{ "Numbers of columns must be same!" };
	}
	template<typename T>
	Matrix<T>::Matrix(): row_size(0), col_size(0) {}
	template<typename T>
	Matrix<T>::Matrix(std::size_t row_size, std::size_t col_size)
		:container(std::vector<std::vector<T>>(row_size,std::vector<T>(col_size))),
		row_size(row_size), col_size(col_size) {}
	
	template<typename T>
	std::size_t Matrix<T>::get_row_size() const
	{
		return row_size;
	}
	template<typename T>
	std::size_t Matrix<T>::get_col_size() const
	{
		return col_size;
	}
	template<typename T>
	Matrix<T> Matrix<T>::operator+ (const Matrix<T>& matrix)
	{
		std::size_t matrix_row_size = matrix.get_row_size();
		std::size_t matrix_col_size = matrix.get_col_size();
		std::string message = "Matrices must have same size!";
		if (this->row_size != matrix_row_size || this->col_size != matrix_col_size)
		{
			throw std::logic_error{ message };
			return Matrix<T>();
		}
		Matrix<T> res(matrix_row_size, matrix_col_size);
		for (std::size_t i = 0; i < matrix_row_size; i++)
		{
			for (std::size_t j = 0; j < matrix_col_size; j++)
			{
				res[i][j] = this->container[i][j] + matrix.container[i][j];
			}
		}

		return res;
	}
	template<typename T>
	Matrix<T> Matrix<T>::operator- (const Matrix<T>& matrix)
	{
		std::size_t matrix_row_size = matrix.get_row_size();
		std::size_t matrix_col_size = matrix.get_col_size();
		std::string message = "Matrices must have same size!";
		if (this->row_size != matrix_row_size || this->col_size != matrix_col_size)
		{
			throw std::logic_error{ message };
			return Matrix<T>();
		}
		Matrix<T> res(matrix_row_size, matrix_col_size);
		for (std::size_t i = 0; i < matrix_row_size; i++)
		{
			for (std::size_t j = 0; j < matrix_col_size; j++)
			{
				res[i][j] = this->container[i][j] - matrix.container[i][j];
			}
		}

		return res;
	}
	template<typename T>
	std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix)
	{
		for (std::size_t i = 0; i < matrix.get_row_size(); i++)
		{
			for (std::size_t j = 0; j < matrix.get_col_size(); j++)
			{
				out << matrix.container[i][j] << "\t";
			}
			out << std::endl;
		}

		return out;
	}
    template<typename T>
	const std::vector<T>& Matrix<T>::operator[](std::size_t index) const
	{
		if(index < this->container.size())
			return this->container[index];
		throw std::out_of_range{ "index=" + std::to_string(index) + 
			" larger than rows number=" + std::to_string(this->container.size()) };
	}
    template<typename T>
    std::vector<T>& Matrix<T>::operator[](std::size_t index)
    {
        if(index < this->container.size())
            return this->container[index];
        throw std::out_of_range{ "index=" + std::to_string(index) +
                                 " larger than rows number=" + std::to_string(this->container.size()) };
    }
}