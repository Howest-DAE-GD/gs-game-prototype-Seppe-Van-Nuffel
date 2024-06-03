#pragma once
#include "vector"
#include "Fruit.h"
#include "player.h"
class FruitManager
{
public:
	FruitManager(int screenWidth, int screenHeight);
	~FruitManager();

	void SpawnFruit();
	void Draw() const;
	bool Update(float elapsedTime);
	int GetActiveNumberOfFruit() const;
	void CheckHit(Player* player);
	void Reset();

	std::vector<Fruit*> m_vFruits{ 100 };
private:
	int m_screenWidth;
	int m_screenHeight;
};

