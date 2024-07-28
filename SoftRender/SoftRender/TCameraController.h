#pragma once

#include "IInputHandler.h"
#include "TMatrix.h"
#include <unordered_map>

class TCameraController : public IInputHandler
{
public:
	virtual void OnKeyDown(int virtualKeyCode) override;
	virtual void OnKeyUp(int virtualKeyCode) override;
	virtual void OnMouseMove(
		int posX,
		int posY,
		bool leftButton,
		bool rightButton,
		bool middleButton) override;

	TCameraController(const tmath::Vec3f& initialPosition, const tmath::Vec3f& eyePosition);
	tmath::Mat4f GetViewMatrix();
private:
	tmath::Vec3f m_position;
	tmath::Vec3f m_forward;
	tmath::Vec3f m_up = { 0.0f, 1.0f, 0.0f };

	float m_yaw;
	float m_pitch;
	float m_mouseSensitivity = 0.1f;
	float m_lastX, m_lastY;
	bool  m_mouseDown = false;

	float m_moveSpeed = 0.01f;

	std::unordered_map<int, bool> m_keyState;
	tmath::Mat4f m_viewMatrix;
};