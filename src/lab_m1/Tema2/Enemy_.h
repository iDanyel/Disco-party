#pragma once

#include "Human_.h"

namespace m1 {
	class Enemy_ : public Human_ {
	private:
		char dir;
		float timeSinceLastDirSwitch, timeSinceDeformed;

	public:
		Enemy_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game);

		void move(const float dt);

		bool endOfLife();

		void update(const float dt);
		void draw();
	};
};