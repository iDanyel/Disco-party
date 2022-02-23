#include "Wall.h"

m1::Wall::Wall(const glm::vec3& pos, const glm::vec3& size, Game__* const game) {
	this->pos = pos; this->size = size; this->game = game;
}

void m1::Wall::draw() {
	std::vector<Game__::LightSource> currLightCells = game->lightCells;

	std::sort(currLightCells.begin(), currLightCells.end(), [&](const auto& light1, const auto& light2) {
		return glm::distance(pos, light1.pos) < glm::distance(pos, light2.pos);
	});

	game->modelMatrix = glm::mat4(1);
	game->modelMatrix = glm::translate(game->modelMatrix, pos);
	game->modelMatrix = glm::scale(game->modelMatrix, size);
	game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework3Shader"], game->modelMatrix, {}, true, false, true, true, {0, 0, 0});
	game->RenderSimpleMesh(game->meshes["box"], game->shaders["homework3Shader"], game->modelMatrix, currLightCells, false, false, true, true, {0, 0, 0});
}
