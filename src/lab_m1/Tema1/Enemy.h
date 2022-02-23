#pragma once

#include "Entity.h"

namespace m1 {
	class Enemy : public Entity {
	protected:
		float currHealth, maxHealth;

	public:
		Enemy(const glm::vec3& pos, const std::pair<float, float>& size,
			 const float maxHealth, const float speed, Game* const game);

		virtual bool obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) = 0;
		virtual bool playerCollision(glm::vec3 pos, Player* const player) = 0;
		virtual void takeDamage(const float damage) = 0;
		virtual float getHealth();

		std::vector<Bullet*> bullets;
	};
};