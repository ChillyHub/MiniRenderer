#pragma once

#include "math/Math.h"
#include "core/Input.h"

namespace MiniRenderer
{
	enum ProjectionType
	{
		Perspective,
		Orthonal
	};

	class Camera
	{
	public:
		// transform
		Vec3 Position       = { 0.0f, 0.0f, 0.0f };
		Quat Rotation       = { 1.0f, 0.0f, 0.0f, 0.0f };
		// camera options
		float MovementSpeed = 2.5f;
		// projection base
		float Fov           = 45.0f;
		float NearClip      = 0.3f;
		float FarClip       = 100.0f;
		float Size          = 5.0f;
		float Aspect        = 16.0f / 9.0f;
		float ScreenWidth   = 800.0f;
		float ScreenHeight  = 600.0f;
	public:
		Camera() = default;
		Camera(const Vec3& position, const Quat& rotation, 
			float fov, float aspect, float nearClip, float farClip);
		//Camera(const Vec3& position, const Quat& rotation, 
		//	float size, float aspect, float nearClip, float farClip);
	public:
		Mat4 GetViewMat() const { return m_viewMat; }
		Mat4 GetProjectMat() const { return m_projectMat; }
		Mat4 GetWorldToClipMat() const { return m_projectMat * m_viewMat; }
		Mat4 GetClipToWorldMat() const { return Math::Inverse(m_projectMat * m_viewMat); }
	public:
		void Update();
		void Resize(float width, float height);
		void CameraLookAt(const Vec3& worldPos, const Vec3& worldUp = { 0.0f, 0.0f, 1.0f });
	private:
		void rotateAroundPoint(const Vec3& worldPos, const Vec3& axis, float angle);
		void updateView();
		void updateProject();
	private:
		Mat4 m_viewMat    = Mat4(1.0f);
		Mat4 m_projectMat = Mat4(1.0f);
	private:
		bool m_changed = false;
		float m_mouseMovedSensitivity = 0.002f;
		float m_mouseScaleSensitivity = 0.25f;
		float m_cursorPosX = 0.0f;
		float m_cursorPosY = 0.0f;
		float m_scaleOffset = 0.0f;
		Vec3 m_focalPoint = { 0.0f, 0.0f, 0.0f };
		Vec3 m_oldPosition = { 0.0f, 0.0f, 0.0f };
		Vec3 m_cameraUp = { 0.0f, 0.0f, 1.0f };
		Vec3 tmpRight = { 1.0f, 0.0f, 0.0f };
	private:
		ProjectionType Projection = ProjectionType::Perspective;
	};
}