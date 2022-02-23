#include "DiscoBall.h"

m1::DiscoBall::DiscoBall(const glm::vec3& pos, const glm::vec3& size, Game__* const game) {
	this->pos = pos; this->size = size; this->game = game;
}

glm::vec3 m1::DiscoBall::getPos() {
	return pos;
}

glm::vec3 m1::DiscoBall::getSize() {
	return size;
}

void m1::DiscoBall::draw() {
	game->modelMatrix = glm::mat4(1);
	game->modelMatrix = glm::translate(game->modelMatrix, pos);
	game->modelMatrix = glm::scale(game->modelMatrix, size);
	game->RenderSimpleMesh(game->meshes["sphere"], game->shaders["homework3Shader"], game->modelMatrix, {}, false, false, false, false, {}, game->mapTextures["randomTexture"]);
}
