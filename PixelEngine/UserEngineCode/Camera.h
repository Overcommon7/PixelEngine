#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class PixelCamera
{
    PixelCamera() = delete;
    PixelCamera(const PixelCamera& c) = delete;
    PixelCamera& operator=(const PixelCamera& c) = delete;

public:
    static void SetPosition(const Math::Vector3& position); // CmdSetCameraPosition
    static void SetDirection(const Math::Vector3& direction); // CmdSetCameraDirection
    static void SetNearPlane(const float& nearPlane);
    static void SetFarPlane(const float& farPlane);
    static void SetFOV(const float& fov);

    static Matrix4 GetViewMatrix();
    static Matrix4 GetProjectionMatrix();

    static const Math::Vector3& GetDirection() { return direction; }
    static const Math::Vector3& GetPosition() { return position; }

private:
    inline static Math::Vector3 position = { 0 ,0, 0 }; // default: 0, 0, 0
    inline static Math::Vector3 direction = { 0, 0, 1 }; // default: 0, 0, 1
    inline static float nearPlane = 0.01f; // default: 0.01
    inline static float farPlane = 100.f; // default: 100
    inline static float FOV = 1.57f; // default: 1.57

};

