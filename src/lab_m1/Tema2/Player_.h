#pragma once

#include "Human_.h"

namespace m1 {
	class Player_ : public Human_ {
	private:
		float totalTime;
		float jumpSpeed, oldJumpSpeed, bodyOffsetY, simpleJumpOffsetY;
		float ascentTime, prevAscentTime, descentTime, f, g;
		float armAngleDiffBetweenJumps, headAngleDiffBetweenJumps;
		float thighAngleDiffBetweenJumps, calfAngleDiffBetweenJumps;

	public:
		Player_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game);

		void jump();
		void addBullet();
		glm::vec3 getGunPos();

		bool canJump();
		bool gameOver();
		bool won();

		void update(const float dt) override;
		void draw();
	};
};
