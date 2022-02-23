#pragma once

#include "Game__.h"

namespace m1 {
	class Dancer {
	private:
		Game__* game;
		glm::vec3 pos, size;
		std::pair<glm::vec3, glm::vec3> area;
		float rotAngle, speed, angle, spinningTime;
		int rotDir, corners;

	public:
		Dancer(const glm::vec3& pos, const glm::vec3& size, const std::pair<glm::vec3, glm::vec3>& area, const float speed, Game__* const game);

		glm::vec3 getPos();

		bool canMove(const float dt);

		void update(const float dt);

		void draw();
	};
}
