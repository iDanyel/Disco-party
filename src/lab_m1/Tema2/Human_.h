#pragma once

#include "Entity_.h"

namespace m1 {
	class Human_ : public Entity_ {
	protected:
		struct Footstep_ {
			Footstep_(const glm::vec3& center, const glm::vec3& size, const float angle, Game_* const game);

			Game_* game;
			float angle, lifespan, initialLifespan;
			glm::mat4 modelMatrix;
			glm::vec3 center, size, color, floorColor;

			bool endOfLife();

			void update(const float dt);
			void draw();
		};

		float maxLife, currLife, speed, recoil;
		float currEnergy, maxEnergy;
		float onGroundMovingTime, cooldown, timeSinceLastBullet;
		glm::vec3 forwardVector, rightVector, upVector;
		glm::vec3 collisionBlock;

		bool isDeformed, wasFired;
		int rightLegDirBeforeJump;

		glm::vec3 skinColor, shirtColor, pantsColor, gunColor;
		float headBodyDistance, legsBodyDistance, legsDistance;

		bool doesntMove;
		bool simpleJump, doubleJump, freeFall;
		bool isWalking, isRunning, isAiming;
		float armAngleZ, headAngleX, headAngleY, thighAngleX;
		float bodyAngleY, calfAngleX, armAngleX, forearmAngleX;

		int armRotationZDirection;
		int headRotationXDirection;
		int headRotationYDirection;

		int thighRotationXDirection;
		int calfRotationXDirection;
		int armRotationXDirection;
		int forearmRotationXDirection;

		float bootScaleY, calfScaleY, thighScaleY, bodyScaleY, headScaleY;
		float armScaleY, forearmScaleY, fistScaleY, gunScaleY;

		float gunOffsetAngleX, gunOffsetDirX;
		float reloadHandOffsetAngleX, reloadHandOffsetDirX;
		float reloadHandOffsetAngleY, reloadHandOffsetDirY;

		bool reloaded;
		bool freshlyFired;

		glm::vec3 leftBootPos, rightBootPos;
		float cameraAngleY, cameraAngleX;

		std::vector<Bullet_*> bullets;
		std::vector<Footstep_*> footsteps;

	public:
		Human_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game);

		void setSkinColor(const glm::vec3& skinColor);
		void setShirtColor(const glm::vec3& shirtColor);
		void setPantsColor(const glm::vec3& pantsColor);
		void setMovement(bool isWalking = true, bool isRunning = false);
		void setDeformity(const float isDeformed);
		void setAiming(const float isAiming);

		float getSpeed();
		float getCurrSpeed();
		glm::vec3 getForwardVector();
		glm::vec3 getRightVector();
		glm::vec3 getUpVector();
		glm::vec3 getDirZ();
		glm::vec3 getDirX();
		float getCurrEnergy();
	
		void takeDamage(const float damage);

		bool canFire();
		bool canAddFootstep();

		bool obstacleCollision(const glm::vec3& pos, Obstacle_* obstacle);
		bool canMove(const char dir, const float dt);
		bool getDeformityStatus();

		void moveForward(const float dt);
		void moveRight(const float dt);

		void rotate(const float angle);
		void addFootstep();

		void update(const float dt) override;
		void draw() override;
	};
};
