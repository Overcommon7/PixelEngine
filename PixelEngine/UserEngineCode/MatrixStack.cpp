#include "pch.h"
#include "MatrixStack.h"

void MatrixStack::Update()
{
	combinedTransform = Matrix4::Identity();
	matrices.clear();
}

void MatrixStack::PushTranslation(const Vector3& d)
{
	auto m = Matrix4::Translation(d);
	matrices.push_back(m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationX(const float& radian)
{
	auto m = Matrix4::RotationX(radian);
	matrices.push_back(m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationY(const float& radian)
{
	auto m = Matrix4::RotationY(radian);
	matrices.push_back(m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationZ(const float& radian)
{
	auto m = Matrix4::RotationZ(radian);
	matrices.push_back(m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushScaling(const Vector3& s)
{
	auto m = Matrix4::Scaling(s);
	matrices.push_back(m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PopMatrix()
{
	if (matrices.empty()) return;
	auto matrix = matrices.back();
	matrices.pop_back();
	combinedTransform = matrix.Inverse() * combinedTransform;
}
