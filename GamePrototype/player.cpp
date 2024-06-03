#include "pch.h"
#include "player.h"
#include "utils.h"

Player::Player(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	m_Pos = Point2f((screenWidth / 2)-25.f, 10.f);
}

void Player::MovePlayer(float speed, float elapsedTime)
{
	if (m_Pos.x > m_ScreenWidth) {
		m_Pos.x -= m_ScreenWidth;
	}
	else if (m_Pos.x > -50) {
		m_Pos.x += m_ScreenWidth;
	}
	m_Pos.x += speed * elapsedTime;
}

void Player::DrawPlayer() const
{
	utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	utils::FillRect(m_Pos, 50.f, 70.f);
	if (m_Pos.x + 50.f > m_ScreenWidth)
		utils::FillRect(m_Pos.x - m_ScreenWidth, m_Pos.y, 50.f, 70.f);
}
