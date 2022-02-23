#pragma once

#include "Game__.h"

namespace m1 {
	class DiscoBall {
	private:
		Game__* game;
		glm::vec3 pos, size;

	public:
		DiscoBall(const glm::vec3& pos, const glm::vec3& size, Game__* const game);

		glm::vec3 getPos();
		glm::vec3 getSize();

		void draw();
	};
}
