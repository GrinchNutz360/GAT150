#include "Actor.h"
#include "Renderer/Renderer.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{
		if(destroyed)return;

		if(lifeSpan != 0.0f) {
			lifeSpan -= dt;
			destroyed = lifeSpan <= 0;
		}

		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		if (destroyed){
			return;
		}
		renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
		//m_model->Draw(renderer, m_transform);
	}
	
	float Actor::GetRadius()
	{
		return (m_texture) ? (m_texture->GetSize().Length() * 0.5f) * m_transform.scale * 0.9f: 0.0f;
	}
}
