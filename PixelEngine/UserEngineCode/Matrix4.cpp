#include "pch.h"
#include "Matrix4.h"
namespace Math
{
    Matrix4::Matrix4(const vector<float> f)
    {
        _11 = f[0];
        _12 = f[1];
        _13 = f[2];
        _14 = f[3];
        _21 = f[4];
        _22 = f[5];
        _23 = f[6];
        _24 = f[7];
        _31 = f[8];
        _32 = f[9];
        _33 = f[10];
        _34 = f[11];
        _41 = f[12];
        _42 = f[13];
        _43 = f[14];
        _44 = f[15];
    }
    Matrix4 Matrix4::operator+(const Matrix4& m) const
    {

        return Matrix4();
    }

    Matrix4 Matrix4::operator*(const Matrix4& right) const
    {
        Matrix4 result;

        result._11 = this->_11 * right._11 + this->_12 * right._21 + this->_13 * right._31 + this->_14 * right._41;
        result._12 = this->_11 * right._12 + this->_12 * right._22 + this->_13 * right._32 + this->_14 * right._42;
        result._13 = this->_11 * right._13 + this->_12 * right._23 + this->_13 * right._33 + this->_14 * right._43;
        result._14 = this->_11 * right._14 + this->_12 * right._24 + this->_13 * right._34 + this->_14 * right._44;
        result._21 = this->_21 * right._11 + this->_22 * right._21 + this->_23 * right._31 + this->_24 * right._41;
        result._22 = this->_21 * right._12 + this->_22 * right._22 + this->_23 * right._32 + this->_24 * right._42;
        result._23 = this->_21 * right._13 + this->_22 * right._23 + this->_23 * right._33 + this->_24 * right._43;
        result._24 = this->_21 * right._14 + this->_22 * right._24 + this->_23 * right._34 + this->_24 * right._44;
        result._31 = this->_31 * right._11 + this->_32 * right._21 + this->_33 * right._31 + this->_34 * right._41;
        result._32 = this->_31 * right._12 + this->_32 * right._22 + this->_33 * right._32 + this->_34 * right._42;
        result._33 = this->_31 * right._13 + this->_32 * right._23 + this->_33 * right._33 + this->_34 * right._43;
        result._34 = this->_31 * right._14 + this->_32 * right._24 + this->_33 * right._34 + this->_34 * right._44;
        result._41 = this->_41 * right._11 + this->_42 * right._21 + this->_43 * right._31 + this->_44 * right._41;
        result._42 = this->_41 * right._12 + this->_42 * right._22 + this->_43 * right._32 + this->_44 * right._42;
        result._43 = this->_41 * right._13 + this->_42 * right._23 + this->_43 * right._33 + this->_44 * right._43;
        result._44 = this->_41 * right._14 + this->_42 * right._24 + this->_43 * right._34 + this->_44 * right._44;

        return result;
    }

    Matrix4 Matrix4::operator*(const float& f) const
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 result = Matrix4({ 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f });

        return result;
    }

    Matrix4 Matrix4::RotationX(float rad)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::RotationY(float rad)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::RotationZ(float rad)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Scaling(float s)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Scaling(Vector3 s)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Translation(Vector3 d)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Translation(float dx, float dy, float dz)
    {
        return Matrix4();
    }

    Vector3 Matrix4::TransformCoord(Vector3 v, Matrix4 m)
    {
        return Vector3();
    }

    Vector3 Matrix4::TransformNormal(Vector3 v, Matrix4 m)
    {
        return Vector3();
    }

    float Matrix4::Determinant(Matrix4 m)
    {
        return 0.0f;
    }

    Matrix4 Matrix4::Adjoint(Matrix4 m)
    {
        return Matrix4();
    }

    Matrix4 Matrix4::Transpose(Matrix4 m)
    {
        Matrix4 result;

        result._11 = m._11;
        result._12 = m._21;
        result._13 = m._31;
        result._14 = m._41;
        result._21 = m._12;
        result._22 = m._22;
        result._23 = m._32;
        result._24 = m._42;
        result._31 = m._13;
        result._32 = m._23;
        result._33 = m._33;
        result._34 = m._43;
        result._41 = m._14;
        result._42 = m._24;
        result._43 = m._34;
        result._44 = m._44;

        return result;
    }

    Matrix4 Matrix4::Inverse(Matrix4 m)
    {
        Matrix4 result;

        // Cache the matrix values (speed optimization)
        float a00 = m._11, a01 = m._12, a02 = m._13, a03 = m._14;
        float a10 = m._21, a11 = m._22, a12 = m._23, a13 = m._24;
        float a20 = m._31, a21 = m._32, a22 = m._33, a23 = m._34;
        float a30 = m._41, a31 = m._42, a32 = m._43, a33 = m._44;

        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

        result._11 = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
        result._12 = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
        result._13 = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
        result._14 = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
        result._21 = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
        result._22 = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
        result._23 = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
        result._24 = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
        result._31 = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
        result._32 = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
        result._33 = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
        result._34 = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
        result._41 = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
        result._42 = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
        result._43 = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
        result._44 = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

        return result;
    }
    vector<float*> Matrix4::ToVector()
    {
        vector<float*> f;
        f.resize(16);

        f[0] = &_11;
        f[1] = &_12;
        f[2] = &_13;
        f[3] = &_14;
        f[4] = &_21;
        f[5] = &_22;
        f[6] = &_23;
        f[7] = &_24;
        f[8] = &_31;
        f[9] = &_32;
       f[10] = &_33;
       f[11] = &_34;
       f[12] = &_41;
       f[13] = &_42;
       f[14] = &_43;
       f[15] = &_44;

       return f;
    }
}