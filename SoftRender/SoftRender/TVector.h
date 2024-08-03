#pragma once
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include <sstream>

namespace tmath
{
	template<typename T, size_t N>
	class Vector
	{
	protected:
		T elements[N];

	public:
		Vector()
		{
		}

		Vector(std::initializer_list<T> init)
		{
			assert(init.size() == N);
			size_t i = 0;
			for (auto& e : init)
				elements[i++] = e;
		}

		size_t size() const
		{
			return N;
		}

		Vector& operator=(const Vector& rhs)
		{
			if (this != &rhs)
				memcpy(elements, rhs.elements, N * sizeof(T));
			return *this;
		}

		T& operator[](size_t i)
		{
			assert(i < N);
			return elements[i];
		}

		const T& operator[](size_t i) const
		{
			assert(i < N);
			return elements[i];
		}

		Vector operator-() const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = -elements[i];
			return res;
		}

		Vector operator+(const Vector& rhs) const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = elements[i] + rhs.elements[i];
			return res;
		}

		Vector operator-(const Vector& rhs) const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = elements[i] - rhs.elements[i];
			return res;
		}

		Vector operator*(const Vector& rhs) const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = elements[i] * rhs.elements[i];
			return res;
		}

		Vector operator*(T scalar) const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = elements[i] * scalar;
			return res;
		}

		Vector operator/(T scalar) const
		{
			assert(scalar != 0);

			Vector res;
			for (size_t i = 0; i < N; i++)
				res[i] = elements[i] / scalar;
			return res;
		}

		Vector& operator+=(const Vector& rhs)
		{
			for (size_t i = 0; i < N; i++)
				elements[i] += rhs.elements[i];
			return *this;
		}

		Vector& operator-=(const Vector& rhs)
		{
			for (size_t i = 0; i < N; i++)
				elements[i] -= rhs.elements[i];
			return *this;
		}

		Vector& operator*=(T scalar)
		{
			for (size_t i = 0; i < N; i++)
				elements[i] *= scalar;
			return *this;
		}

		Vector& operator/=(T scalar)
		{
			assert(scalar != 0);
			for (size_t i = 0; i < N; i++)
				elements[i] /= scalar;
			return *this;
		}

		Vector& Normalize()
		{
			T norm = 0;
			for (size_t i = 0; i < N; i++)
				norm += elements[i] * elements[i];
			norm = sqrt(norm);

			assert(norm != 0);

			for (size_t i = 0; i < N; i++)
				elements[i] /= norm;

			return *this;
		}

		std::string toString() const
		{
			std::ostringstream oss;
			oss << "(";
			for (size_t i = 0; i < N; i++)
			{
				oss << elements[i];
				if (i < N - 1)
					oss << ", ";
			}
			oss << ")";
			return oss.str();
		}
	};

	template<typename T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2()
		{
		}

		Vector2(T x, T y) : Vector<T, 2>({ x, y })
		{
		}

		Vector2(const Vector<T, 2>& v)
			: Vector<T, 2>({ v[0], v[1] })
		{
		}

		T& x() { return Vector<T, 2>::elements[0]; }
		T& y() { return Vector<T, 2>::elements[1]; }
		const T& x() const { return Vector<T, 2>::elements[0]; }
		const T& y() const { return Vector<T, 2>::elements[1]; }

		T& u() { return Vector<T, 2>::elements[0]; }
		T& v() { return Vector<T, 2>::elements[1]; }
		const T& u() const { return Vector<T, 2>::elements[0]; }
		const T& v() const { return Vector<T, 2>::elements[1]; }
	};

	template<typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3()
		{
		}

		Vector3(T x, T y, T z) : Vector<T, 3>({ x, y, z })
		{
		}

		Vector3(const Vector<T, 3>& v)
			: Vector<T, 3>({ v[0], v[1], v[2]})
		{
		}

		T& x() { return Vector<T, 3>::elements[0]; }
		T& y() { return Vector<T, 3>::elements[1]; }
		T& z() { return Vector<T, 3>::elements[2]; }

		const T& x() const { return Vector<T, 3>::elements[0]; }
		const T& y() const { return Vector<T, 3>::elements[1]; }
		const T& z() const { return Vector<T, 3>::elements[2]; }
	};

	template<typename T>
	class Vector4 : public Vector<T, 4>
	{
	public:
		Vector4() : Vector<T, 4>()
		{
		}

		Vector4(T x, T y, T z, T w) : Vector<T, 4>({ x, y, z, w })
		{
		}

		Vector4(const Vector<T, 4>& v)
			: Vector<T, 4>({ v[0], v[1], v[2], v[3] })
		{
		}

		Vector4(const Vector<T, 3>& vec3, T w)
			: Vector<T, 4>({ vec3[0], vec3[1], vec3[2], w })
		{
		}

		T& x() { return Vector<T, 4>::elements[0]; }
		T& y() { return Vector<T, 4>::elements[1]; }
		T& z() { return Vector<T, 4>::elements[2]; }
		T& w() { return Vector<T, 4>::elements[3]; }

		const T& x() const { return Vector<T, 4>::elements[0]; }
		const T& y() const { return Vector<T, 4>::elements[1]; }
		const T& z() const { return Vector<T, 4>::elements[2]; }
		const T& w() const { return Vector<T, 4>::elements[3]; }

		operator Vector3<T>() const
		{
			return Vector3<T>(Vector<T, 4>::elements[0], Vector<T, 4>::elements[1], Vector<T, 4>::elements[2]);
		}
	};

	template<typename T, size_t N>
	Vector<T, N> operator*(T scalar, const Vector<T, N>& vec)
	{
		Vector<T, N> res;
		for (size_t i = 0; i < N; i++)
			res[i] = scalar * vec[i];
		return res;
	}

	template<typename T, size_t N>
	T dot(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		T sum = 0;
		for (size_t i = 0; i < a.size(); i++)
			sum += a[i] * b[i];
		return sum;
	}

	template<typename T>
	T cross(const Vector<T, 2>& a, const Vector<T, 2>& b)
	{
		return a[0] * b[1] - a[1] * b[0];
	}

	template<typename T>
	Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b)
	{
		return Vector3<T>(
			a.y() * b.z() - a.z() * b.y(),
			a.z() * b.x() - a.x() * b.z(),
			a.x() * b.y() - a.y() * b.x()
			);
	}

	template<typename T, size_t N>
	Vector<T, N> interpolate(const Vector<T, N>& v1, T weight1, const Vector<T, N>& v2, T weight2, const Vector<T, N>& v3, T weight3)
	{
		Vector<T, N> result;
		for (size_t i = 0; i < N; i++)
		{
			result[i] = v1[i] * weight1 + v2[i] * weight2 + v3[i] * weight3;
		}
		return result;
	}

	using Vec2f = Vector2<float>;
	using Vec2i = Vector2<int>;
	using Vec3f = Vector3<float>;
	using Vec3i = Vector3<int>;
	using Vec4f = Vector4<float>;
	using Point2i = Vector2<int>;
	using UV2f = Vector2<float>;
}
