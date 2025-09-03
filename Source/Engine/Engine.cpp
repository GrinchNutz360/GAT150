#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystems.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.H"


namespace viper {

	bool Engine::Initialize() {
		m_renderer = std::make_unique<Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWinow("Viper Engine", 1200, 1024, false);

		m_input= std::make_unique<InputSystem>();
		m_input->Initialize();

		m_audio= std::make_unique<AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<ParticleSystem>();
		m_particleSystem->Initialize(5000);

		m_physics = std::make_unique<Physics>();
		m_physics->Initialize();

		return true;
	}

	void Engine::Shutdown() {
		//release resources from resource manager
		Resources().Clear();
		Factory::Instance().RemoveAll();
		EventManager::Instance().RemoveAll();

		//shudown engine systems
		m_particleSystem->Shutdown();
		m_audio->Shutdown();
		m_renderer->Shutdown();
		m_input->Shutdown();
		m_physics->Shutdown();
	}
	
	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
		m_physics->Update(m_time.GetDeltaTime());
	}
	void Engine::Draw()
	{

	}
}