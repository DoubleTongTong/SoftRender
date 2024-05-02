#pragma once
#include <string.h>
#include <assert.h>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "TVector.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace tmath
{
	template<typename T, size_t ROWS, size_t COLS>
	class Matrix
	{
		T elements[ROWS][COLS];

	public:
		Matrix()
		{
		}

		Matrix(std::initializer_list<T> init)
		{
			assert(init.size() == ROWS * COLS);
			auto it = init.begin();
			for (size_t row = 0; row < ROWS; row++)
			{
				for (size_t col = 0; col < COLS; col++)
				{
					elements[row][col] = *it;
					it++;
				}
			}
		}

		Matrix(std::initializer_list<std::initializer_list<T>> init)
		{
			assert(init.size() == ROWS);
			size_t i = 0, j = 0;
			for (auto& row : init)
			{
				assert(row.size() == COLS);
				j = 0;
				for (auto& ele : row)
				{
					elements[i][j] = ele;
					j++;
				}
				i++;
			}
		}

		Matrix& operator=(const Matrix& other)
		{
			if (this != &other)
			{
				memcpy(elements, other.elements, sizeof(elements));
			}
			return *this;
		}

		T& at(size_t row, size_t col)
		{
			assert(row < ROWS&& col < COLS);
			return elements[row][col];
		}

		const T& at(size_t row, size_t col) const
		{
			assert(row < ROWS&& col < COLS);
			return elements[row][col];
		}

		void SwapRows(size_t row1, size_t row2)
		{
			std::swap(elements[row1], elements[row2]);
		}

		template<size_t N>
		Matrix<T, ROWS, N> operator*(const Matrix<T, COLS, N>& other) const
		{
			Matrix<T, ROWS, N> res;
			T sum;
			for (size_t i = 0; i < ROWS; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					sum = 0;
					for (size_t k = 0; k < COLS; k++)
					{
						sum += at(i, k) * other.at(k, j);
					}
					res.at(i, j) = sum;
				}
			}
			return res;
		}

		Vector<T, ROWS> operator*(const Vector<T, COLS>& vec)
		{
			Vector<T, ROWS> res;
			T sum;
			for (size_t i = 0; i < ROWS; i++)
			{
				sum = 0;
				for (size_t j = 0; j < COLS; j++)
					sum += elements[i][j] * vec[j];
				res[i] = sum;
			}
			return res;
		}

		void ToIdentity()
		{
			memset(elements, 0, sizeof(elements));
			for (size_t i = 0; i < std::min(ROWS, COLS); ++i)
			{
				elements[i][i] = 1;
			}
		}

		void ToZero()
		{
			memset(elements, 0, sizeof(elements));
		}

		Matrix Inverse()
		{
			assert(ROWS == COLS);
			Matrix P, L, U;
			PLUDecomposition(&P, &L, &U);

			//LY=P
			Matrix X, Y;
			ForwardSubstitute(L, P, &Y);
			//UX=Y
			BackwardSubstitute(U, Y, &X);

			return X;
		}

		void Print(const std::string& name = "") const
		{
			if (!name.empty())
				std::cout << "Matrix '" << name << "' (" << ROWS << "x" << COLS << "):\n";
			else
				std::cout << "Matrix (" << ROWS << "x" << COLS << "):\n";

			for (size_t r = 0; r < ROWS; r++)
			{
				for (size_t c = 0; c < COLS; c++)
				{
					std::cout << std::setw(10) << std::setprecision(4) << elements[r][c] << " ";
				}
				std::cout << "\n";
			}
			std::cout << std::endl;
		}
	private:
		void LUDecomposition(Matrix* L, Matrix* U)
		{
			assert(ROWS == COLS);

			*U = *this;
			L->ToIdentity();

			for (size_t k = 0; k < ROWS; k++)
			{
				for (size_t i = k + 1; i < ROWS; i++)
				{
					assert(U->at(k, k) != 0);
					L->at(i, k) = U->at(i, k) / U->at(k, k);

					for (size_t j = k; j < ROWS; j++)
						U->at(i, j) -= L->at(i, k) * U->at(k, j);
				}
			}
		}

		void PLUDecomposition(Matrix* P, Matrix* L, Matrix* U)
		{
			assert(ROWS == COLS);

			T maxEle, ele;
			size_t i, j, k;
			size_t maxRow;

			*U = *this;
			L->ToIdentity();
			P->ToIdentity();

			for (k = 0; k < ROWS; k++)
			{
				maxEle = std::abs(U->at(k, k));
				maxRow = k;

				for (i = k + 1; i < ROWS; i++)
				{
					ele = std::abs(U->at(i, k));
					if (ele > maxEle)
					{
						maxEle = ele;
						maxRow = i;
					}
				}

				if (k != maxRow)
				{
					U->SwapRows(k, maxRow);
					P->SwapRows(k, maxRow);

					// SwapRowsPartial
					for (j = 0; j < k; j++)
						std::swap(L->at(k, j), L->at(maxRow, j));
				}

				for (i = k + 1; i < ROWS; i++)
				{
					assert(U->at(k, k) != 0);
					L->at(i, k) = U->at(i, k) / U->at(k, k);
					for (size_t j = k; j < ROWS; j++)
						U->at(i, j) -= L->at(i, k) * U->at(k, j);
				}
			}
		}

		// LY=B
		template<size_t N>
		static void ForwardSubstitute(const Matrix& L, const Matrix<T, ROWS, N>& B, Matrix<T, COLS, N>* Y)
		{
			assert(ROWS == COLS);
			T sum;
			for (size_t i = 0; i < COLS; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					sum = B.at(i, j);

					for (size_t k = 0; k < i; k++)
						sum -= L.at(i, k) * Y->at(k, j);

					Y->at(i, j) = sum / L.at(i, i);
				}
			}
		}

		// UX=Y
		template<size_t N>
		static void BackwardSubstitute(const Matrix& U, const Matrix<T, ROWS, N>& Y, Matrix<T, COLS, N>* X)
		{
			assert(ROWS == COLS);
			T sum;
			for (int i = COLS - 1; i >= 0; i--)
			{
				for (size_t j = 0; j < N; j++)
				{
					sum = Y.at(i, j);
					for (size_t k = i + 1; k < COLS; k++)
						sum -= U.at(i, k) * X->at(k, j);

					X->at(i, j) = sum / U.at(i, i);
				}
			}
		}
	};



	using Mat4f = Matrix<float, 4, 4>;
}