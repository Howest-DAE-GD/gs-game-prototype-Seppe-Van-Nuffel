#pragma once
#include "BaseGame.h"
#include "player.h"
#include "FruitManager.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;
	void Reset();

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Player* m_pPlayer;
	FruitManager* m_pFruitManager;
	int m_playerSpeed;
	int m_speed{ 150 };
	float counter{};
	bool hasWon;
	GameState m_GameState;
	Rectf MenuButtonEasy;
	Rectf MenuButtonHard;
	Rectf MenuButtonStart;
	Difficulty m_Difficulty;
	bool firstFruit;
};