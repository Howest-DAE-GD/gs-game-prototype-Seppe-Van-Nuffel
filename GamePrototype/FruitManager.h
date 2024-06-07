#pragma once
#include "vector"
#include "Fruit.h"
#include "player.h"
class FruitManager
{
public:
	FruitManager(float screenWidth, float screenHeight);
	~FruitManager();

	void SpawnFruit();
	void Draw() const;
	bool Update(float elapsedTime);
	int GetActiveNumberOfFruit() const;
	void CheckHit(Player* player);
	void Reset();

	std::vector<Fruit*> m_vFruits{ 100 };
private:
	float m_screenWidth;
	float m_screenHeight;
};

