#include "DanceFloor.h"

m1::DanceFloor::DanceFloor(const glm::vec3& pos, const glm::ivec2& gridSize, const glm::vec3& cellSize, Game__* const game) {
	this->pos = pos; this->gridSize = gridSize; this->cellSize = cellSize; this->game = game;

	for (int i = 0; i < gridSize.x * gridSize.y; i++) {
		Cell cell;

		int row = i / gridSize.x;
		int column = i % gridSize.y;

		float r = (float)(rand() % 255) / 255;
		float g = (float)(rand() % 255) / 255;
		float b = (float)(rand() % 255) / 255;

		cell.pos.x = pos.x - gridSize.x * cellSize.x / 2 + cellSize.x / 2 + row * cellSize.x;
		cell.pos.y = pos.y;
		cell.pos.z = pos.z - gridSize.y * cellSize.z / 2 + cellSize.z / 2 + column * cellSize.z;

		cell.color = {r, g, b};
		cell.timeSinceLastDirSwitch = 0;

		int randomNo1 = rand() % 2;
		int randomNo2 = rand() % 2;
		int randomNo3 = rand() % 2;

		if (randomNo1 == 1)
			cell.dir1 = 1;
		else
			cell.dir1 = -1;

		if (randomNo2 == 1)
			cell.dir2 = 1;
		else
			cell.dir2 = -1;

		if (randomNo3 == 1)
			cell.dir3 = 1;
		else
			cell.dir3 = -1;

		cell.randomFactor = (float)(10 + rand() % 20) / 7500;
		cell.randomTime = 2 + rand() % 3;

		cells.push_back(cell);
	}
}

glm::vec3 m1::DanceFloor::getPos() {
	return pos;
}

glm::ivec2 m1::DanceFloor::getGridSize() {
	return gridSize;
}

glm::vec3 m1::DanceFloor::getCellSize() {
	return cellSize;
}

std::vector<m1::Game__::LightSource> m1::DanceFloor::computeLights() {
	std::vector<Game__::LightSource> lights;

	for (const auto& cell : cells)
		lights.push_back({cell.pos, cell.color, {0, 1, 0}, 1.5f, false});

	return lights;
}

void m1::DanceFloor::update(const float dt) {
	for (auto& cell : cells) {
		cell.timeSinceLastDirSwitch += dt;

		if (cell.timeSinceLastDirSwitch > cell.randomTime) {
			cell.timeSinceLastDirSwitch = 0;
			cell.dir1 *= -1;
			cell.dir2 *= -1;
			cell.dir3 *= -1;
		}

		cell.color.x += cell.dir1 * cell.randomFactor;
		cell.color.y += cell.dir2 * cell.randomFactor;
		cell.color.z += cell.dir3 * cell.randomFactor;
	}
}

void m1::DanceFloor::draw(bool opaque) {
	for (const auto& cell : cells) {
		game->modelMatrix = glm::mat4(1);
		game->modelMatrix = glm::translate(game->modelMatrix, cell.pos);
		game->modelMatrix = glm::scale(game->modelMatrix, cellSize);

		if (!opaque) {
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework3Shader"], game->modelMatrix, {}, true, false, true, true, {0, 0, 0});
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework3Shader"], game->modelMatrix, {}, true, false, true, true, cell.color);
		} else
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework3Shader"], game->modelMatrix, {}, true, false, true, true, {0, 0, 0});
	}
}

