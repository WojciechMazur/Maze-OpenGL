#pragma once

#include <iostream>
#include "Point2D.h"


template <typename Datatype>
class Array2D
{
public:
	Array2D(size_t _rows, size_t _collumns) {
		if (_rows > 0 && _collumns > 0) {
			this->collumns = _collumns;
			this->rows = _rows;
		}
		array = new Datatype*[this->rows];
		for (size_t i = 0; i < rows; i++)
			array[i] = new Datatype[collumns];

		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < collumns; j++)
				array[i][j] = (Datatype)NULL;;
	}

	Array2D(const Array2D& copied)
	{
		this->rows = copied->rows;
		this->collumns = copied->collumns;

		this->array = new (Datatype*)[rows];
		for (size_t i = 0; i < rows; i++)
			this->array[i] = new Datatype[collumns];

		for (size_t i = 0; i < rows; i++)
			for (int j = 0; j < collumns; j++)
				array[i][j] = NULL;
	}

	~Array2D()
	{
		{
			for (size_t i = 0; i < rows; i++)
			{
					delete array[i];
			}
			delete array;
		}
	}

	Datatype* operator()(size_t row, size_t collumn) const throw(std::logic_error)
	{
		if (row < rows && row >= 0 && collumn < collumns && collumn >= 0)
			return &Array2D::array[row][collumn];
		throw std::out_of_range("Row or collumn position in Array2D<Datatype>* operator() is out of range");
	}
	
	Datatype* operator[](Point2D<size_t>* position) const throw (std::logic_error)
	{
		if (position->x >= 0 && position->y >= 0 && position->x < rows && position->y < collumns)
			return &Array2D::array[position->x][position->y];
	throw std::out_of_range("Position used in Array2D<Datatype>* operator[] is out of range");
	}
	
	void print()
	{
		for (size_t i = 0; i < this->rows; i++)
		{
			for (size_t j = 0; j < this->collumns; j++)
			{
				std::cout << static_cast<Datatype>(*this->operator()(i, j)) << " ";
			}
			std::cout << std::endl;
		}
	}

	size_t getSizeOfRows() { return rows; }
	size_t getSizeOfCollumns() { return collumns; }


protected:
	size_t rows, collumns;
	Datatype** array;

};

