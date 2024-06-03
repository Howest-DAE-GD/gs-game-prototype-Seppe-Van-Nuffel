#include "pch.h"
#include "player.h"
#include "utils.h"

Player::Player(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
    m_isAlive = true;
    m_Score = 0;
    m_Streak = 0;
    m_HighestStreak = 0;
	Point2f m_Pos = Point2f((screenWidth / 2)-25.f, 10.f);
	m_Rects[0] = Rectf{ m_Pos.x, m_Pos.y, 50.f, 70.f };
	m_Rects[1] = Rectf{ m_Pos.x - screenWidth, m_Pos.y, 50.f, 70.f };
	m_Rects[2] = Rectf{ m_Pos.x - screenWidth, m_Pos.y, 50.f, 70.f };
}

void Player::MovePlayer(float speed, float elapsedTime)
{
    if (m_Rects[0].left > m_ScreenWidth) {
        m_Rects[0].left -= m_ScreenWidth;
    }
    else if (m_Rects[0].left < -75) {
        m_Rects[0].left += m_ScreenWidth;
    }
    m_Rects[0].left += speed * elapsedTime;
    m_Rects[1].left = m_Rects[0].left - m_ScreenWidth;
    m_Rects[2].left = m_Rects[0].left + m_ScreenWidth;
}

void Player::DrawPlayer() const
{
    utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
    utils::FillRect(m_Rects[0]);
    utils::FillRect(m_Rects[1]);
    utils::FillRect(m_Rects[2]);
}

bool Player::CheckIfHit(Fruit* fruit)
{
    for (Rectf rect : m_Rects)
    {
        if ((utils::IsPointInRect(fruit->GetPos(), rect)) or 
            (utils::IsPointInRect(Point2f(fruit->GetPos().x - fruit->GetRadius(), fruit->GetPos().y), rect)) or 
            (utils::IsPointInRect(Point2f(fruit->GetPos().x + fruit->GetRadius(), fruit->GetPos().y), rect))){

            switch (fruit->GetType())
            {
            case EF_FruitRed:
                m_isAlive = false;
                break;
            case EF_FruitGreen:
                ++m_Score;
                ++m_Streak;
                break;
            case EF_FruitYellow:
                m_Score += 2;
                ++m_Streak;
                break;
            case EF_FruitBlue:
                m_Score += 5;
                ++m_Streak;
                break;
            }
            return true;
        }
    }
    return false;
}

int Player::GetScore() const
{
    return m_Score;
}

bool Player::isAlive() const
{
    return m_isAlive;
}

void Player::lostStreak(bool lostStreak)
{
    if (lostStreak) {
        if (m_Streak > m_HighestStreak)
            m_HighestStreak = m_Streak;
        m_Streak = 0;
    }
}

int Player::GetStreak() const
{
    return m_Streak;
}

int Player::GetHighestStreak() const
{
    return m_HighestStreak;
}
