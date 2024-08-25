#include "pch.h"
#include "FruitManager.h"

FruitManager::FruitManager(float screenWidth, float screenHeight)
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
		Point2f pos{ float(rand() % int((m_screenWidth - 2 * radius) + radius)), float(m_screenHeight + radius) };

		for (int indx = 0; indx < m_vFruits.size(); indx++)
		{
			if (m_vFruits.at(indx) == nullptr) {
				int random{ rand() % 20 };
				FRUITTYPE type{};
				if (random == 19)
					type = EF_FruitPink;
				else if (random >= 18)
					type = EF_FruitYellow;
				else if (random >= 14)
					type = EF_FruitBlue;
				else if (random >= 10)
					type = EF_FruitGreen;
				else
					type = EF_FruitRed;
				m_vFruits.at(indx) = new Fruit(pos, radius, type);
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
