#include "Bullet_.h"

m1::Bullet_::Bullet_(const glm::vec3& center, const glm::vec3& size, const float speed, const float lifeSpan, const float angleX, const float angleY,
					 const glm::vec3& forwardVector, const glm::vec3& right, const glm::vec3& upVector, Game_* const game) : Entity_(center, size, game) {
	this->speed = speed; this->lifeSpan = lifeSpan; this->angleX = angleX; this->angleY = angleY;
	this->forwardVector = forwardVector; this->rightVector = rightVector; this->upVector = upVector;

	time = 0;
}

bool m1::Bullet_::endOfLife() {
	return lifeSpan <= 0;
}

void m1::Bullet_::update(const float dt) {
	time += dt;
	lifeSpan -= dt;

	center += glm::normalize(glm::vec3(forwardVector.x, forwardVector.y, forwardVector.z)) * speed * dt;
}

void m1::Bullet_::draw() {
	glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);

	{
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, angleY, {0, 1, 0});
		modelMatrix = glm::rotate(modelMatrix, angleX, {1, 0, 0});
		modelMatrix = glm::scale(modelMatrix, halfSize);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});
	}
}
