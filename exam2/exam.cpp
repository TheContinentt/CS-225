// Your code here!
#include "exam.h"
#include "matrix.h"
#include <iostream>

//using namespace std;
//using namespace exam;
namespace exam{
Matrix flip_horiz(Matrix &m)
{
	unsigned int columns = (&m)->get_num_columns();
	unsigned int rows = (&m)->get_num_rows();
	Matrix newmatrix = Matrix(rows, columns);
	//cout << rows/2 << columns/2 << endl;
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			unsigned int oldvalue = (&m)->get_coord(i, j);
			newmatrix.set_coord(rows - 1 - i, j, oldvalue);
		}
	}
	return newmatrix;
}
}
