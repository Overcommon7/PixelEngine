#pragma once
#include "Vector3.h"

namespace Math
{
	class Matrix4
	{
	public:
		float
			_11, _21, _31, _41,
			_12, _22, _32, _42,
			_13, _23, _33, _43,
			_14, _24, _34, _44;

		Matrix4() = default;
		Matrix4(const Matrix4& m) = default;
		Matrix4& operator= (const Matrix4& m) = default;
		Matrix4(const vector<float> f);


		Matrix4 operator+(const Matrix4& m) const;
		Matrix4 operator*(const Matrix4& m) const;
		Matrix4 operator*(const float& f) const;

		static Matrix4 Identity();
		static Matrix4 RotationX(float rad);
		static Matrix4 RotationY(float rad);
		static Matrix4 RotationZ(float rad);
		static Matrix4 Scaling(float s);
		static Matrix4 Scaling(Vector3 s);
		static Matrix4 Scaling(float sx, float sy, float sz);
		static Matrix4 Translation(Vector3 d);
		static Matrix4 Translation(float dx, float dy, float dz);

		Vector3 TransformCoord(Vector3 v, Matrix4 m); // assume w = 1
		Vector3 TransformNormal(Vector3 v, Matrix4 m); // assume w = 0
		float Determinant(Matrix4 m);
		Matrix4 Adjoint(Matrix4 m);
		Matrix4 Transpose(Matrix4 m);
		Matrix4 Inverse(Matrix4 m);
		vector<float*> ToVector();
	};
}


