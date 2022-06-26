#include "Camera.h"

namespace MiniRenderer
{
	Camera::Camera(const Vec3& position, const Quat& rotation, 
		float fov, float aspect, float nearClip, float farClip)
		: Position(position), Rotation(rotation)
		, Fov(fov), Aspect(aspect), NearClip(nearClip), FarClip(farClip)
	{
		Projection = ProjectionType::Perspective;
		m_oldPosition = Position;
	}

	void Camera::Update()
	{
		float X = Input::GetCursorX();
		float Y = Input::GetCursorY();

		if (Input::IsMouseButtonPressed(Mouse::Left) && Input::IsHovered())
		{
			float deltaX = X - m_cursorPosX;
			float deltaY = Y - m_cursorPosY;
			Vec3 delta = { deltaX, -deltaY, 0.0f };
			auto up = Math::Rotate(Rotation, delta);

			if (Math::Norm2(up) != 0)
			{
				float angleX = delta.x / 4.0f;
				float angleY = delta.y / 4.0f;
				rotateAroundPoint(m_focalPoint, Vec3{ 0.0f, 0.0f, 1.0f }, -angleX);
				CameraLookAt(m_focalPoint, m_cameraUp);
				auto cameraBack = Math::Rotate(Rotation, Vec3{ 0.0f, 0.0f, 1.0f });
				auto planeBack = Vec3(cameraBack.x, cameraBack.y, 0.0f);
				auto oldDot = Math::Dot(Position - m_focalPoint, planeBack);
				auto cameraUp = Math::Rotate(Rotation, Vec3{ 0.0f, 1.0f, 0.0f });
				auto cameraRight = Math::Rotate(Rotation, Vec3{ 1.0f, 0.0f, 0.0f });
				rotateAroundPoint(m_focalPoint, cameraRight, angleY);
				auto newDot = Math::Dot(Position - m_focalPoint, planeBack);
				if (oldDot * newDot < 0)
				{
					m_cameraUp = -m_cameraUp;
				}
				CameraLookAt(m_focalPoint, m_cameraUp);
			}
			m_oldPosition = Position;
			m_changed = true;
		}
		else if ((Input::IsMouseButtonPressed(Mouse::Middle) || 
			Input::IsMouseButtonPressed(Mouse::Right)) && Input::IsHovered())
		{
			float deltaX = X - m_cursorPosX;
			float deltaY = Y - m_cursorPosY;
			Vec3 delta = { deltaX, -deltaY, 0.0f };
			auto up = Math::Rotate(Rotation, delta);

			auto mat = GetWorldToClipMat();
			auto mat_inv = Math::Inverse(mat);
			auto clipPoint = mat * Vec4(m_focalPoint, 1.0f);
			auto screenDelta = Vec4(delta.x / ScreenWidth,
				delta.y / ScreenHeight, 0.0f, 0.0f) * clipPoint.w * 2.0f;
			auto worldPoint = mat_inv * (clipPoint + screenDelta);
			auto worldDelta = Vec3(worldPoint) - m_focalPoint;

			Position -= worldDelta;
			m_focalPoint -= worldDelta;

			m_oldPosition = Position;
			m_changed = true;
		}
		else if (Position != m_oldPosition)
		{
			auto deltaOnWorld = Position - m_oldPosition;
			auto cameraX = Math::Rotate(Rotation, Vec3{ 0.0f, 1.0f, 0.0f });
			auto cameraY = Math::Rotate(Rotation, Vec3{ 1.0f, 0.0f, 0.0f });
			auto dCameraX = Math::Dot(cameraX, deltaOnWorld) * cameraX;
			auto dCameraY = Math::Dot(cameraY, deltaOnWorld) * cameraY;
			m_focalPoint += dCameraX + dCameraY;
			m_oldPosition = Position;

			m_changed = true;
		}

		if (Input::GetWheelDelta())
		{
			auto delta = Input::GetWheelDelta();
			auto back = Math::Rotate(Rotation, Vec3{ 0.0f, 0.0f, 1.0f });
			auto dist = Math::Norm(Position - m_focalPoint) * 0.2f;
			Position += -delta * dist * back;

			if (Size > 0.05f || Input::GetWheelDelta() < 0)
				m_scaleOffset += delta * m_mouseScaleSensitivity;

			Size = Math::Max(Math::Exp(0.7f * -m_scaleOffset), 0.05f);

			Input::ResetWheelDelta();
			m_changed = true;
		}

		m_cursorPosX = X;
		m_cursorPosY = Y;

		if (m_changed)
		{
			updateView();
			updateProject();
			m_changed = false;
		}
	}

	void Camera::Resize(float width, float height)
	{
		// Size = height;
		Aspect = width / height;
		m_changed = true;
	}

	void Camera::rotateAroundPoint(const Vec3& worldPos, const Vec3& axis, float angle)
	{
		Vec3 position = Position;
		Quat q = Quat(1.0f, 0.0f, 0.0f, 0.0f);
		q = Math::Rotate(q, Math::Radians(angle), axis);
		Vec3 newPosition = Math::Rotate(q, position - worldPos);
		Position = newPosition + worldPos;
	}

	void Camera::CameraLookAt(const Vec3& worldPos, const Vec3& worldUp)
	{
		Rotation = Math::MatToQuat(Math::Transpose(Math::LookAt(Position, worldPos, worldUp)));
	}

	void Camera::updateView()
	{
		Vec3 center = Math::Rotate(Rotation, Vec3{ 0.0f, 0.0f, -1.0f }) + Position;
		Vec3 up = Math::Rotate(Rotation, Vec3{ 0.0f, 1.0f, 0.0f });
		m_viewMat = Math::LookAt(Position, center, up);
	}

	void Camera::updateProject()
	{
		if (Projection == ProjectionType::Perspective)
		{
			m_projectMat = Math::Perspective(Math::Radians(Fov), Aspect, NearClip, FarClip);
		}
		else
		{
			m_projectMat = Math::Orthogonal(Aspect * Size, Size, NearClip, FarClip);
		}
	}
} // namespace MiniRenderer