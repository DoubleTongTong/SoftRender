#include "TCameraController.h"
#include <algorithm>

void TCameraController::OnKeyDown(int virtualKeyCode)
{
	if (virtualKeyCode == 'W' || virtualKeyCode == 'S' ||
		virtualKeyCode == 'A' || virtualKeyCode == 'D' ||
		virtualKeyCode == 'Q' || virtualKeyCode == 'E')
	{
		m_keyState[virtualKeyCode] = true;
	}
}
void TCameraController::OnKeyUp(int virtualKeyCode)
{
	if (virtualKeyCode == 'W' || virtualKeyCode == 'S' ||
		virtualKeyCode == 'A' || virtualKeyCode == 'D' ||
		virtualKeyCode == 'Q' || virtualKeyCode == 'E')
	{
		m_keyState[virtualKeyCode] = false;
	}
}

void TCameraController::OnMouseMove(
	int posX,
	int posY,
	bool leftButton,
	bool rightButton,
	bool middleButton)
{
	if (rightButton == false)
		m_mouseDown = false;
	else
	{
		if (m_mouseDown == false)
		{
			m_lastX = posX;
			m_lastY = posY;
			m_mouseDown = true;
		}

		float offsetX = m_lastX - posX;
		float offsetY = m_lastY - posY;

		m_lastX = posX;
		m_lastY = posY;

		m_yaw += offsetX * m_mouseSensitivity;
		m_pitch += offsetY * m_mouseSensitivity;

		m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
	}
}

TCameraController::TCameraController(const tmath::Vec3f& initialPosition, const tmath::Vec3f& eyePosition)
	: m_position(initialPosition), m_lastX(0), m_lastY(0)
{
	m_forward = (eyePosition - initialPosition).Normalize();
	m_yaw = tmath::radToDeg(atan2(m_forward.z(), m_forward.x()));
	m_pitch = tmath::radToDeg(asin(m_forward.y()));
}

tmath::Mat4f TCameraController::GetViewMatrix()
{
	m_forward.x() = cos(tmath::degToRad(m_yaw)) * cos(tmath::degToRad(m_pitch));
	m_forward.y() = sin(tmath::degToRad(m_pitch));
	m_forward.z() = sin(tmath::degToRad(m_yaw)) * cos(tmath::degToRad(m_pitch));
	m_forward.Normalize();
	//printf("m_forward=%f %f %f\n", m_forward.x(), m_forward.y(), m_forward.z());

	tmath::Vec3f right = tmath::cross(tmath::Vec3f(0.0f, 1.0f, 0.0f), m_forward).Normalize();

	m_up = tmath::cross(m_forward, right).Normalize();
	//printf("m_up=%f %f %f\n", m_up.x(), m_up.y(), m_up.z());
	if (m_keyState['W'])
		m_position += m_forward * m_moveSpeed;
	if (m_keyState['S'])
		m_position -= m_forward * m_moveSpeed;
	if (m_keyState['A'])
		m_position -= right * m_moveSpeed;
	if (m_keyState['D'])
		m_position += right * m_moveSpeed;
	if (m_keyState['Q'])
		m_position -= m_up * m_moveSpeed;
	if (m_keyState['E'])
		m_position += m_up * m_moveSpeed;

	tmath::Vec3f eye = m_position + m_forward;
	//printf("m_position=%f %f %f\n", m_position.x(), m_position.y(), m_position.z());
	return tmath::LookAtMatrix(m_position, eye, tmath::Vec3f(0.0f, 1.0f, 0.0f));
}