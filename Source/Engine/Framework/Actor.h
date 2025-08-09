#pragma once
#include "Renderer/Texture.h"
#include "Math/Transform.h"
#include <memory>
#include <string>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;


		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifeSpan{ 0.0f };

		class Scene* scene{ nullptr };


	public:
		Actor() = default;
		Actor(const Transform& transform, res_t<Texture> texture) :
			m_transform{ transform } 
			, m_texture{ texture }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		Transform& GetTransform() { return m_transform; }

	public:
		Transform m_transform;
		//std::shared_ptr<Model> m_model;
	protected:
		res_t<Texture> m_texture;
	};
}