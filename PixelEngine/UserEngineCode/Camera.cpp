#include "pch.h"
#include "Camera.h"
#include "Defines.h"

void PixelCamera::SetPosition(const Math::Vector3& pos)
{
	position = pos;
}

void PixelCamera::SetDirection(const Math::Vector3& dir)
{
	direction = dir;
}

void PixelCamera::SetNearPlane(const float& near)
{
	nearPlane = near;
}

void PixelCamera::SetFarPlane(const float& far)
{
	farPlane = far;
}

void PixelCamera::SetFOV(const float& fov)
{
	FOV = fov;
}


Matrix4 PixelCamera::GetViewMatrix()
{
	Math::Vector3 up = { 0, 1, 0 };
	Math::Vector3 right = { 1, 0, 0 };
	Math::Vector3 look = { 0, 0, 1 };

	return Matrix4{
		right.x, up.x, look.x, 0,
		right.y, up.y, look.y, 0,
		right.z, up.z, look.z, 0,
		-right.DotProduct(direction), -up.DotProduct(direction), -look.DotProduct(direction), 1
	};	
}

Matrix4 PixelCamera::GetProjectionMatrix()
{
	float
		a = screenWidth / screenHeight,
		d = 1 / tanf(FOV / 2),
		q = farPlane / (farPlane - nearPlane);

	return Matrix4{
		d / a, 0, 0, 0,
		0, d, 0, 0,
		0, 0, q, 1,
		0, 0, -nearPlane * q, 0
	};
	
}
