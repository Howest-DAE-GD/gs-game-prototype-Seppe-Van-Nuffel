#include "pch.h"
#include "FruitManager.h"

FruitManager::FruitManager(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

FruitManager::~FruitManager()
{
	Reset();
}

void FruitManager::SpawnFruit()
{
	if (GetActiveNumberOfFruit() < m_vFruits.size()) {
		int radius{ rand() % 11 + 10 };
		Point2f pos{ float(rand() % (m_screenWidth - 2 * radius) + radius), float(m_screenHeight - radius) };

		for (int indx = 0; indx < m_vFruits.size(); indx++)
		{
			if (m_vFruits.at(indx) == nullptr) {
				m_vFruits.at(indx) = new Fruit(pos, radius, FRUITTYPE(rand() % 4));
				break;
			}
		}

	}
}

void FruitManager::Draw() const
{
	for (int indx = 0; indx < m_vFruits.size(); indx++)
	{
		if (m_vFruits.at(indx) != nullptr)
			m_vFruits.at(indx)->Draw();
	}
}

bool FruitManager::Update(float elapsedTime)
{
	bool streaklost{ false };
	for (int indx = 0; indx < m_vFruits.size(); indx++)
	{
		if (m_vFruits.at(indx) != nullptr) {
			m_vFruits.at(indx)->Update(elapsedTime);
			if (m_vFruits.at(indx)->GetPos().y + m_vFruits.at(indx)->GetRadius() < 0) {
				if (!streaklost and m_vFruits.at(indx)->GetType() != EF_FruitRed)
					streaklost = true;
				delete m_vFruits.at(indx);
				m_vFruits.at(indx) = nullptr;
			}
		}
	}
	return streaklost;
}

int FruitManager::GetActiveNumberOfFruit() const
{
	int amount{};
	for (Fruit* i : m_vFruits)
	{
		if (i != nullptr) {
			++amount;
		}
	}
	return amount;
}

void FruitManager::CheckHit(Player* player)
{
	for (int indx = 0; indx < m_vFruits.size(); indx++)
	{
		if (m_vFruits.at(indx) != nullptr) {
			if (player->CheckIfHit(m_vFruits.at(indx))) {
				delete m_vFruits.at(indx);
				m_vFruits.at(indx) = nullptr;
			}
		}
	}
}

void FruitManager::Reset()
{
	for (int indx = 0; indx < m_vFruits.size(); indx++)
	{
		if (m_vFruits.at(indx) != nullptr) {
			delete m_vFruits.at(indx);
			m_vFruits.at(indx) = nullptr;
		}
	}
}
