#pragma once

#include "Enemy.h"

namespace m1 {
	class Enemy3 : public Enemy {
	private:
		float radians;

		float wheelOffset;
		float thornOffset;

		int wheelMoveDirection;
		int thornMoveDirection;

		float timeInArea;
		bool powerUp;

		void drawWheel(int index);
		void drawWheels();
		void drawBody();
		void drawWeapon();
		void drawHealthBar();

	public:
		Enemy3(const glm::vec3& pos, const std::pair<float, float>& size,
			   const float speed, const float radians, const float maxHealth, Game* const game);

		bool endOfPowerup();

		glm::vec3 getPos() override;
		float getSpeed() override;
		std::pair<float, float> getSize() override;

		bool playerCollision(glm::vec3 pos, Player* const player) override;
		bool obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) override;
		bool canMove(glm::vec3 pos);

		void takeDamage(const float damage) override;
		void update(const float dt) override;
		void draw() override;
	};
};
