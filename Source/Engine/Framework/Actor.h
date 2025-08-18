#pragma once
#include "Object.h"
#include "Component.h"
#include "Renderer/Texture.h"
#include "Math/Transform.h"
#include <memory>
#include <string>

namespace viper {
	class Actor : public Object{
	public:
		
		std::string tag;


		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifeSpan{ 0.0f };

		class Scene* scene{ nullptr };


	public:
		Actor() = default;
		Actor(const Transform& transform) :
			m_transform{ transform } 
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		//components
		void AddComponent(std::unique_ptr<Component> component);

		Transform& GetTransform() { return m_transform; }

	public:
		Transform m_transform;
		//std::shared_ptr<Model> m_model;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};
}