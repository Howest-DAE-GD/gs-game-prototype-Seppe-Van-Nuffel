#pragma once
#include "Fruit.h"
#include "vector"
class Player final
{
public:
	explicit Player(int screenWidth, int screenHeight);

	void MovePlayer(float speed, float elapsedTime);
	void DrawPlayer() const;
	bool CheckIfHit(Fruit* fruit);
	int GetScore() const;
	bool isAlive() const;
	void lostStreak(bool lostStreak);
	int GetStreak() const;
	int GetHighestStreak() const;

private:
	int m_ScreenWidth;
	int m_ScreenHeight;
	bool m_isAlive{ true };
	int m_Score;
	int m_Streak;
	int m_HighestStreak;
	std::vector<Rectf> m_Rects{ 3 };
};

