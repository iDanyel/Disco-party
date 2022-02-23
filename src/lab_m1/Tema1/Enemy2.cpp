#include "Enemy2.h"
#include "Player.h"
#include "Bullet.h"
#include "Obstacle.h"

#include "lab_m1/lab4/transform3D.h"

void m1::Enemy2::drawWheel(int index) {
	float offsetX, offsetY;

	if (index == 1 || index == 2 || index == 3)
		offsetX = size.first / 2;
	else
		offsetX = -size.first / 2;

	if (index == 1 || index == 4)
		offsetY = -size.second / 1.5;
	else if (index == 2 || index == 5)
		offsetY = size.second / 1.5;
	else
		offsetY = 0;

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 0);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.25 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 1);
	modelMatrix *= transform3D::Scale(0.075 * size.first, 0.175 * size.second, 1);
	game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(1.1 * offsetX, (offsetY + wheelOffset) / 2.25, 0);
	modelMatrix *= transform3D::Scale(0.125 * size.first, 0.2 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy2::drawWheels() {
	for (int i = 0; i < 6; i++)
		drawWheel(i);
}

void m1::Enemy2::drawBody() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 2);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Scale(0.33 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 3);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-0.33 * size.first, 0, 2);
	modelMatrix *= transform3D::Scale(0.33 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-0.33 * size.first, 0, 3);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(0.33 * size.first, 0, 2);
	modelMatrix *= transform3D::Scale(0.33 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(0.33 * size.first, 0, 3);
	modelMatrix *= transform3D::Scale(0.25 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 4);
	modelMatrix *= transform3D::Scale(0.75 * size.first / 2, 0.75 * size.second / 2, 1);
	game->RenderMesh(game->getMesh("blackCircle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 5);
	modelMatrix *= transform3D::Scale(0.65 * size.first / 2, 0.65 * size.second / 2, 1);
	game->RenderMesh(game->getMesh("lightBlueCircle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 2);
	modelMatrix *= transform3D::Scale(0.85 * size.first, 0.075 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.75 * size.first, 0.175 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(0, -size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.65 * size.first, 0.125 * size.second, 1);
	game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 2.5, size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 2.5, size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.075 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 2.5, size.second / 2, 0);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.15 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 2.5, size.second / 2, 1);
	modelMatrix *= transform3D::Scale(0.075 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy2::drawWeapon() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 7.5, size.second / 2.5 + cannonOffset, 6);
	modelMatrix *= transform3D::Scale(0.3 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 7.5, size.second / 2.5 + cannonOffset, 7);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 7.5, size.second / 2.5 + cannonOffset, 6);
	modelMatrix *= transform3D::Scale(0.3 * size.first, size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 7.5, size.second / 2.5 + cannonOffset, 7);
	modelMatrix *= transform3D::Scale(0.2 * size.first, 0.9 * size.second, 1);
	game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y - size.second / 7.5, pos.z + 8);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Scale(0.35 * size.first, 0.25 * size.second + cannonOffset, 8);
	game->RenderMesh(game->getMesh("blackCircle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y - size.second / 7.5, pos.z + 9);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Scale(0.3 * size.first, 0.2 * size.second + cannonOffset, 1);
	game->RenderMesh(game->getMesh("lightBlueCircle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 7.5, 0.8 * size.second + cannonOffset, 8);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(-size.first / 7.5, 0.7 * size.second + cannonOffset, 8);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 7.5, 0.8 * size.second + cannonOffset, 8);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Translate(0, -size.second / 7.5, 0);
	modelMatrix *= transform3D::RotateOZ(-cannonRadians);
	modelMatrix *= transform3D::Translate(0, size.second / 7.5, 0);
	modelMatrix *= transform3D::Translate(size.first / 7.5, 0.7 * size.second + cannonOffset, 8);
	modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Enemy2::drawHealthBar() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::RotateOZ(-bodyRadians);
	modelMatrix *= transform3D::Translate(1.1 * size.first, size.second / 1.75, 20);
	modelMatrix *= transform3D::Scale(0.5 * size.first, 0.1 * size.second, 1);
	game->RenderMesh(game->getMesh("blackUnfilledRectangle"), game->getShader("VertexColor"), modelMatrix);

	if (currHealth > 0) {
		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
		modelMatrix *= transform3D::RotateOZ(-bodyRadians);
		modelMatrix *= transform3D::Translate(1.1 * size.first - (1 - currHealth / maxHealth) * 1.1 * size.first / 4, size.second / 1.75, 20);
		modelMatrix *= transform3D::Scale(0.5 * size.first * currHealth / maxHealth, 0.1 * size.second, 1);
		game->RenderMesh(game->getMesh("redRectangle"), game->getShader("VertexColor"), modelMatrix);
	}
}

m1::Enemy2::Enemy2(const glm::vec3& pos, const std::pair<float, float>& size, const float speed,
				   const float bodyRadians, const float maxHealth, Game* const game) : Enemy(pos, size, speed, maxHealth, game) {
	this->bodyRadians = bodyRadians;

	wheelOffset = 0;
	cannonOffset = 0;

	wheelMoveDirection = 1;
	cannonMoveDirection = 1;

	timeSinceLastPowerUp = 0;
	timeSinceLastBullet = 0;

	cannonRadians = bodyRadians;
	powerup = false;
}

glm::vec3 m1::Enemy2::getPos() {
	return pos;
}

float m1::Enemy2::getSpeed() {
	return speed;
}

std::pair<float, float> m1::Enemy2::getSize() {
	return size;
}

glm::vec3 m1::Enemy2::getCannon1Pos() {
	glm::vec3 cannon1Pos(-size.first / 7.5, size.second, pos.z);

	cannon1Pos += glm::vec3(0, size.second / 7.5, 0);
	cannon1Pos = glm::vec3(cannon1Pos.x * cos(cannonRadians) - cannon1Pos.y * sin(cannonRadians),
						   cannon1Pos.x * sin(cannonRadians) + cannon1Pos.y * cos(cannonRadians),
						   cannon1Pos.z);
	cannon1Pos += glm::vec3(0, -size.second / 7.5, 0);
	cannon1Pos += glm::vec3(pos.x, pos.y, 0);

	return cannon1Pos;
}

glm::vec3 m1::Enemy2::getCannon2Pos() {
	glm::vec3 cannon1Pos(size.first / 7.5, size.second, pos.z);

	cannon1Pos += glm::vec3(0, size.second / 7.5, 0);
	cannon1Pos = glm::vec3(cannon1Pos.x * cos(cannonRadians) - cannon1Pos.y * sin(cannonRadians),
						   cannon1Pos.x * sin(cannonRadians) + cannon1Pos.y * cos(cannonRadians),
						   cannon1Pos.z);
	cannon1Pos += glm::vec3(0, -size.second / 7.5, 0);
	cannon1Pos += glm::vec3(pos.x, pos.y, 0);

	return cannon1Pos;
}

bool m1::Enemy2::obstacleCollision(glm::vec3 pos, Obstacle* const obstacle) {
	glm::vec2 halfSize(obstacle->getSize().first / 2, obstacle->getSize().second / 2);
	glm::vec2 difference = pos - obstacle->getPos();

	glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
	glm::vec2 closest = obstacle->getPos();

	closest += clamped;
	difference = closest - glm::vec2(pos.x, pos.y);

	return glm::length(difference) < std::max(size.first / 2, size.second / 2);
}

bool m1::Enemy2::playerCollision(glm::vec3 pos, Player* const player) {
	float radius1 = std::min(size.first, size.second);
	float radius2 = std::min(player->getSize().first, player->getSize().second);

	return game->getEuclidianDistance(pos, player->getPos()) <= radius1 + radius2;
}

bool m1::Enemy2::canMove(glm::vec3 pos) {
	for (const auto& wall : game->walls)
		if (obstacleCollision(pos, wall))
			return false;

	return true;
}

void m1::Enemy2::takeDamage(const float damage) {
	currHealth -= damage;
}

void m1::Enemy2::update(const float dt) {
	if (game->player->isFreshlySpawned())
		return;

	glm::vec3 oldPos = pos;
	float oldRadians = bodyRadians;

	time += dt;
	counter++;

	bodyRadians = game->getAngle(pos, game->player->getPos());

	if (bodyRadians) {
		if (canMove({pos.x + speed * cos(bodyRadians) * dt, pos.y + speed * sin(bodyRadians) * dt, pos.z}))
			if (game->getEuclidianDistance(pos, game->player->getPos()) > 2 * (size.first + game->player->getSize().first)) {
				pos.x += speed * cos(bodyRadians) * dt;
				pos.y += speed * sin(bodyRadians) * dt;
			}

		if (pos != oldPos || game->convertAngle(bodyRadians, -glm::pi<float>() / 2) != oldRadians) {
			if (!(counter % 3))
				wheelMoveDirection *= -1;

			if (!(counter % 5))
				cannonMoveDirection *= -1;

			wheelOffset = counter % 3 * 0.5 * wheelMoveDirection * dt;
			cannonOffset = counter % 5 * 0.25 * cannonMoveDirection * dt;
		}
	} else {
		wheelOffset = 0;
		cannonOffset = 0;

		wheelMoveDirection = 1;
		cannonMoveDirection = 1;
	}

	bodyRadians = game->convertAngle(bodyRadians, -glm::pi<float>() / 2);

	if (!powerup)
		cannonRadians = bodyRadians;

	timeSinceLastBullet += dt;
	timeSinceLastPowerUp += dt;

	if (!powerup && timeSinceLastBullet >= 1.25) {
		bullets.push_back(new Bullet(getCannon1Pos(), {size.first / 8, size.second / 5}, cannonRadians, speed + 3, 10, 3, game));
		bullets.push_back(new Bullet(getCannon2Pos(), {size.first / 8, size.second / 5}, cannonRadians, speed + 3, 10, 3, game));
		timeSinceLastBullet = 0;
	}

	if (!powerup && timeSinceLastPowerUp >= 10) {
		powerup = true;
		powerUpTime = time;
	}

	if (powerup) {
		cannonRadians -= 10 * dt;

		if (!(counter % 3)) {
			bullets.push_back(new Bullet(getCannon1Pos(), {size.first / 8, size.second / 5}, cannonRadians, speed + 3, 5, 3, game));
			bullets.push_back(new Bullet(getCannon2Pos(), {size.first / 8, size.second / 5}, cannonRadians, speed + 3, 5, 3, game));
		}

		if (time - powerUpTime >= 1) {
			powerup = false;
			timeSinceLastPowerUp = 0;
		}
	}

	std::vector<Bullet*> remainingBullets;

	for (const auto& bullet : bullets)
		if (bullet->endOfLife())
			delete bullet;
		else {
			bullet->update(dt);

			if (!game->player->isFreshlySpawned() && bullet->playerCollision(bullet->getPos(), game->player)) {
				if (powerup)
					game->player->takeDamage(15);
				else
					game->player->takeDamage(10);

				delete bullet;
			} else
				remainingBullets.push_back(bullet);
		}

	bullets.erase(bullets.begin(), bullets.end());

	for (const auto& bullet : remainingBullets)
		bullets.push_back(bullet);
}

void m1::Enemy2::draw() {
	drawWheels();
	drawBody();
	drawWeapon();
	drawHealthBar();

	for (const auto& bullet : bullets)
		bullet->draw();
}
