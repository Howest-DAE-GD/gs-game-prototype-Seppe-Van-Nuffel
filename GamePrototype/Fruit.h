#pragma once
#include "Enums.h"
class Fruit final
{
public:
	explicit Fruit(Point2f pos, int radius, FRUITTYPE type);

	void Draw() const;
	void Update(float elapsedTime);

	FRUITTYPE GetType() const;
	Point2f GetPos() const;
	int GetRadius() const;
private:
	FRUITTYPE m_Type;
	Point2f m_Pos;
	int m_Radius;
};

