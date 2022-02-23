#pragma once

#include "Game__.h"

namespace m1 {
	class Wall {
	private:
		Game__* game;
		glm::vec3 pos, size;

	public:
		Wall(const glm::vec3& pos, const glm::vec3& size, Game__* const game);

		void draw();
	};
}
