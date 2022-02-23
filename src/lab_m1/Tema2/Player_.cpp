#include "Player_.h"
#include "Bullet_.h"
#include "Obstacle_.h"
#include "Map_.h"
#include "Colliders_.h"
#include "Enemy_.h"

m1::Player_::Player_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game) : Human_(center, size, speed, game) {
	jumpSpeed = 5;
	bodyOffsetY = center.y;
	ascentTime = 0;
	descentTime = 0;
	
	f = 1.5;
	g = 9.81;

	totalTime = 300;
	doesntMove = true;

	collisionBlock = size;
}

void m1::Player_::jump() {
	if (simpleJump) {
		doubleJump = true;
		simpleJump = false;
		simpleJumpOffsetY = center.y;
		prevAscentTime = ascentTime;
		oldJumpSpeed = jumpSpeed;
		jumpSpeed *= f;

		armAngleDiffBetweenJumps = glm::pi<float>() - armAngleX;
		headAngleDiffBetweenJumps = glm::pi<float>() / 4 - headAngleX;
		thighAngleDiffBetweenJumps = glm::pi<float>() / 2 - thighAngleX;
		calfAngleDiffBetweenJumps = glm::pi<float>() / 2 - calfAngleX;
	} else {
		if (thighAngleX <= 0)
			rightLegDirBeforeJump = 1;
		else
			rightLegDirBeforeJump = -1;

		simpleJump = true;
		oldJumpSpeed = jumpSpeed;
		armAngleX = 0;

		headAngleX = 0;
		headAngleY = 0;
		armAngleX = 0;
		forearmAngleX = 0;
		thighAngleX = 0;
		calfAngleX = 0;

		armAngleDiffBetweenJumps = glm::pi<float>();
		headAngleDiffBetweenJumps = glm::pi<float>() / 4;
		thighAngleDiffBetweenJumps = glm::pi<float>() / 2;
		calfAngleDiffBetweenJumps = glm::pi<float>() / 2;

		addFootstep();
	}
}

void m1::Player_::addBullet() {
	bullets.push_back(new Bullet_(getGunPos(), glm::vec3(0.2 * size.z), 10 * getCurrSpeed(), 2, game->camera->getCameraAngleX(), game->camera->getCameraAngleY(),
								  game->camera->forward, game->camera->right, game->camera->up, game));

	reloaded = false;
	timeSinceLastBullet = 0;
	wasFired = true;
	gunOffsetAngleX = 0;
	gunOffsetDirX = 1;
	freshlyFired = true;
}

glm::vec3 m1::Player_::getGunPos() {
	glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);
	float offsetZ = -1.45 * halfSize.z;

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, center);
	modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
	modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
	modelMatrix = glm::translate(modelMatrix, {0, 0.125 * halfSize.y, offsetZ - 0.4 * halfSize.z - halfSize.z - 0.5 * halfSize.z + 0.25 * halfSize.z - 0.375 * halfSize.z - 0.125 * halfSize.z - 0.05 * halfSize.z - 0.75 * halfSize.z - 0.2 * halfSize.z});

	return modelMatrix[3];
}

bool m1::Player_::canJump() {
	return !freeFall && !doubleJump;
}

bool m1::Player_::gameOver() {
	return currLife <= 0 || currTime >= totalTime;
}

bool m1::Player_::won() {
	return colliders::AABB_AABB_collision({center, size}, {game->portal->getCenter(), game->portal->getSize()});
}

