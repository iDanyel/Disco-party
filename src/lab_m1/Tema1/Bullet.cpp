#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"

#include "lab_m1/lab4/transform3D.h"

m1::Bullet::Bullet(const glm::vec3& pos, const std::pair<float, float> size, const float radians,
				   const float speed, const float lifeSpan, const int type, Game* const game) : Entity(pos, size, speed, game) {
	this->radians = radians; this->lifeSpan = lifeSpan; this->type = type;
}

bool m1::Bullet::enemyCollision(const glm::vec3& pos, Enemy* const enemy) {
	glm::vec2 halfSize(enemy->getSize().first / 2, enemy->getSize().second / 2);
	glm::vec2 difference = pos - enemy->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = enemy->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < 1.05 * std::min(size.first / 2, size.second / 2);
}

bool m1::Bullet::playerCollision(const glm::vec3& pos, Player* const player) {
	glm::vec2 halfSize(player ->getSize().first / 2, player->getSize().second / 2);
	glm::vec2 difference = pos - player->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = player->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < 1.05 * std::min(size.first / 2, size.second / 2);
}

bool m1::Bullet::obstacleCollision(const glm::vec3& pos, Obstacle* const obstacle) {
	glm::vec2 halfSize(obstacle->getSize().first / 2, obstacle->getSize().second / 2);
	glm::vec2 difference = pos - obstacle->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = obstacle->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < 1.05 * std::min(size.first / 2, size.second / 2);
}

bool m1::Bullet::endOfLife() {
	if (lifeSpan <= 0)
		return true;

	for (const auto& wall : game->walls)
		if (obstacleCollision(pos, wall))
			return true;

	for (const auto& obstacle : game->obstacles)
		if (obstacleCollision(pos, obstacle))
			return true;

	return false;
}

void m1::Bullet::update(const float dt) {
	pos.x += speed * dt * cos(game->convertAngle(radians, glm::pi<float>() / 2));
	pos.y += speed * dt * sin(game->convertAngle(radians, glm::pi<float>() / 2));

	lifeSpan -= dt;
}

glm::vec3 m1::Bullet::getPos() {
	return pos;
}

float m1::Bullet::getSpeed() {
	return speed;
}

std::pair<float, float> m1::Bullet::getSize() {
	return size;
}

int m1::Bullet::getType() {
	return type;
}

void m1::Bullet::draw() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, 0, -4);
	modelMatrix *= transform3D::Scale(size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
	
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, 0, -3);
	modelMatrix *= transform3D::Scale(0.7 * size.first, 0.7 * size.second, 1);
	
	if (type == 1)
		game->RenderMesh(game->getMesh("smaraldRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("lightOrangeRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("blueGrayRectangle"), game->getShader("VertexColor"), modelMatrix);
	
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 2, -2);
	modelMatrix *= transform3D::Scale(size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
	
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 2, -1);
	modelMatrix *= transform3D::Scale(0.7 * size.first, 0.15 * size.second, 1);
	
	if (type == 1)
		game->RenderMesh(game->getMesh("limeRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("lightYellowRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("turquoiseRectangle"), game->getShader("VertexColor"), modelMatrix);
	
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, -2);
	modelMatrix *= transform3D::Scale(size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
	
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, -1);
	modelMatrix *= transform3D::Scale(0.7 * size.first, 0.15 * size.second, 1);

	if (type == 1)
		game->RenderMesh(game->getMesh("limeRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("lightYellowRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("turquoiseRectangle"), game->getShader("VertexColor"), modelMatrix);
}
