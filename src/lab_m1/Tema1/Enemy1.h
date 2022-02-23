#pragma once

#include "Enemy.h"

namespace m1 {
	class Enemy1 : public Enemy {
	private:
		float radians;

		float wheelOffset;
		float gunOffset;

		int wheelMoveDirection;
		int gunMoveDirection;

		float timeSinceLastBullet;

		void drawWheel(int index);
		void drawWheels();
		void drawBody();
		void drawWeapon();
		void drawHealthBar();

	public:
		Enemy1(const glm::vec3& pos, const std::pair<float, float>& size,
			   const float speed, const float radians, const float maxHealth, Game* const game);

		glm::vec3 getCannon1Pos();
		glm::vec3 getCannon2Pos();
		std::vector<Bullet*> getBullets();

		glm::vec3 getPos() override;
		float getSpeed() override;
		std::pair<float, float> getSize() override;

		bool playerCollision(glm::vec3 pos, Player* const player) override;
		bool obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) override;
		bool canMove(glm::vec3 pos);

		void takeDamage(const float damage);
		void update(const float dt) override;
		void draw() override;
	};
};
