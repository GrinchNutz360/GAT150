#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"
namespace viper {
	void viper::Actor::Update(float dt)
	{
		if(destroyed)return;

		if(lifeSpan != 0.0f) {
			lifeSpan -= dt;
			destroyed = lifeSpan <= 0;
		}

		for (auto& component : m_components) {
			if (component->active)
			component->Update(dt);
		}

		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		if (destroyed){
			return;
		}

		for (auto& component : m_components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}
		//renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
		//m_model->Draw(renderer, m_transform);
	}
	
	float Actor::GetRadius()
	{
		return 50.0f;//(m_texture) ? (m_texture->GetSize().Length() * 0.5f) * m_transform.scale * 0.9f: 0.0f;
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}