void m1::Player_::update(const float dt) {
	bool wasMoving = !doesntMove;

	Human_::update(dt);

	cameraAngleY = (game->paused) ? (cameraAngleY) : (game->camera->getCameraAngleY());
	cameraAngleX = (game->paused) ? (cameraAngleX) : (game->camera->getCameraAngleX());
	currEnergy = std::min(maxEnergy, currEnergy + 5 * dt);

	if (isAiming) {
		headAngleX = 0;
		headAngleY = 0;
		armAngleZ = 0;

		headRotationXDirection = 1;
		headRotationYDirection = 1;
		armRotationZDirection = 1;
	} else
		gunOffsetAngleX = 0;

	if (simpleJump) {
		armAngleX += glm::pi<float>() * g * dt / jumpSpeed;
		headAngleX += glm::pi<float>() / 4 * g * dt / jumpSpeed;
		thighAngleX += glm::pi<float>() / 2 * g * dt / jumpSpeed;
		calfAngleX += glm::pi<float>() / 2 * g * dt / jumpSpeed;

		doesntMove = false;
	} else if (doubleJump) {
		armAngleX += armAngleDiffBetweenJumps * g * dt / jumpSpeed;
		headAngleX += headAngleDiffBetweenJumps * g * dt / jumpSpeed;
		thighAngleX += thighAngleDiffBetweenJumps * g * dt / jumpSpeed;
		calfAngleX += calfAngleDiffBetweenJumps * g * dt / jumpSpeed;

		doesntMove = false;
	} else if (freeFall) {
		if (descentTime <= ascentTime - prevAscentTime) {
			armAngleX -= armAngleDiffBetweenJumps * g * dt / jumpSpeed;
			headAngleX -= headAngleDiffBetweenJumps * g * dt / jumpSpeed;
			thighAngleX -= thighAngleDiffBetweenJumps * g * dt / jumpSpeed;
			calfAngleX -= calfAngleDiffBetweenJumps * g * dt / jumpSpeed;
		} else {
			armAngleX -= glm::pi<float>() * g * dt / jumpSpeed;
			headAngleX -= glm::pi<float>() / 4 * g * dt / jumpSpeed;
			thighAngleX -= glm::pi<float>() / 2 * g * dt / jumpSpeed;
			calfAngleX -= glm::pi<float>() / 2 * g * dt / jumpSpeed;
		}

		doesntMove = false;
	} else if (isRunning) {
		headAngleX += headRotationXDirection * speed / 5 * dt;
		thighAngleX += thighRotationXDirection * 2 * speed * dt;
		calfAngleX += calfRotationXDirection * 2 * speed * dt;
		armAngleX += armRotationXDirection * 2 * speed * dt;
		forearmAngleX += forearmRotationXDirection * 2 * speed * dt;

		if (headAngleX < 0) {
			headAngleX = 0;
			headRotationXDirection *= -1;
		} else if (headAngleX > glm::pi<float>() / 5) {
			headAngleX = glm::pi<float>() / 5;
			headRotationXDirection *= -1;
		}

		if (armAngleX < -glm::pi<float>() / 2) {
			armAngleX = -glm::pi<float>() / 2;
			armRotationXDirection *= -1;
		} else if (armAngleX > glm::pi<float>() / 2) {
			armAngleX = glm::pi<float>() / 2;
			armRotationXDirection *= -1;
		}

		if (thighAngleX < -glm::pi<float>() / 2) {
			thighAngleX = -glm::pi<float>() / 2;
			thighRotationXDirection *= -1;
		} else if (thighAngleX > glm::pi<float>() / 2) {
			thighAngleX = glm::pi<float>() / 2;
			thighRotationXDirection *= -1;
		}

		if (calfAngleX < -glm::pi<float>() / 2) {
			calfAngleX = -glm::pi<float>() / 2;
			calfRotationXDirection *= -1;
		} else if (calfAngleX > glm::pi<float>() / 2) {
			calfAngleX = glm::pi<float>() / 2;
			calfRotationXDirection *= -1;
		}

		if (forearmAngleX < -glm::pi<float>() / 2) {
			forearmAngleX = -glm::pi<float>() / 2;
			forearmRotationXDirection *= -1;
		} else if (forearmAngleX > glm::pi<float>() / 2) {
			forearmAngleX = glm::pi<float>() / 2;
			forearmRotationXDirection *= -1;
		}

		headAngleY = 0;
		armAngleZ = 0;

		doesntMove = false;
	} else if (isWalking) {
		headAngleX += headRotationXDirection * speed / 10 * dt;
		armAngleX += armRotationXDirection * speed * dt;
		thighAngleX += thighRotationXDirection * speed * dt;

		if (headAngleX < 0) {
			headAngleX = 0;
			headRotationXDirection *= -1;
		} else if (headAngleX > glm::pi<float>() / 10) {
			headAngleX = glm::pi<float>() / 10;
			headRotationXDirection *= -1;
		}

		if (armAngleX < -glm::pi<float>() / 4) {
			armAngleX = -glm::pi<float>() / 4;
			armRotationXDirection *= -1;
		} else if (armAngleX > glm::pi<float>() / 4) {
			armAngleX = glm::pi<float>() / 4;
			armRotationXDirection *= -1;
		}

		if (thighAngleX < -glm::pi<float>() / 4) {
			thighAngleX = -glm::pi<float>() / 4;
			thighRotationXDirection *= -1;
		} else if (thighAngleX > glm::pi<float>() / 4) {
			thighAngleX = glm::pi<float>() / 4;
			thighRotationXDirection *= -1;
		}

		headAngleY = 0;
		armAngleZ = 0;
		calfAngleX = 0;

		headRotationYDirection = 1;
		armRotationZDirection = 1;
		calfRotationXDirection = 1;

		doesntMove = false;
	} else {
		armAngleZ += armRotationZDirection * 0.2 * dt;
		headAngleX += headRotationXDirection * 0.1 * dt;
		headAngleY += headRotationYDirection * 0.2 * dt;

		if (armAngleZ < 0) {
			armAngleZ = 0;
			armRotationZDirection *= -1;
		} else if (armAngleZ > glm::pi<float>() / 10) {
			armAngleZ = glm::pi<float>() / 10;
			armRotationZDirection *= -1;
		}

		if (headAngleX < 0) {
			headAngleX = 0;
			headRotationXDirection *= -1;
		} else if (headAngleX > glm::pi<float>() / 10) {
			headAngleX = glm::pi<float>() / 10;
			headRotationXDirection *= -1;
		}

		if (headAngleY < -glm::pi<float>() / 10) {
			headAngleY = -glm::pi<float>() / 10;
			headRotationYDirection *= -1;
		} else if (headAngleY > glm::pi<float>() / 10) {
			headAngleY = glm::pi<float>() / 10;
			headRotationYDirection *= -1;
		}

		thighAngleX = 0;
		calfAngleX = 0;
		armAngleX = 0;
		forearmAngleX = 0;

		thighRotationXDirection = 1;
		calfRotationXDirection = 1;
		armRotationXDirection = 1;
		forearmRotationXDirection = 1;

		doesntMove = true;
	}

	glm::vec3 oldCenter = center;

	if (doubleJump) {
		ascentTime += dt;

		if (ascentTime - prevAscentTime > jumpSpeed / g) {
			doubleJump = false;
			freeFall = true;

			armAngleX = glm::pi<float>();
		} else
			center.y += jumpSpeed * dt - g / 2 * dt * dt;
	} else if (simpleJump) {
		ascentTime += dt;

		if (ascentTime > jumpSpeed / g) {
			simpleJump = false;
			freeFall = true;

			armAngleX = glm::pi<float>();
		} else
			center.y += jumpSpeed * dt - g / 2 * dt * dt;
	} else if (freeFall) {
		descentTime += dt;
		center.y -= jumpSpeed * dt - g / 2 * dt * dt;

		if (jumpSpeed != oldJumpSpeed && descentTime > ascentTime - prevAscentTime)
			jumpSpeed /= f;

		if (center.y < bodyOffsetY) {
			freeFall = false;
			center.y = bodyOffsetY;

			ascentTime = 0;
			descentTime = 0;

			armAngleX = 0;
			headAngleX = 0;

			rightLegDirBeforeJump = 1;
			addFootstep();
		}
	}

	game->camera->TranslateUpwardGlobal(center.y - oldCenter.y);

	for (const auto& enemy : game->enemies)
		if (colliders::AABB_AABB_collision({center, size}, {enemy->getCenter(), enemy->getSize()}) && !enemy->getDeformityStatus()) {
			takeDamage(50);
			enemy->setDeformity(true);
		}

	std::vector<Bullet_*> remainingBullets;

	for (const auto& bullet : bullets)
		if (bullet->endOfLife())
			delete bullet;
		else {
			bool collision = false;

			for (const auto& obstacle : game->map->getMazeCells())
				if (colliders::AABB_AABB_collision({bullet->getCenter(), bullet->getSize()}, {obstacle->getCenter(), obstacle->getSize()}))
					collision = true;

			if (collision)
				delete bullet;
			else {
				for (const auto& enemy : game->enemies)
					if (colliders::Sphere_AABB_collision(bullet->getCenter(), bullet->getSize().x, {enemy->getCenter(), enemy->getSize()})) {
						enemy->takeDamage(50);
						collision = true;
					}

				if (collision)
					delete bullet;
				else {
					bullet->update(dt);
					remainingBullets.push_back(bullet);
				}
			}
		}

	bullets.erase(bullets.begin(), bullets.end());

	for (const auto& bullet : remainingBullets)
		bullets.push_back(bullet);

	std::vector<Footstep_*> remainingFootsteps;

	for (const auto& footstep : footsteps)
		if (footstep->endOfLife())
			delete footstep;
		else {
			footstep->update(dt);
			remainingFootsteps.push_back(footstep);
		}

	footsteps.erase(footsteps.begin(), footsteps.end());

	for (const auto& footstep : remainingFootsteps)
		footsteps.push_back(footstep);

	if (!wasMoving && !doesntMove)
		addFootstep();

	if (freshlyFired) {
		gunOffsetAngleX += gunOffsetDirX * 0.5 * getCurrSpeed() * dt;

		if (gunOffsetAngleX < 0) {
			gunOffsetAngleX = 0;
			gunOffsetDirX = 1;
			freshlyFired = false;
		} else if (gunOffsetAngleX > glm::pi<float>() / 10) {
			gunOffsetAngleX = glm::pi<float>() / 10;
			gunOffsetDirX *= -1;
		}
	} else if (wasFired) {
		reloadHandOffsetAngleX += reloadHandOffsetDirX * 0.5 * getCurrSpeed() * dt;
		reloadHandOffsetAngleY += reloadHandOffsetDirY * 0.1 * getCurrSpeed() * dt;

		if (reloadHandOffsetAngleX < 0) {
			reloadHandOffsetAngleX = 0;
			reloadHandOffsetDirX *= -1;

			wasFired = false;
			reloaded = true;

			gunOffsetAngleX = 0;
			gunOffsetDirX = 1;

			reloadHandOffsetAngleX = 0;
			reloadHandOffsetDirX = 1;

			reloadHandOffsetAngleY = 0;
			reloadHandOffsetDirY = 1;
		} else if (reloadHandOffsetAngleX > glm::pi<float>() / 7.5) {
			reloadHandOffsetAngleX = glm::pi<float>() / 7.5;
			reloadHandOffsetDirX *= -1;
		}
	} else if (!doesntMove) {
		if (isAiming) {
			gunOffsetAngleX += gunOffsetDirX * 0.01 * getCurrSpeed() * dt;

			if (gunOffsetAngleX < -glm::pi<float>() / 100) {
				gunOffsetAngleX = -glm::pi<float>() / 100;
				gunOffsetDirX *= -1;
			}
			else if (gunOffsetAngleX > glm::pi<float>() / 100) {
				gunOffsetAngleX = glm::pi<float>() / 100;
				gunOffsetDirX *= -1;
			}
		} else {
			gunOffsetAngleX = 0;
			gunOffsetDirX = 1;
		}
	}

	// Pickups collisions
	std::vector<Obstacle_*> remainingLifePickups;

	for (const auto& lifePickup : game->lifePickups)
		if (colliders::AABB_AABB_collision({center, size}, {lifePickup->getCenter(), lifePickup->getSize()})) {
			currLife = std::min(maxLife, currLife + 50);
			delete lifePickup;
		} else
			remainingLifePickups.push_back(lifePickup);

	game->lifePickups.erase(game->lifePickups.begin(), game->lifePickups.end());

	for (const auto& lifePickup : remainingLifePickups)
		game->lifePickups.push_back(lifePickup);

	std::vector<Obstacle_*> remainingTimePickups;

	for (const auto& timePickup : game->timePickups)
		if (colliders::AABB_AABB_collision({center, size}, {timePickup->getCenter(), timePickup->getSize()})) {
			currTime = std::max(0.0f, currTime - 20);
			delete timePickup;
		}
		else
			remainingTimePickups.push_back(timePickup);

	game->timePickups.erase(game->timePickups.begin(), game->timePickups.end());

	for (const auto& timePickup : remainingTimePickups)
		game->timePickups.push_back(timePickup);
}

