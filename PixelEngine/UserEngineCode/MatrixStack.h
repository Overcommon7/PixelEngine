#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class MatrixStack
{
public:
    MatrixStack() = delete;
    MatrixStack(const MatrixStack& m) = delete;
    MatrixStack& operator=(const MatrixStack& m) = delete;

    static void Update();
    static void PushTranslation(const Vector3& d);
    static void PushRotationX(const float& radian);
    static void PushRotationY(const float& radian);
    static void PushRotationZ(const float& radian);
    static void PushScaling(const Vector3& s);
    static void PopMatrix();

    static const Matrix4& GetTransform() { return combinedTransform; }

private:
    inline static vector<Matrix4> matrices = {};
    inline static Matrix4 combinedTransform = Matrix4::Identity();
};

