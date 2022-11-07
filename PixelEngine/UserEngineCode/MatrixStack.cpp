#include "pch.h"
#include "MatrixStack.h"

void MatrixStack::Update()
{
	combinedTransform = Matrix4::Identity();
	matrices.clear();
	matrices.resize(1);
}

void MatrixStack::PushTranslation(const Vector3& d)
{
	auto m = Matrix4::Translation(d);
	matrices.insert(matrices.begin(), m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationX(const float& radian)
{
	auto m = Matrix4::RotationX(radian);
	matrices.insert(matrices.begin(), m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationY(const float& radian)
{
	auto m = Matrix4::RotationY(radian);
	matrices.insert(matrices.begin(), m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushRotationZ(const float& radian)
{
	auto m = Matrix4::RotationZ(radian);
	matrices.insert(matrices.begin(), m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PushScaling(const Vector3& s)
{
	auto m = Matrix4::Scaling(s);
	matrices.insert(matrices.begin(), m);
	combinedTransform = m * combinedTransform;
}

void MatrixStack::PopMatrix()
{
	if (matrices.empty()) return;
	matrices.erase(matrices.begin());
}
