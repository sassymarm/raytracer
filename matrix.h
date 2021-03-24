#pragma once

#include <stdio.h>
#include <assert.h>
#include "Tuple.h"

class Matrix
{
private:
	int r, c;
	double* m;
public:

	~Matrix()
	{
		//free(m);
	}

	Matrix()
	{
		r = 4;
		c = 4;
		m = (double*)malloc(sizeof(double) * r * c);
	}

	Matrix(int r, int c)
	{
		this->r = r;
		this->c = c;
		m = (double*)malloc(sizeof(double) * r * c);
	}

	Matrix(int r, int c, double * mn)
	{
		this->r = r;
		this->c = c;
		m = (double*)malloc(sizeof(double) * r * c);
		for (int i = 0; i < r * c; ++i)
		{
			m[i] = mn[i];
		}
	}

	Matrix(int rn, int cn, double _0, double _1, double _2, double _3)
	{
		r = rn;
		c = cn;
		m = (double*)malloc(sizeof(double) * r * c);
		m[0] = _0;
		m[1] = _1;
		m[2] = _2;
		m[3] = _3;
	}

	Matrix(int rn, int cn, double _0, double _1, double _2, double _3, double _4, double _5, double _6, double _7, double _8)
	{
		r = rn;
		c = cn;
		m = (double*)malloc(sizeof(double) * r * c);
		m[0] = _0;
		m[1] = _1;
		m[2] = _2;
		m[3] = _3;
		m[4] = _4;
		m[5] = _5;
		m[6] = _6;
		m[7] = _7;
		m[8] = _8;
	}

	Matrix(int rn, int cn, double _0, double _1, double _2, double _3, double _4, double _5, double _6, double _7, double _8, double _9, double _10, double _11,
		double _12, double _13, double _14, double _15)
	{
		r = rn;
		c = cn;
		m = (double*)malloc(sizeof(double) * r * c);
		m[0] = _0;
		m[1] = _1;
		m[2] = _2;
		m[3] = _3;
		m[4] = _4;
		m[5] = _5;
		m[6] = _6;
		m[7] = _7;
		m[8] = _8;
		m[9] = _9;
		m[10] = _10;
		m[11] = _11;
		m[12] = _12;
		m[13] = _13;
		m[14] = _14;
		m[15] = _15;
	}

	Matrix submatrix(int rn, int cn)
	{
		Matrix sub(r - 1, c - 1);
		for (int i = 0; i < c; ++i)
		{
			if (i == cn)
				continue;
			for (int y = 0; y < c; ++y)
			{
				if (y == rn)
					continue;

				// if i > rn, or y > cn, place these -1 position in the new matrix
				int ipos = i;
				int ypos = y;

				if (i > rn)
					--ipos;
				if (y > cn)
					--ypos;

				sub.setValue(ipos, ypos, m[i + y * c]);
			}
		}
		return sub;
	}

	void setValues(double* mn)
	{
		for (int i = 0; i < r * c; ++i)
		{
			m[i] = mn[i];
		}
	}

	double getValue(int r, int c)
	{
		return m[r * this->r + c];
	}

	void setValue(int r, int c, double value)
	{
		m[r * this->r + c] = value;
	}

	void print()
	{
		for (int i = 0; i < r * c; ++i)
		{
			printf("%0.2f ", m[i]);
		}
		printf("\n");
	}

	void printg()
	{
		printf("Printing %d by %d matrix:\n", r, c);
		for (int y = 0; y < r; ++y)
		{
			for (int x = 0; x < c; ++x)
			{
				printf("%.2f ", m[x + y * r]);
			}
			printf("\n");
		}
	}


