#include "Obstacle_.h"

// Public methods
m1::Obstacle_::Obstacle_(const glm::vec3& center, const glm::vec3& size, const glm::vec3& color, const bool noBorder, Game_* const game) : Entity_(center, size, game) {
	this->color = color; this->noBorder = noBorder;

	angle = 0;
}

float m1::Obstacle_::getAngle() {
	return angle;
}

void m1::Obstacle_::setAngle(const float angle) {
	this->angle = angle;
}

float m1::Obstacle_::getTime() {
	return currTime;
}

void m1::Obstacle_::update(const float dt) {
	currTime += dt;
}

void m1::Obstacle_::draw() {
	glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);

	{
		if (!noBorder) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, angle, {1, 1, 1});
			modelMatrix = glm::scale(modelMatrix, halfSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, angle, {1, 1, 1});
			modelMatrix = glm::scale(modelMatrix, 0.999f * halfSize);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, color);
		} else {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, angle, {1, 1, 1});
			modelMatrix = glm::scale(modelMatrix, halfSize);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, color);
		}
	}
}
