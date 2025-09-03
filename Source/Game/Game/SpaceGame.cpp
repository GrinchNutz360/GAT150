#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"


bool SpaceGame::Initialize()
{

    OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);

	m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("scene.json");
   

   /* m_titleFont = std::make_shared<viper::Font>();
	m_titleFont->Load("ArcadeClassic.ttf", 128);

    m_uiFont = std::make_shared<viper::Font>();
    m_uiFont->Load("ArcadeClassic.ttf", 48);*/

    m_titleText = std::make_unique < viper::Text>(viper::Resources().GetWithID<viper::Font>("title_Font", "ArcadeClassic.ttf", 128.0f));
    m_livesText = std::make_unique < viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_Font", "ArcadeClassic.ttf", 48.0f));
    m_scoreText = std::make_unique < viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_Font", "ArcadeClassic.ttf", 48.0f));
	/*m_titleText = std::make_unique < viper::Text>(m_titleFont);
    m_scoreText = std::make_unique < viper::Text>(m_uiFont);
    m_livesText = std::make_unique < viper::Text>(m_uiFont);*/
    
	
         return false;
}

void SpaceGame::Shutdown()
{

}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {   

    case SpaceGame::GameState::Initialize:
		m_gameState = SpaceGame::GameState::Title;

        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
		}
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
		m_gameState = GameState::StartRound;

        break;

    case SpaceGame::GameState::StartRound:
    {
		m_scene->RemoveAllActors();
        
		auto player = viper::Instantiate("Player");
        m_scene->AddActor(std::move(player));

		m_gameState = GameState::Game;
    }
        break;
	
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 4;
            SpawnEnemy();
        
        }

        break;

    case SpaceGame::GameState::PlayerDead:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
				m_stateTimer = 3.0f;
                m_gameState = GameState::GameOver;
            }
            else m_gameState = GameState::StartRound;
        }
        break;

    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
		}   
        break;

    default:
        break;
    }
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0 ,0 });
        m_titleText->Draw(renderer, 350, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0 ,0 });
        m_titleText->Draw(renderer, 350, 400);
    }

    m_scoreText->Create(renderer, "SCORE " + std::to_string(m_score), {1,1,1});
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES " + std::to_string(m_lives), {1,1,1});
    m_livesText->Draw(renderer, renderer.GetWidth() - 200.0f, 20.0f);


    m_scene->Draw(renderer);
    
	viper::GetEngine().GetPS().Draw(renderer); 
}

void SpaceGame::OnNotify(const viper::Event& event)
{
    if (viper::equalsIgnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    }
    else if (viper::equalsIgnoreCase(event.id, "add_points")) {
        AddPoints(std::get<int>(event.data));
	}

}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy()
{
   viper::Actor* player = m_scene->GetActorByName<viper::Actor>("Player");
    if (player) {
        viper::vec2 position = player->m_transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform m_tranform{ position, viper::random::getReal(0.0f, 360.0f), 2.0f };

        auto enemy = viper::Instantiate("Enemy", m_tranform);
        m_scene->AddActor(std::move(enemy));
    }
    

}


