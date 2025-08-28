#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"
namespace viper {
	FACTORY_REGISTER(Actor)

	void viper::Actor::Update(float dt)
	{
		if(destroyed)return;



		if(lifeSpan > 0.0f) {
			lifeSpan -= dt;
			if (lifeSpan < -0) {
				destroyed = true;
				return;
			}
		}
		//update all components
		for (auto& component : m_components) {
			if (component->active)
			component->Update(dt);
		}
			
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

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		m_components.push_back(std::move(component));
	}
	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifeSpan);

		if (JSON_HAS(value, m_transform)) m_transform.Read(JSON_GET(value, m_transform));

		//read components
		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {

				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}
}
