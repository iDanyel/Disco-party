#pragma once

#include "Game__.h"

namespace m1 {
	class DanceFloor {
	private:
		struct Cell {
			glm::vec3 pos, color;
			float timeSinceLastDirSwitch;
			int dir1, dir2, dir3;
			float randomFactor, randomTime;
		};

		Game__* game;
		glm::vec3 pos;
		glm::ivec2 gridSize;
		glm::vec3 cellSize;
		std::vector<Cell> cells;

	public:
		DanceFloor(const glm::vec3& pos, const glm::ivec2& gridSize, const glm::vec3& cellSize, Game__* const game);

		glm::vec3 getPos();
		glm::ivec2 getGridSize();
		glm::vec3 getCellSize();

		std::vector<Game__::LightSource> computeLights();

		void update(const float dt);

		void draw(bool opaque = false);
	};
}
