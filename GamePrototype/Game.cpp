#include "pch.h"
#include "Game.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	delete m_pPlayer;
	delete m_pFruitManager;
	Cleanup( );
}

void Game::Initialize( )
{
	m_pPlayer = new Player(GetViewPort().width, GetViewPort().height);
	m_pFruitManager = new FruitManager(GetViewPort().width, GetViewPort().height);
	m_playerSpeed = 0;
	hasWon = false;
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	if (m_pPlayer->isAlive() and !hasWon) {
		m_pPlayer->MovePlayer(m_playerSpeed, elapsedSec);
		m_pPlayer->lostStreak(m_pFruitManager->Update(elapsedSec));
		counter += elapsedSec;

		if (m_pPlayer->GetScore() <= 50 and m_pFruitManager->GetActiveNumberOfFruit() < 10) {
			if (counter > 2.5f) {
				m_pFruitManager->SpawnFruit();
				counter = 0;
			}
		}
		else if (m_pPlayer->GetScore() > 50 and m_pPlayer->GetScore() <= 75 and m_pFruitManager->GetActiveNumberOfFruit() < 20) {
			if (counter > 1.5f) {
				m_pFruitManager->SpawnFruit();
				counter = 0;
			}
		}
		else if (m_pPlayer->GetScore() > 75 and m_pPlayer->GetScore() <= 125 and m_pFruitManager->GetActiveNumberOfFruit() < 30) {
			if (counter > 0.5f) {
				m_pFruitManager->SpawnFruit();
				counter = 0;
			}
		}
		else if (m_pPlayer->GetScore() > 125 and m_pPlayer->GetScore() <= 250 and m_pFruitManager->GetActiveNumberOfFruit() < 100) {
			if (counter > 0.25f) {
				m_pFruitManager->SpawnFruit();
				counter = 0;
			}
		}
		else if (m_pPlayer->GetScore() > 250 and m_pPlayer->GetScore() <= 500 and m_pFruitManager->GetActiveNumberOfFruit() < 100) {
			if (counter > 0.1f) {
				m_pFruitManager->SpawnFruit();
				counter = 0;
			}
		}
		else if(m_pPlayer->GetScore() > 500)
			hasWon = true;

		m_pFruitManager->CheckHit(m_pPlayer);
	}

	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	
	if (m_pPlayer->isAlive() and !hasWon) {
		Texture{ "red = dead", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) }.Draw(Point2f(0, GetViewPort().height - 30.f));
		Texture{ "green = 1", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) }.Draw(Point2f(0, GetViewPort().height - 60.f));
		Texture{ "yellow = 2", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) }.Draw(Point2f(0, GetViewPort().height - 90.f));
		Texture{ "blue = 5", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) }.Draw(Point2f(0, GetViewPort().height - 120.f));

		m_pFruitManager->Draw();
		m_pPlayer->DrawPlayer();

		Texture score{ std::to_string(m_pPlayer->GetScore()), "LuckiestGuy-Regular.ttf", 50, Color4f(1.f,1.f,1.f,1.f) };
		score.Draw(Point2f(GetViewPort().width - score.GetWidth() - 5.f, GetViewPort().height - score.GetHeight() - 5.f));
		Texture streak{ "Streak: " + std::to_string(m_pPlayer->GetStreak()), "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		streak.Draw(Point2f((GetViewPort().width / 2) - (streak.GetWidth() / 2), GetViewPort().height - streak.GetHeight() - 5.f));
	}

	if (!m_pPlayer->isAlive()) {
		Texture restart{ "Press R to restart", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		restart.Draw(Point2f((GetViewPort().width / 2) - (restart.GetWidth() / 2), (GetViewPort().height / 2) - (restart.GetHeight() / 2) + 15.f));
		Texture allergy{ "Try to avoid the red fruits! You are allergic to them", "LuckiestGuy-Regular.ttf", 15, Color4f(1.f,1.f,1.f,1.f) };
		allergy.Draw(Point2f((GetViewPort().width / 2) - (allergy.GetWidth() / 2), (GetViewPort().height / 2) - (allergy.GetHeight() / 2) - 15.f));
		Texture streak{ "Highest streak: " + std::to_string((m_pPlayer->GetHighestStreak() == 0 ? m_pPlayer->GetStreak() : m_pPlayer->GetHighestStreak())), "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		streak.Draw(Point2f((GetViewPort().width / 2) - (streak.GetWidth() / 2), GetViewPort().height - streak.GetHeight() - 5.f));
	}
	else if (hasWon) {
		Texture restart{ "Press R to restart", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		restart.Draw(Point2f((GetViewPort().width / 2) - (restart.GetWidth() / 2), (GetViewPort().height / 2) - (restart.GetHeight() / 2) + 15.f));
		Texture won{ "You have won!", "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		won.Draw(Point2f((GetViewPort().width / 2) - (won.GetWidth() / 2), (GetViewPort().height / 2) - (won.GetHeight() / 2) - 15.f));
		Texture streak{ "Highest streak: " + std::to_string((m_pPlayer->GetHighestStreak() == 0 ? m_pPlayer->GetStreak() : m_pPlayer->GetHighestStreak())), "LuckiestGuy-Regular.ttf", 25, Color4f(1.f,1.f,1.f,1.f) };
		streak.Draw(Point2f((GetViewPort().width / 2) - (streak.GetWidth() / 2), GetViewPort().height - streak.GetHeight() - 5.f));
	}
}

void Game::Reset()
{
	delete m_pPlayer;
	delete m_pFruitManager;
	Initialize();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_d:
		m_playerSpeed = m_speed;
		break;
	case SDLK_a:
		m_playerSpeed = -m_speed;
		break;
	default:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_d:
		if(m_playerSpeed == m_speed)
			m_playerSpeed = 0;
		break;
	case SDLK_a:
		if (m_playerSpeed == -m_speed)
			m_playerSpeed = 0;
		break;
	case SDLK_r:
		if(!m_pPlayer->isAlive() or hasWon)
			Reset();
	default:
		break;
	}
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
