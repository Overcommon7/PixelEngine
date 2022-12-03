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
	Math::Vector3 look = direction.Normalize();
	Math::Vector3 right = Math::Vector3(0, 1, 0).CrossProduct(look).Normalize();
	Math::Vector3 up = look.CrossProduct(right);
	

	return Matrix4{
		right.x, up.x, look.x, 0,
		right.y, up.y, look.y, 0,
		right.z, up.z, look.z, 0,
		-right.DotProduct(position), -up.DotProduct(position), -look.DotProduct(position), 1
	};	
}

Matrix4 PixelCamera::GetProjectionMatrix()
{
	const float
		aspect = screenWidth / screenHeight,
		h = 1 / tanf(FOV * 0.5f),
		w = h / aspect,
		zf = farPlane,
		zn = nearPlane,
		d = zf / (zf - zn);



	return Matrix4{
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, d, 1,
		0, 0, -zn * d, 0
	};
	
}
