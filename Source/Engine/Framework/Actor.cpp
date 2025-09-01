#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"
namespace viper {
	FACTORY_REGISTER(Actor)
	
	Actor::Actor(const Actor& other) :
		Object{ other },
		tag {other.tag}, 
		lifeSpan{ other.lifeSpan },
		m_transform{ other.m_transform }
	{
		//copy components
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}

	}

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
		JSON_READ(value, persistent);

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
