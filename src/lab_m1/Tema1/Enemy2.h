#pragma once

#include "Enemy.h"

namespace m1 {
	class Enemy2 : public Enemy {
	private:
		float bodyRadians;
		float cannonRadians;

		float wheelOffset;
		float cannonOffset;

		int wheelMoveDirection;
		int cannonMoveDirection;

		bool powerup;

		float timeSinceLastPowerUp;
		float timeSinceLastBullet;

		float powerUpTime;

		void drawWheel(int index);
		void drawWheels();
		void drawBody();
		void drawWeapon();
		void drawHealthBar();

	public:
		Enemy2(const glm::vec3& pos, const std::pair<float, float>& size, const float speed,
			   const float bodyRadians, const float maxHealth, Game* const game);

		glm::vec3 getPos() override;
		float getSpeed() override;
		std::pair<float, float> getSize() override;

		glm::vec3 getCannon1Pos();
		glm::vec3 getCannon2Pos();

		bool playerCollision(glm::vec3 pos, Player* const player) override;
		bool obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) override;
		bool canMove(glm::vec3 pos);

		void takeDamage(const float damage) override;
		void update(const float dt) override;
		void draw() override;
	};
};
