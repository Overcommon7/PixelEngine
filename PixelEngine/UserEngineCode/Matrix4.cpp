
#include "pch.h"
#include "Matrix4.h"
namespace Math
{
    float Matrix4::Get3x3Determinant(const vector<vector<float>>& m) const
    {
        return (m[0][0] * ((m[1][1] * m[2][2]) - (m[1][2] * m[2][1]))) - (m[0][1] * ((m[1][0] * m[2][2]) - (m[2][0] * m[1][2]))) - (m[0][2] * ((m[1][0] * m[2][1]) - (m[1][1] * m[2][0])));
    }
    vector<vector<float>> Matrix4::GetMinorMatrix(short row, short column) const
    {
        vector<vector<float>> result = To2DVector();
        result.erase(result.begin() + column - 1);
        for (short i = 0; i < result.size(); i++)
            result[i].erase(result.front().begin() + row - 1);
        return result;
    }
    Matrix4::Matrix4(const vector<float>& f)
    {
        if (f.size() < 16)
        {
            *this = Matrix4();
            return;
        }
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
    Matrix4::Matrix4(const vector<vector<float>>& f)
    {
        if (f.size() < 4 || f[0].size() < 4 || f[1].size() < 4 || f[2].size() < 4 || f[3].size() < 4)
        {
            *this = Matrix4();
            return;
        }
        _11 = f[0][0];
        _12 = f[0][1];
        _13 = f[0][2];
        _14 = f[0][3];
        _21 = f[1][0];
        _22 = f[1][1];
        _23 = f[1][2];
        _24 = f[1][3];
        _31 = f[2][0];
        _32 = f[2][1];
        _33 = f[2][2];
        _34 = f[2][3];
        _41 = f[3][0];
        _42 = f[3][1];
        _43 = f[3][2];
        _44 = f[3][3];
    }
    Matrix4::Matrix4(const std::initializer_list<float> f)
    {
        if (f.size() < 16)
        {
            *this = Matrix4();
            return;
        }
        _11 = *f.begin();
        _12 = *f.begin() + 1;
        _13 = *f.begin() + 2;
        _14 = *f.begin() + 3;
        _21 = *f.begin() + 4;
        _22 = *f.begin() + 5;
        _23 = *f.begin() + 6;
        _24 = *f.begin() + 7;
        _31 = *f.begin() + 8;
        _32 = *f.begin() + 9;
        _33 = *f.begin() + 10;
        _34 = *f.begin() + 11;
        _41 = *f.begin() + 12;
        _42 = *f.begin() + 13;
        _43 = *f.begin() + 14; 
        _44 = *f.begin() + 15; 
    }
    Matrix4 Matrix4::operator+(const Matrix4& m) const
    {
        Matrix4 result;

        result._11 = this->_11 + m._11;
        result._12 = this->_12 + m._12;
        result._13 = this->_13 + m._13;
        result._14 = this->_14 + m._14;
        result._21 = this->_21 + m._21;
        result._22 = this->_22 + m._22;
        result._23 = this->_23 + m._23;
        result._24 = this->_24 + m._24;
        result._31 = this->_31 + m._31;
        result._32 = this->_32 + m._32;
        result._33 = this->_33 + m._33;
        result._34 = this->_34 + m._34;
        result._41 = this->_41 + m._41;
        result._42 = this->_42 + m._42;
        result._43 = this->_43 + m._43;
        result._44 = this->_44 + m._44;

        return result;
    }

    Matrix4 Matrix4::operator-(const Matrix4& m) const
    {
        Matrix4 result;

        result._11 = this->_11 - m._11;
        result._12 = this->_12 - m._12;
        result._13 = this->_13 - m._13;
        result._14 = this->_14 - m._14;
        result._21 = this->_21 - m._21;
        result._22 = this->_22 - m._22;
        result._23 = this->_23 - m._23;
        result._24 = this->_24 - m._24;
        result._31 = this->_31 - m._31;
        result._32 = this->_32 - m._32;
        result._33 = this->_33 - m._33;
        result._34 = this->_34 - m._34;
        result._41 = this->_41 - m._41;
        result._42 = this->_42 - m._42;
        result._43 = this->_43 - m._43;
        result._44 = this->_44 - m._44;

        return result;
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
        auto result = ToVector();
        for (auto& v : result)
            v *= f;
        return Matrix4(result);
    }

    Matrix4 Matrix4::Identity()
    {
        return Matrix4({ 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f });

    }

    Matrix4 Matrix4::RotationX(float rad)
    {
        Matrix4 result = Identity();
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._22 = cosres;
        result._23 = sinres;
        result._32 = -sinres;
        result._33 = cosres;

        return result;
    }

    Matrix4 Matrix4::RotationY(float rad)
    {
        Matrix4 result = Identity();
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._11 = cosres;
        result._13 = -sinres;
        result._31 = sinres;
        result._33 = cosres;

        return result;
    }

    Matrix4 Matrix4::RotationZ(float rad)
    {
        Matrix4 result = Identity();
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._11 = cosres;
        result._12 = sinres;
        result._21 = -sinres;
        result._22 = cosres;

        return result;
    }

    Matrix4 Matrix4::Scaling(float s)
    {
        return Matrix4 ({ s, 0.0f, 0.0f, 0.0f,
                      0.0f, s, 0.0f, 0.0f,
                      0.0f, 0.0f, s, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Scaling(Vector3 s)
    {
        return Matrix4({ s.x, 0.0f, 0.0f, 0.0f,
                      0.0f, s.y, 0.0f, 0.0f,
                      0.0f, 0.0f, s.z, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
    {
        return Matrix4 ({sx, 0.0f, 0.0f, 0.0f,
                        0.0f, sy, 0.0f, 0.0f,
                        0.0f, 0.0f, sz, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Translation(Vector3 d)
    {
        return Matrix4 ({1.0f, 0.0f, 0.0f, d.x,
                            0.0f, 1.0f, 0.0f, d.y,
                            0.0f, 0.0f, 1.0f, d.z,
                            0.0f, 0.0f, 0.0f, 1.0f });

    }

    Matrix4 Matrix4::Translation(float dx, float dy, float dz)
    {
        return Matrix4 ({  1.0f, 0.0f, 0.0f, dx,
                    0.0f, 1.0f, 0.0f, dy,
                    0.0f, 0.0f, 1.0f, dz,
                    0.0f, 0.0f, 0.0f, 1.0f });

    }

    Vector3 Matrix4::TransformCoord(Vector3 v)
    {
        Matrix4 transform = { 1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         v.x, v.y, v.z, 1.0f };
        return Vector3();
    }

    Vector3 Matrix4::TransformNormal(Vector3 v)
    {
        return Vector3();
    }

    float Matrix4::Determinant()
    {
        float result = 0.0f;

        float a00 = this->_11, a01 = this->_12, a02 = this->_13, a03 = this->_14;
        float a10 = this->_21, a11 = this->_22, a12 = this->_23, a13 = this->_24;
        float a20 = this->_31, a21 = this->_32, a22 = this->_33, a23 = this->_34;
        float a30 = this->_41, a31 = this->_42, a32 = this->_43, a33 = this->_44;

        result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
            a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
            a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
            a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
            a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
            a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

        return result;
    }

    Matrix4 Matrix4::Adjoint()
    {
        auto as2DVec = To2DVector();
        vector<vector<float>> result(4, vector<float>(4, 0));
        for (short i = 1; i <= as2DVec.size(); i++)
            for (short j = 1; j <= as2DVec[i].size(); i++)
                result[i - 1][j - 1] = pow(-1, i + j) * Get3x3Determinant(GetMinorMatrix(j, i));
        return result;
    }

    Matrix4 Matrix4::Transpose()
    {
        Matrix4 result;

        result._11 = this->_11;
        result._12 = this->_21;
        result._13 = this->_31;
        result._14 = this->_41;
        result._21 = this->_12;
        result._22 = this->_22;
        result._23 = this->_32;
        result._24 = this->_42;
        result._31 = this->_13;
        result._32 = this->_23;
        result._33 = this->_33;
        result._34 = this->_43;
        result._41 = this->_14;
        result._42 = this->_24;
        result._43 = this->_34;
        result._44 = this->_44;

        return result;
    }

    Matrix4 Matrix4::Inverse()
    {
        Matrix4 result;

        float a00 = this->_11, a01 = this->_12, a02 = this->_13, a03 = this->_14;
        float a10 = this->_21, a11 = this->_22, a12 = this->_23, a13 = this->_24;
        float a20 = this->_31, a21 = this->_32, a22 = this->_33, a23 = this->_34;
        float a30 = this->_41, a31 = this->_42, a32 = this->_43, a33 = this->_44;

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
    vector<float*> Matrix4::GetVector()
    {
        return vector<float*>({
            &_11, &_12, &_13, &_14,
            &_21, &_22, &_23, &_24,
            &_31, &_32, &_33, &_34,
            &_41, &_42, &_43, &_44,
            });
    }
    vector<float> Matrix4::ToVector() const
    {
        return vector<float>({
             _11, _12, _13, _14,
             _21, _22, _23, _24,
             _31, _32, _33, _34,
             _41, _42, _43, _44,
            });
    }
    vector<vector<float>> Matrix4::To2DVector() const
    {
        return vector<vector<float>>({
            {_11, _12, _13, _14},
            {_21, _22, _23, _24},
            {_31, _32, _33, _34},
            {_41, _42, _43, _44},
            });
    }
}