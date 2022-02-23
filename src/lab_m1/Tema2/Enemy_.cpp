#include "Enemy_.h"
#include "Map_.h"

m1::Enemy_::Enemy_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game) : Human_(center, size, speed, game) {
	dir = 'u';
	timeSinceLastDirSwitch = 0;
	timeSinceDeformed = 0;
	collisionBlock = {1.5 * size.x, size.y, 1.5 * size.x};
}

void m1::Enemy_::move(const float dt) {
	if (dir == 'u')
		moveForward(getCurrSpeed() * dt);
	else if (dir == 'd')
		moveForward(-getCurrSpeed() * dt);
	else if (dir == 'r')
		moveRight(getCurrSpeed() * dt);
	else
		moveRight(-getCurrSpeed() * dt);
}

bool m1::Enemy_::endOfLife() {
	return timeSinceDeformed >= 3;
}

void m1::Enemy_::update(const float dt) {
	if (isDeformed) {
		timeSinceDeformed += dt;

		if (timeSinceDeformed >= 2)
			size /= 1.5f;

		return;
	}

	Human_::update(dt);

	if (currLife <= 0) {
		isDeformed = true;
		return;
	}

	timeSinceLastDirSwitch += dt;

	if (!canMove(dir, getCurrSpeed() * dt)) {
		std::vector<char> directions;

		if (canMove('u', getCurrSpeed() * dt)) {
			if (dir == 'l' || dir == 'r')
				for (int i = 0; i < 10; i++)
					directions.push_back('u');

			directions.push_back('u');
		}
		
		if (canMove('d', getCurrSpeed() * dt)) {
			if (dir == 'l' || dir == 'r')
				for (int i = 0; i < 10; i++)
					directions.push_back('d');

			directions.push_back('d');
		}
		
		if (canMove('r', getCurrSpeed() * dt)) {
			if (dir == 'u' || dir == 'd')
				for (int i = 0; i < 10; i++)
					directions.push_back('r');

			directions.push_back('r');
		}
		
		if (canMove('l', getCurrSpeed() * dt)) {
			if (dir == 'u' || dir == 'd')
				for (int i = 0; i < 10; i++)
					directions.push_back('l');

			directions.push_back('l');
		}

		dir = directions[rand() % directions.size()];
	} else if (timeSinceLastDirSwitch >= 3) {
		std::vector<char> directions;

		if (dir != 'd' && canMove('u', getCurrSpeed() * dt)) {
			if (dir == 'l' || dir == 'r')
				for (int i = 0; i < 10; i++)
					directions.push_back('u');

			directions.push_back('u');
		}

		if (dir != 'u' && canMove('d', getCurrSpeed() * dt)) {
			if (dir == 'l' || dir == 'r')
				for (int i = 0; i < 10; i++)
					directions.push_back('d');

			directions.push_back('d');
		}

		if (dir != 'l' && canMove('r', getCurrSpeed() * dt)) {
			if (dir == 'u' || dir == 'd')
				for (int i = 0; i < 10; i++)
					directions.push_back('r');

			directions.push_back('r');
		}

		if (dir != 'r' && canMove('l', getCurrSpeed() * dt)) {
			if (dir == 'u' || dir == 'd')
				for (int i = 0; i < 10; i++)
					directions.push_back('l');

			directions.push_back('l');
		}

		if (!directions.empty())
			dir = directions[rand() % directions.size()];

		timeSinceLastDirSwitch = 0;
	}

	if (dir == 'l')
		cameraAngleY = glm::pi<float>() / 2;
	else if (dir == 'r')
		cameraAngleY = -glm::pi<float>() / 2;
	else if (dir == 'd')
		cameraAngleY = glm::pi<float>();
	else
		cameraAngleY = 0;

	// Enemies are always walking
	headAngleX += headRotationXDirection * speed / 10 * dt;
	armAngleX += armRotationXDirection * speed * dt;
	thighAngleX += thighRotationXDirection * speed * dt;

	if (headAngleX < 0) {
		headAngleX = 0;
		headRotationXDirection *= -1;
	}
	else if (headAngleX > glm::pi<float>() / 10) {
		headAngleX = glm::pi<float>() / 10;
		headRotationXDirection *= -1;
	}

	if (armAngleX < -glm::pi<float>() / 4) {
		armAngleX = -glm::pi<float>() / 4;
		armRotationXDirection *= -1;
	}
	else if (armAngleX > glm::pi<float>() / 4) {
		armAngleX = glm::pi<float>() / 4;
		armRotationXDirection *= -1;
	}

	if (thighAngleX < -glm::pi<float>() / 4) {
		thighAngleX = -glm::pi<float>() / 4;
		thighRotationXDirection *= -1;
	}
	else if (thighAngleX > glm::pi<float>() / 4) {
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
	onGroundMovingTime += dt;

	if (canAddFootstep())
		addFootstep();

	move(dt);

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
}

void m1::Enemy_::draw() {
	Human_::draw();

	// Draw health bar
	if (!isDeformed) {
		glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);

		float headTopY = halfSize.y * (-1 + 2 * (bootScaleY + calfScaleY + thighScaleY + bodyScaleY + headScaleY));
		float barHeight = 0.075 * halfSize.y;

		float life = currLife >= 0 ? currLife : 0;

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0, headTopY + 1.5 * barHeight, 0});
		modelMatrix = glm::scale(modelMatrix, {halfSize.x, barHeight / 2, 0.4 * halfSize.z});
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0});

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-(maxLife - life) / maxLife * halfSize.x, headTopY + 1.5 * barHeight, 0});
		modelMatrix = glm::scale(modelMatrix, {life / maxLife * halfSize.x, barHeight / 2, 0.4 * halfSize.z});
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, {1, 0, 0});
	}
}
