#pragma once
#include "Fruit.h"
#include "vector"
class Player final
{
public:
	explicit Player(float screenWidth, float screenHeight);

	void MovePlayer(int speed, float elapsedTime);
	void DrawPlayer() const;
	bool CheckIfHit(Fruit* fruit);
	int GetScore() const;
	bool isAlive() const;
	void lostStreak(bool lostStreak);
	int GetStreak() const;
	int GetHighestStreak() const;
	void EndOfMatch();
	int GetHighScore() const;
	void Reset(float screenWidth, float screenHeight);

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	bool m_isAlive{ true };
	int m_Score;
	int m_Streak;
	int m_HighestStreak;
	std::vector<Rectf> m_Rects{ 3 };
	int m_Highscore;
};