void m1::Player_::draw() {
	Human_::draw();

	if (!isAiming) {
		glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);
		float cameraAngleY = game->camera->getCameraAngleY();

		// Draw health bar
		if (!isAiming && !isDeformed) {
			float headTopY = halfSize.y * (-1 + 2 * (bootScaleY + calfScaleY + thighScaleY + bodyScaleY + headScaleY));
			float barHeight = 0.075 * halfSize.y;

			float life = currLife >= 0 ? currLife : 0;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, headTopY + 4.5 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {-(maxLife - life) / maxLife * halfSize.x, headTopY + 4.5 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {life / maxLife * halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {1, 0, 0});
		}

		// Draw time bar
		{
			float headTopY = halfSize.y * (-1 + 2 * (bootScaleY + calfScaleY + thighScaleY + bodyScaleY + headScaleY));
			float barHeight = 0.075 * halfSize.y;

			float time = currTime < totalTime ? currTime : totalTime;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, headTopY + 3 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {-time / totalTime * halfSize.x, headTopY + 3 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {(totalTime - time) / totalTime * halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {1, 1, 0});
		}

		// Draw energy bar
		{
			float headTopY = halfSize.y * (-1 + 2 * (bootScaleY + calfScaleY + thighScaleY + bodyScaleY + headScaleY));
			float barHeight = 0.075 * halfSize.y;

			float energy = currEnergy < maxEnergy ? currEnergy : maxEnergy;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, headTopY + 1.5 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {-(maxEnergy - energy) / maxEnergy * halfSize.x, headTopY + 1.5 * barHeight, 0});
			modelMatrix = glm::scale(modelMatrix, {energy / maxEnergy * halfSize.x, barHeight / 2, 0.4 * halfSize.z});
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 1, 0});
		}
	} else {
		glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);

		if (cameraAngleX < -glm::pi<float>() / 3)
			cameraAngleX = -glm::pi<float>() / 3;
		else if (cameraAngleX > glm::pi<float>() / 3)
			cameraAngleX = glm::pi<float>() / 3;

		float offsetZ = -1.45 * halfSize.z;

		// Draw left arm
		{
			glm::vec3 scaleSize(0.15 * halfSize.x, 0.025 * halfSize.y, 0.5 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {-0.35 * halfSize.x, 0.1 * halfSize.y, offsetZ});

			modelMatrix = glm::translate(modelMatrix, {0, 0, 0.5 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, -glm::pi<float>() / 10, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -0.5 * halfSize.z});

			modelMatrix = glm::translate(modelMatrix, {0, 0, 0.5 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -0.5 * halfSize.z});

			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
		}

		// Draw left forearm
		{
			glm::vec3 scaleSize(0.15 * halfSize.x, 0.025 * halfSize.y, 0.3 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {-0.35 * halfSize.x, 0.1 * halfSize.y, offsetZ - halfSize.z + 0.2 * halfSize.z});

			modelMatrix = glm::translate(modelMatrix, {0, 0, halfSize.z + 0.3 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, -glm::pi<float>() / 10, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -halfSize.z - 0.3 * halfSize.z});

			modelMatrix = glm::translate(modelMatrix, {0, 0, halfSize.z + 0.3 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -halfSize.z - 0.3 * halfSize.z});

			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
		}

		// Draw left fist
		{
			glm::vec3 scaleSize(0.15 * halfSize.x, 0.025 * halfSize.y, 0.2 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {-0.35 * halfSize.x, 0.1 * halfSize.y, offsetZ - halfSize.z - 0.6 * halfSize.z + 0.3 * halfSize.z});

			modelMatrix = glm::translate(modelMatrix, {0, 0, halfSize.z + 0.6 * halfSize.z + 0.2 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, -glm::pi<float>() / 10, {0, 1, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -halfSize.z - 0.6 * halfSize.z - 0.2 * halfSize.z});

			modelMatrix = glm::translate(modelMatrix, {0, 0, halfSize.z + 0.6 * halfSize.z + 0.2 * halfSize.z});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, reloadHandOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0, -halfSize.z - 0.6 * halfSize.z - 0.2 * halfSize.z});

			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
		}

		// Draw right arm
		{
			glm::vec3 scaleSize(0.2 * halfSize.x, 0.025 * halfSize.y, 0.5 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.025 * halfSize.y, offsetZ - 0.4 * halfSize.z});
			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
		}

		// Draw right forearm
		{
			glm::vec3 scaleSize(0.2 * halfSize.x, 0.025 * halfSize.y, 0.25 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.025 * halfSize.y, offsetZ - 0.4 * halfSize.z - halfSize.z + 0.25 * halfSize.z});
			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
		}

		// Draw right fist
		{
			glm::vec3 scaleSize(0.2 * halfSize.x, 0.025 * halfSize.y, 0.25 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.025 * halfSize.y, offsetZ - 0.4 * halfSize.z - halfSize.z - 0.5 * halfSize.z + 0.25 * halfSize.z});
			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
		}

		// Draw handle
		{
			glm::vec3 scaleSize(0.135 * halfSize.x, 0.025 * halfSize.y, 0.2 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.075 * halfSize.y, offsetZ - 0.4 * halfSize.z - halfSize.z - 0.5 * halfSize.z + 0.25 * halfSize.z});
			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		}

		// Draw gun
		{
			glm::vec3 scaleSize(0.135 * halfSize.x, 0.025 * halfSize.y, 0.75 * halfSize.z);

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.125 * halfSize.y, offsetZ - 0.4 * halfSize.z - halfSize.z - 0.5 * halfSize.z + 0.25 * halfSize.z - 0.375 * halfSize.z - 0.125 * halfSize.z - 0.05 * halfSize.z});
			modelMatrix = glm::scale(modelMatrix, scaleSize);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		}

		// Draw aim
		if (reloaded) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, center);
			modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
			modelMatrix = glm::rotate(modelMatrix, cameraAngleX + gunOffsetAngleX, {1, 0, 0});
			modelMatrix = glm::translate(modelMatrix, {0, 0.125 * halfSize.y, -3});
			modelMatrix = glm::scale(modelMatrix, {0.0175, 0.0175, 1});
			game->RenderSimpleMesh(game->meshes["filledCircle"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		}

		float width = 10, height = 10;

		game->projectionMatrix = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, game->zNear, game->zFar);
		game->camera = game->hud_camera;

		// Draw health bar
		{
			float life = currLife >= 0 ? currLife : maxLife;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.65 * height, 0});
			modelMatrix = glm::scale(modelMatrix, {0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["unfilledSquare"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.65 * height, 0});
			modelMatrix = glm::translate(modelMatrix, {-(maxLife - life) / maxLife * 0.1 * width, 0, 0});
			modelMatrix = glm::scale(modelMatrix, {life / maxLife * 0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["filledSquare"], game->shaders["homework2Shader"], modelMatrix, {1, 0, 0});
		}

		// Draw time bar
		{
			float time = currTime < totalTime ? currTime : totalTime;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.59 * height, 0});
			modelMatrix = glm::scale(modelMatrix, {0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["unfilledSquare"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.59 * height, 0});
			modelMatrix = glm::translate(modelMatrix, {-time / totalTime * 0.1 * width, 0, 0});
			modelMatrix = glm::scale(modelMatrix, {(totalTime - time) / totalTime * 0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["filledSquare"], game->shaders["homework2Shader"], modelMatrix, {1, 1, 0});
		}

		// Draw energy bar
		{
			float energy = currEnergy >= 0 ? currEnergy : maxEnergy;

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.53 * height, 0});
			modelMatrix = glm::scale(modelMatrix, {0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["unfilledSquare"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, {width / 2 - 0.11 * width, 0.53 * height, 0});
			modelMatrix = glm::translate(modelMatrix, {-(maxEnergy - energy) / maxLife * 0.1 * width, 0, 0});
			modelMatrix = glm::scale(modelMatrix, {energy / maxEnergy * 0.1 * width, 0.025 * height, 1});
			game->RenderSimpleMesh(game->meshes["filledSquare"], game->shaders["homework2Shader"], modelMatrix, {0, 1, 0});
		}

		game->projectionMatrix = glm::perspective(game->fov, game->window->props.aspectRatio, game->zNear, game->zFar);
		game->camera = game->firstPersonCamera;
	}
}
