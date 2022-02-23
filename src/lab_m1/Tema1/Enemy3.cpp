#include "Enemy3.h"
#include "Player.h"
#include "Obstacle.h"

#include "lab_m1/lab4/transform3D.h"

void m1::Enemy3::drawWheel(int index) {
	float offsetX, offsetY;

	if (index == 1 || index == 2)
		offsetX = size.first / 2;
	else
		offsetX = -size.first / 2;

	if (index == 2 || index == 3)
		offsetY = -size.second / 2;
	else
		offsetY = size.second / 2;

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 0);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 1);
	modelMatrix *= transform3D::Scale(0.075 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("lightPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(1.1 * offsetX, (offsetY + wheelOffset) / 2.25, 0);
	modelMatrix *= transform3D::Scale(0.1 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy3::drawWheels() {
	for (int i = 0; i < 4; i++)
		drawWheel(i);
}

void m1::Enemy3::drawBody() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 2);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 3);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.9 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("lightPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 3, 4);
	modelMatrix *= transform3D::Scale(0.7 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 3, 5);
	modelMatrix *= transform3D::Scale(0.65 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 5, size.second / 8.5, 4);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 5, size.second / 8.5, 5);
	modelMatrix *= transform3D::Scale(0.1 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 4);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.5 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 5);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.1 * size.first, 0.45 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 5, size.second / 8.5, 4);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 5, size.second / 8.5, 5);
	modelMatrix *= transform3D::Scale(0.1 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, -size.second / 6, 4);
	modelMatrix *= transform3D::Scale(0.5 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, -size.second / 6, 5);
	modelMatrix *= transform3D::Scale(0.4 * size.first, 0.8 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, -size.second / 6, 4);
	modelMatrix *= transform3D::Scale(0.5 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackReversedTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, -size.second / 6, 5);
	modelMatrix *= transform3D::Scale(0.4 * size.first, 0.8 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleReversedTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.125 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.075 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy3::drawWeapon() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, size.second / 2 + thornOffset, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3, size.second / 2 + thornOffset, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3.5, 0.75 * size.second + thornOffset, 4);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackReversedTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.5 * size.second + thornOffset, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.4 * size.second + thornOffset, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-0.05 * size.first, 0.85 * size.second + thornOffset, 4);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.4 * size.second, 1);
	game->RenderMesh(game->getMesh("blackReversedTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0.05 * size.first, 0.85 * size.second + thornOffset, 1);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.4 * size.second, 1);
	game->RenderMesh(game->getMesh("blackTriangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, size.second / 2 + thornOffset, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3, size.second / 2 + thornOffset, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("darkPurpleRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3.5, 0.75 * size.second + thornOffset, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackTriangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy3::drawHealthBar() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first, size.second / 2, 20);
	modelMatrix *= transform3D::Scale(0.5 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("blackUnfilledRectangle"), game->getShader("VertexColor"), modelMatrix);

	if (currHealth > 0) {
		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
		modelMatrix *= transform3D::RotateOZ(-radians);
		modelMatrix *= transform3D::Translate(size.first - (1 - currHealth / maxHealth) * size.first / 4, size.second / 2, 20);
		modelMatrix *= transform3D::Scale(0.5 * size.first * currHealth / maxHealth, 0.1 * size.second, 1);
		game->RenderMesh(game->getMesh("redRectangle"), game->getShader("VertexColor"), modelMatrix);
	}
}

m1::Enemy3::Enemy3(const glm::vec3& pos, const std::pair<float, float>& size,
				   const float speed, const float radians, const float maxHealth, Game* const game) : Enemy(pos, size, speed, maxHealth, game) {
	this->radians = radians;

	wheelOffset = 0;
	thornOffset = 0;

	wheelMoveDirection = 1;
	thornMoveDirection = 1;

	timeInArea = 0;
	powerUp = false;
}

bool m1::Enemy3::endOfPowerup() {
	for (const auto& obstacle : game->walls)
		if (obstacleCollision(pos, obstacle))
			return true;

	return false;
}

glm::vec3 m1::Enemy3::getPos() {
	return pos;
}

float m1::Enemy3::getSpeed() {
	return speed;
}

std::pair<float, float> m1::Enemy3::getSize() {
	return size;
}

bool m1::Enemy3::playerCollision(glm::vec3 pos, Player* const player) {
	float radius1 = std::min(size.first, size.second);
	float radius2 = std::min(player->getSize().first, player->getSize().second);

	return game->getEuclidianDistance(pos, player->getPos()) <= radius1 + radius2;
}

bool m1::Enemy3::obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) {
	glm::vec2 halfSize(obstacle->getSize().first / 2, obstacle->getSize().second / 2);
	glm::vec2 difference = pos - obstacle->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = obstacle->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < std::max(size.first / 2, size.second / 2);
}

bool m1::Enemy3::canMove(glm::vec3 pos) {
	for (const auto& wall : game->walls)
		if (obstacleCollision(pos, wall))
			return false;

	return true;
}

void m1::Enemy3::takeDamage(const float damage) {
	currHealth -= damage;
}

void m1::Enemy3::update(const float dt) {
	if (game->player->isFreshlySpawned())
		return;

	glm::vec3 oldPos = pos;
	float oldRadians = radians;

	time += dt;
	counter++;

	if (!powerUp) {
		radians = game->getAngle(pos, game->player->getPos());

		if (radians) {
			if (canMove({pos.x + speed * cos(radians) * dt, pos.y + speed * sin(radians) * dt, pos.z})) {
				pos.x += speed * cos(radians) * dt;
				pos.y += speed * sin(radians) * dt;
			}

			if (pos != oldPos || game->convertAngle(radians, -glm::pi<float>() / 2) != oldRadians) {
				if (!(counter % 3))
					wheelMoveDirection *= -1;

				if (!(counter % 5))
					thornMoveDirection *= -1;

				wheelOffset = counter % 3 * 0.75 * wheelMoveDirection * dt;
				thornOffset = counter % 5 * 0.25 * thornMoveDirection * dt;
			}
		} else {
			wheelOffset = 0;
			thornOffset = 0;

			wheelMoveDirection = 1;
			thornMoveDirection = 1;
		}

		if (game->getEuclidianDistance(pos, game->player->getPos()) < 3 * (size.first + game->player->getSize().first))
			timeInArea += dt;
		else
			timeInArea = 0;

		radians = game->convertAngle(radians, -glm::pi<float>() / 2);

		if (timeInArea >= 3) {
			powerUp = true;
			speed *= 10;
			size.second *= 1.2;
		}
	} else {
		if (endOfPowerup()) {
			powerUp = false;
			speed /= 10;
			size.second /= 1.2;
			timeInArea = 0;
		} else {
			pos.x += speed * cos(game->convertAngle(radians, glm::pi<float>() / 2)) * dt;
			pos.y += speed * sin(game->convertAngle(radians, glm::pi<float>() / 2)) * dt;
		}

		if (!(counter % 3))
			wheelMoveDirection *= -1;

		if (!(counter % 5))
			thornMoveDirection *= -1;

		wheelOffset = counter % 3 * 0.75 * wheelMoveDirection * dt;
		thornOffset = counter % 5 * 0.25 * thornMoveDirection * dt;
	}
}

void m1::Enemy3::draw() {
	drawWheels();
	drawBody();
	drawWeapon();
	drawHealthBar();
}
