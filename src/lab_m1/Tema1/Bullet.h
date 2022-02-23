#pragma once

#include "Entity.h"

namespace m1 {
	class Bullet : public Entity {
	private:
		glm::mat4 modelMatrix;

		int type;

		float radians;
		float lifeSpan;

	public:
		Bullet(const glm::vec3& pos, const std::pair<float, float> size, const float radians,
			   const float speed, const float lifeSpan, const int type, Game* const game);

		bool enemyCollision(const glm::vec3& pos, Enemy* const enemy);
		bool playerCollision(const glm::vec3& pos, Player* const player);
		bool obstacleCollision(const glm::vec3& pos, Obstacle* const obstacle);

		bool endOfLife();

		glm::vec3 getPos() override;
		float getSpeed() override;
		std::pair<float, float> getSize() override;
		int getType();

		void update(const float dt) override;
		void draw() override;
	};
}
