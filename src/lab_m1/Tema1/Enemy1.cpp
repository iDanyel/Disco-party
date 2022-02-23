#include "Enemy1.h"
#include "Player.h"
#include "Obstacle.h"
#include "Bullet.h"

#include "lab_m1/lab4/transform3D.h"

class Bullet;

void m1::Enemy1::drawWheel(int index) {
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
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(1.1 * offsetX, (offsetY + wheelOffset) / 2.25, 0);
	modelMatrix *= transform3D::Scale(0.1 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy1::drawWheels() {
	for (int i = 0; i < 4; i++)
		drawWheel(i);
}

void m1::Enemy1::drawBody() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 2);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 3);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.9 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("orangeRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 5, 0, 4);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 5, 0, 5);
	modelMatrix *= transform3D::Scale(0.05 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 4);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.3 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 5);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Scale(0.05 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 5, 0, 4);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 5, 0, 5);
	modelMatrix *= transform3D::Scale(0.05 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 3.5, 4);
	modelMatrix *= transform3D::Scale(0.75 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 3.5, 5);
	modelMatrix *= transform3D::Scale(0.65 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 3.5, 4);
	modelMatrix *= transform3D::Scale(0.75 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 3.5, 5);
	modelMatrix *= transform3D::Scale(0.65 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.4 * size.first, 0.075 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3.5, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.4 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-size.first / 3.5, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3.5, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.4 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(size.first / 3.5, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy1::drawWeapon() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0, size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-0.25 * size.first, size.second / 2 + gunOffset, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.8 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-0.25 * size.first, size.second / 2 + gunOffset, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.7 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0.25 * size.first, size.second / 2 + gunOffset, 0);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.8 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0.25 * size.first, size.second / 2 + gunOffset, 1);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.7 * size.second, 1);
	game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-0.25 * size.first, 0.8 * size.second + gunOffset, 2);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0.25 * size.first, 0.8 * size.second + gunOffset, 2);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 2);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(-0.25 * size.first, 0.7 * size.second + gunOffset, 2);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-radians);
	modelMatrix *= transform3D::Translate(0.25 * size.first, 0.7 * size.second + gunOffset, 2);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy1::drawHealthBar() {
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

m1::Enemy1::Enemy1(const glm::vec3& pos, const std::pair<float, float>& size,
				   const float speed, const float radians, const float maxHealth, Game* const game) : Enemy(pos, size, speed, maxHealth, game) {
	this->radians = radians;

	wheelOffset = 0;
	gunOffset = 0;

	wheelMoveDirection = 1;
	gunMoveDirection = 1;

	timeSinceLastBullet = 0;
}

glm::vec3 m1::Enemy1::getCannon1Pos() {
	glm::vec3 cannon1Pos(-0.25 * size.first, size.second, pos.z);

	cannon1Pos = glm::vec3(cannon1Pos.x * cos(radians) - cannon1Pos.y * sin(radians),
		cannon1Pos.x * sin(radians) + cannon1Pos.y * cos(radians),
		cannon1Pos.z);
	cannon1Pos += glm::vec3(pos.x, pos.y, 0);

	return cannon1Pos;
}

glm::vec3 m1::Enemy1::getCannon2Pos() {
	glm::vec3 cannon1Pos(0.25 * size.first, size.second, pos.z);

	cannon1Pos = glm::vec3(cannon1Pos.x * cos(radians) - cannon1Pos.y * sin(radians),
		cannon1Pos.x * sin(radians) + cannon1Pos.y * cos(radians),
		cannon1Pos.z);
	cannon1Pos += glm::vec3(pos.x, pos.y, 0);

	return cannon1Pos;
}

glm::vec3 m1::Enemy1::getPos() {
	return pos;
}

float m1::Enemy1::getSpeed() {
	return speed;
}

std::pair<float, float> m1::Enemy1::getSize() {
	return size;
}

bool m1::Enemy1::playerCollision(glm::vec3 pos, Player* const player) {
	float radius1 = std::min(size.first, size.second);
	float radius2 = std::min(player->getSize().first, player->getSize().second);

	return game->getEuclidianDistance(pos, player->getPos()) <= radius1 + radius2;
}

bool m1::Enemy1::obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) {
	glm::vec2 halfSize(obstacle->getSize().first / 2, obstacle->getSize().second / 2);
	glm::vec2 difference = pos - obstacle->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = obstacle->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < std::max(size.first / 2, size.second / 2);
}

bool m1::Enemy1::canMove(glm::vec3 pos) {
	for (const auto& wall : game->walls)
		if (obstacleCollision(pos, wall))
			return false;

	return true;
}

void m1::Enemy1::takeDamage(const float damage) {
	currHealth -= damage;
}

void m1::Enemy1::update(const float dt) {
	if (game->player->isFreshlySpawned())
		return;

	glm::vec3 oldPos = pos;
	float oldRadians = radians;

	time += dt;
	counter++;

	radians = game->getAngle(pos, game->player->getPos());

	if (radians) {
		if (canMove({ pos.x + speed * cos(radians) * dt, pos.y + speed * sin(radians) * dt, pos.z }))
			if (game->getEuclidianDistance(pos, game->player->getPos()) > 2 * (size.first + game->player->getSize().first)){
				pos.x += speed * cos(radians) * dt;
				pos.y += speed * sin(radians) * dt;
			}

		if (pos != oldPos || game->convertAngle(radians, -glm::pi<float>() / 2) != oldRadians) {
			if (!(counter % 3))
				wheelMoveDirection *= -1;

			if (!(counter % 5))
				gunMoveDirection *= -1;

			wheelOffset = counter % 3 * 0.5 * wheelMoveDirection * dt;
			gunOffset = counter % 5 * 0.25 * gunMoveDirection * dt;
		}
	} else {
		wheelOffset = 0;
		gunOffset = 0;

		wheelMoveDirection = 1;
		gunMoveDirection = 1;
	}

	radians = game->convertAngle(radians, -glm::pi<float>() / 2);
	timeSinceLastBullet += dt;

	if (timeSinceLastBullet >= 0.25) {
		bullets.push_back(new Bullet(getCannon1Pos(), {size.first / 8, size.second / 5}, radians, speed + 5, 2, 2.5, game));
		bullets.push_back(new Bullet(getCannon2Pos(), {size.first / 8, size.second / 5}, radians, speed + 5, 2, 2.5, game));
		timeSinceLastBullet = 0;
	}

	std::vector<Bullet*> remainingBullets;

	for (const auto& bullet : bullets)
		if (bullet->endOfLife())
			delete bullet;
		else {
			bullet->update(dt);

			if (!game->player->isFreshlySpawned() && bullet->playerCollision(bullet->getPos(), game->player)) {
				game->player->takeDamage(5);
				delete bullet;
			}
			else
				remainingBullets.push_back(bullet);
		}

	bullets.erase(bullets.begin(), bullets.end());

	for (const auto& bullet : remainingBullets)
		bullets.push_back(bullet);
}

void m1::Enemy1::draw() {
	drawWheels();
	drawBody();
	drawWeapon();
	drawHealthBar();

	for (const auto& bullet : bullets)
		bullet->draw();
}