	static Matrix IdentityMatrix()
	{
		double a[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		Matrix q(4, 4, a);
		return q;

	}

	void setIdentityMatrix()
	{
		m[0] = 1;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;
		m[4] = 0;

		m[5] = 1;
		m[6] = 0;
		m[7] = 0;
		m[8] = 0;
		m[9] = 0;

		m[10] = 1;
		m[11] = 0;
		m[12] = 0;
		m[13] = 0;
		m[14] = 0;

		m[15] = 1;
	}

	double determinant()
	{
		return m[0] * m[3] - m[1] * m[2];
	}

	Matrix transpose()
	{
		Matrix mn;
		for (int i = 0; i < r; ++i)
		{
			for (int y = 0; y < c; ++y)
			{
				mn.setValue(i, y, m[i + y * c]);
			}
		}
		return mn;
	}

	bool operator==(Matrix matrix)
	{
		bool result = true;
		for (int i = 0; i < r * c; ++i)
		{
			if (m[i] != matrix.m[i])
			{
				result = false;
				break;
			}
		}
		return result;
	}

	bool operator!=(Matrix matrix)
	{
		bool result = false;
		for (int i = 0; i < r * c; ++i)
		{
			if (m[i] != matrix.m[i])
			{
				result = true;
				break;
			}
		}
		return result;
	}

	Matrix operator*(Matrix matrix)
	{
		//double* d = (double*)malloc(sizeof(double) * r * c);
		Matrix n(r, c);

		for (int i = 0; i < r * c; ++i)
		{
			int row, column = 0;
			row = (int)floor(i / c);
			column = i % c;

			double value = 0;
			for (int y = 0; y < 4; ++y)
			{
				value += this->getValue(row, y)* matrix.getValue(y, column);
			}
			n.setValue(row, column, value);

		}
		return n;
	}

	Tuple operator*(Tuple t)
	{
		Tuple n;
		double vals[4];
		for (int y = 0; y < 4; ++y)
		{
			double value = 0;
			
			int i = 0;
			value += m[i++ + y * r] * t.getX();
			value += m[i++ + y * r] * t.getY();
			value += m[i++ + y * r] * t.getZ();
			value += m[i + y * r] * t.getW();
			
			vals[y] = value;
		}
		n.set(vals[0], vals[1], vals[2], vals[3]);
		return n;
	}

	void operator=(Matrix matrix)
	{
		m = matrix.m;
	}

	

	static void equalityTest()
	{
		double a1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
		Matrix m1(4, 4, a1);
		double a2[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
		Matrix m2(4, 4, a2);

		double a3[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		Matrix m3(4, 4, a3);

		assert(m1 == m2);
		assert(m1 != m3);
	}


	static void multiplicationTest()
	{
		// Matrix * Matrix
		double a1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
		Matrix m1(4, 4, a1);
		double a2[16] = { -2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8 };
		Matrix m2(4, 4, a2);

		Matrix m3 = m1 * m2;
		
		double a4[16] = { 20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42 };
		Matrix m4(4, 4, a4);

		assert(m3 == m4);

		// Matrix * Tuple
		Tuple t1(1, 2, 3, 1);
		double a5[16] = { 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
		Matrix m5(4, 4, a5);
		Tuple t2 = m5 * t1;
		Tuple t3(18, 24, 33, 1);

		assert(t2 == t3);

		// Matrix * IdentityMatrix
		double a6[16] = { 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
		Matrix m6(4, 4, a6);
		assert(m6 * Matrix::IdentityMatrix() == m6);

		// IdentityMatrix * Tuple
		Tuple t4(1, 2, 3, 4);
		assert(Matrix::IdentityMatrix() * t4 == t4);
	}


	static void runTests()
	{
		printf("Running Matrix::runTests()\n");
		
		// Constructors
		double ma1[16] = { 1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5 };
		Matrix m1(4, 4, ma1);
		assert(m1.getValue(0, 0) == 1);
		assert(m1.getValue(0, 3) == 4);
		assert(m1.getValue(1, 0) == 5.5);
		assert(m1.getValue(1, 2) == 7.5);
		assert(m1.getValue(2, 2) == 11);
		assert(m1.getValue(3, 0) == 13.5);
		assert(m1.getValue(3, 2) == 15.5);

		double ma2[4] = { -3, 5, 1, -2 };
		Matrix m2(2, 2, ma2);
		assert(m2.getValue(0, 0) == -3);
		assert(m2.getValue(0, 1) == 5);
		assert(m2.getValue(1, 0) == 1);
		assert(m2.getValue(1, 1) == -2);

		double ma3[9] = {-3, 5, 0, 1, -2, -7, 0, 1, 1 };
		Matrix m3(3, 3, ma3);
		assert(m3.getValue(0, 0) == -3);
		assert(m3.getValue(1, 1) == -2);
		assert(m3.getValue(2, 2) == 1);

		// Equality
		equalityTest();

		// Multiplication
		multiplicationTest();

		// Transpose
		assert(Matrix(4, 4, 0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8).transpose() == Matrix(4, 4, 0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8));
		assert(Matrix::IdentityMatrix() == Matrix::IdentityMatrix().transpose());

		// Determinant
		assert(Matrix(2, 2, 1, 5, -3, 2).determinant() == 17);

		// Submatrix
		Matrix m(3, 3, 1, 5, 0, -3, 2, 7, 0, 6, -3);
		Matrix mx(2, 2);
		mx = m.submatrix(0, 2);
		mx.printg();
		//assert( == Matrix(2, 2, -3, 2, 0, 6));
	}
};