#pragma once
class Player final
{
public:
	explicit Player(int screenWidth, int screenHeight);

	void MovePlayer(float speed, float elapsedTime);
	void DrawPlayer() const;
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
	Point2f m_Pos;
};

