#include "pch.h"
#include "Fruit.h"
#include "utils.h"
Fruit::Fruit(Point2f pos, int radius, FRUITTYPE type)
{
    m_Pos = pos;
    m_Radius = radius;
    m_Type = type;
    m_Speed = (rand() % 41) + 120.f;
}

void Fruit::Draw() const
{
    switch (m_Type)
    {
    case EF_FruitRed:
        utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
        break;
    case EF_FruitGreen:
        utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
        break;
    case EF_FruitYellow:
        utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
        break;
    case EF_FruitBlue:
        utils::SetColor(Color4f(0.f, 0.f, 0.5f, 1.f));
        break;
    case EF_FruitPink:
        utils::SetColor(Color4f(1.f, 192.f / 255.f, 203.f / 255.f, 1.f));
        break;
    default:
        utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
        break;
    }
    utils::FillEllipse(m_Pos, m_Radius);
}

void Fruit::Update(float elapsedTime)
{
    m_Pos.y -= m_Speed * elapsedTime;
}

FRUITTYPE Fruit::GetType() const
{
    return m_Type;
}

Point2f Fruit::GetPos() const
{
    return m_Pos;
}

int Fruit::GetRadius() const
{
    return m_Radius;
}
