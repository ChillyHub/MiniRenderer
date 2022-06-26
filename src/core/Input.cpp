#include "Input.h"

namespace MiniRenderer
{
	bool Input::IsKeyPressed(int keycode)
	{
		return Screen::GetKeyPress(keycode);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return Screen::GetMousePress(button);
	}

	bool Input::IsHovered()
	{
		return Screen::IsHovered();
	}

	IVec2 Input::GetCursorPos()
	{
		POINT p{0, 0};
		::GetCursorPos(&p);
		return { p.x, p.y };
	}

	int Input::GetCursorX()
	{
		return GetCursorPos().x;
	}

	int Input::GetCursorY()
	{
		return GetCursorPos().y;
	}

	int Input::GetWheelDelta()
	{
		return Screen::GetWheelDelta();
	}

	void Input::ResetWheelDelta()
	{
		Screen::ResetWheelDelta();
	}
} // namespace MiniRenderer