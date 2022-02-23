#include "Human_.h"
#include "Bullet_.h"
#include "Obstacle_.h"
#include "Colliders_.h"
#include "Map_.h"

// Private methods
m1::Human_::Footstep_::Footstep_(const glm::vec3& center, const glm::vec3& size, const float angle, Game_* const game) {
	this->center = center; this->size = size; this->angle = angle;  this->game = game;

	lifespan = 2;
	initialLifespan = lifespan;
	color = {0, 0, 0};
	floorColor = {0.219, 0, 0.054};
}

bool m1::Human_::Footstep_::endOfLife() {
	return lifespan <= 0;
}

void m1::Human_::Footstep_::update(const float dt) {
	lifespan -= dt;
	color.x = std::min(floorColor.x, color.x + 0.001f);
	color.y = std::min(floorColor.y, color.y + 0.001f);
	color.z = std::min(floorColor.z, color.z + 0.001f);
}

void m1::Human_::Footstep_::draw() {
	{
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, angle, {0, 1, 0});
		modelMatrix = glm::scale(modelMatrix, size);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, color);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, angle, {0, 1, 0});
		modelMatrix = glm::scale(modelMatrix, 0.75f * size);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, color);
	}
}

// Public methods
m1::Human_::Human_(const glm::vec3& center, const glm::vec3& size, const float speed, Game_* const game) : Entity_(center, size, game) {
	this->speed = speed;

	maxLife = 100;
	currLife = 100;

	skinColor = {1, 0.858, 0.674};
	shirtColor = {0.152, 0.568, 0.470};
	pantsColor = {0.152, 0.290, 0.568};
	gunColor = {0, 0, 0};

	headBodyDistance = 0.05;
	legsBodyDistance = 0.05;
	legsDistance = 0.025;

	forwardVector = {0, 0, -1};
	rightVector = {1, 0, 0};
	upVector = {0, 1, 0};

	simpleJump = false;
	doubleJump = false;
	freeFall = false;

	isWalking = false;
	isRunning = false;
	isAiming = false;

	armAngleZ = 0;
	headAngleX = 0;
	headAngleY = 0;

	thighAngleX = 0;
	calfAngleX = 0;
	armAngleX = 0;
	forearmAngleX = 0;
	bodyAngleY = 0;

	armRotationZDirection = 1;
	headRotationXDirection = 1;
	headRotationYDirection = 1;

	thighRotationXDirection = 1;
	calfRotationXDirection = 1;
	armRotationXDirection = 1;
	forearmRotationXDirection = 1;

	bootScaleY = 0.075;
	calfScaleY = 0.05;
	thighScaleY = 0.15;
	bodyScaleY = 0.3;
	headScaleY = 0.125;
	armScaleY = 0.125;
	forearmScaleY = 0.075;
	fistScaleY = 0.055;
	gunScaleY = 0.175;

	isDeformed = false;
	onGroundMovingTime = 0;
	cooldown = 2;
	timeSinceLastBullet = cooldown;

	cameraAngleY = 0;
	cameraAngleX = 0;

	gunOffsetAngleX = 0;
	gunOffsetDirX = 1;

	reloadHandOffsetAngleX = 0;
	reloadHandOffsetDirX = 1;

	reloadHandOffsetAngleY = 0;
	reloadHandOffsetDirY = 1;

	reloaded = true;
	wasFired = false;
	freshlyFired = false;

	currEnergy = 100;
	maxEnergy = 100;
}

void m1::Human_::setSkinColor(const glm::vec3& skinColor) {
	this->skinColor = skinColor;
}

void m1::Human_::setShirtColor(const glm::vec3& shirtColor) {
	this->shirtColor = shirtColor;
}

void m1::Human_::setPantsColor(const glm::vec3& pantsColor) {
	this->pantsColor = pantsColor;
}

void m1::Human_::setMovement(bool isWalking, bool isRunning) {
	if (simpleJump || doubleJump || freeFall)
		return;

	if (isRunning)
		currEnergy = std::max(0.0, currEnergy - 0.2);

	if ((isRunning && isAiming) || (isRunning && currEnergy <= 0)) {
		isWalking = true;
		isRunning = false;
	}

	if ((isRunning && !this->isRunning) || (isWalking && !this->isWalking)) {
		armAngleZ = 0;
		headAngleX = 0;
		headAngleY = 0;

		thighAngleX = 0;
		calfAngleX = 0;
		forearmAngleX = 0;
		bodyAngleY = 0;

		armRotationZDirection = 1;
		headRotationXDirection = 1;
		headRotationYDirection = 1;

		thighRotationXDirection = 1;
		calfRotationXDirection = 1;
		forearmRotationXDirection = 1;

		if (isRunning && !this->isRunning) {
			armAngleX = 0;
			armRotationXDirection = 1;
		}
	}

	this->isWalking = isWalking; this->isRunning = isRunning;
}

void m1::Human_::setDeformity(const float isDeformed) {
	this->isDeformed = isDeformed;
}

void m1::Human_::setAiming(const float isAiming) {
	this->isAiming = isAiming;
}

void m1::Human_::rotate(const float cameraAngleY) {
	forwardVector = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), cameraAngleY, {0, 1, 0}) * glm::vec4(forwardVector, 1)));
	rightVector = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), cameraAngleY, {0, 1, 0}) * glm::vec4(rightVector, 1)));
	upVector = glm::cross(rightVector, forwardVector);
}

float m1::Human_::getSpeed() {
	return speed;
}

float m1::Human_::getCurrSpeed() {
	if (simpleJump || doubleJump || freeFall)
		return speed;

	return isRunning ? 2 * speed : speed;
}

glm::vec3 m1::Human_::getForwardVector() {
	return forwardVector;
}

glm::vec3 m1::Human_::getRightVector() {
	return rightVector;
}

glm::vec3 m1::Human_::getUpVector() {
	return upVector;
}

glm::vec3 m1::Human_::getDirZ() {
	return glm::normalize(glm::vec3(forwardVector.x, 0, forwardVector.z));
}

glm::vec3 m1::Human_::getDirX() {
	return glm::normalize(glm::vec3(rightVector.x, 0, rightVector.z));
}

float m1::Human_::getCurrEnergy() {
	return currEnergy;
}

void m1::Human_::takeDamage(const float damage) {
	currLife -= damage;
}

bool m1::Human_::canFire() {
	return isAiming && reloaded;
}

bool m1::Human_::canAddFootstep() {
	return onGroundMovingTime >= 0.5;
}

bool m1::Human_::obstacleCollision(const glm::vec3& pos, Obstacle_* obstacle) {
	return colliders::AABB_AABB_collision({pos, size}, {obstacle->getCenter(), obstacle->getSize()});
}

bool m1::Human_::canMove(const char dir, const float dt) {
	glm::vec3 newCenter = center;

	if (dir == 'u')
		newCenter += getDirZ() * getCurrSpeed() * dt;
	else if (dir == 'd')
		newCenter -= getDirZ() * getCurrSpeed() * dt;
	else if (dir == 'r')
		newCenter += getDirX() * getCurrSpeed() * dt;
	else
		newCenter -= getDirX() * getCurrSpeed() * dt;

	for (const auto& obstacle : game->map->getMazeCells())
		if (colliders::AABB_AABB_collision({newCenter, collisionBlock}, {obstacle->getCenter(), obstacle->getSize()}))
			return false;

	return true;
}

bool m1::Human_::getDeformityStatus() {
	return isDeformed;
}

void m1::Human_::addFootstep() {
	float angle = game->camera->getCameraAngleY();
	
	footsteps.push_back(new Footstep_({leftBootPos.x, 0, leftBootPos.z}, {size.x / 4, 0.01, size.z / 2}, angle, game));
	footsteps.push_back(new Footstep_({rightBootPos.x, 0, rightBootPos.z}, {size.x / 4, 0.01, size.z / 2}, angle, game));

	onGroundMovingTime = 0;
}

void m1::Human_::moveForward(const float dt) {
	center += getDirZ() * getCurrSpeed() * dt;
}

void m1::Human_::moveRight(const float dt) {
	center += getDirX() * getCurrSpeed() * dt;;
}

void m1::Human_::update(const float dt) {
	currTime += dt;
	frames++;
	timeSinceLastBullet += dt;
	currLife += dt;

	currLife = std::min(currLife, maxLife);

	if (timeSinceLastBullet > cooldown) {
		wasFired = false;
		recoil = 0;
	}

	if (wasFired) {
		if (timeSinceLastBullet <= cooldown / 2)
			recoil += speed * dt;
		else
			recoil -= speed * dt;
	}

	if (simpleJump || doubleJump || freeFall)
		onGroundMovingTime = 0;
	else if (isWalking || isRunning)
		onGroundMovingTime += dt;

	if (canAddFootstep())
		addFootstep();
}

void m1::Human_::draw() {
	// Draw footsteps
	{
		for (const auto& footstep : footsteps)
			footstep->draw();
	}

	// Draw bullets
	{
		for (const auto& bullet : bullets)
			bullet->draw();
	}

	glm::vec3 halfSize(size.x / 2, size.y / 2, size.z / 2);
	int reversedAngle = simpleJump || doubleJump || freeFall ? -1 : 1;

	// Draw head
	if (!isAiming) {
		glm::vec3 scaleSize(0.55 * halfSize.x, headScaleY * halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y + headScaleY * halfSize.y, 0});

		modelMatrix = glm::rotate(modelMatrix, headAngleX, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, headAngleY, {0, 1, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
	}

	// Draw body
	if (!isAiming) {
		glm::vec3 scaleSize(halfSize.x, bodyScaleY * halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + bodyScaleY * halfSize.y, 0});
		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
	}

	// Left arm
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, armScaleY * halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - armScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, armScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleX * reversedAngle, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -armScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
	}

	// Left forearm
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, forearmScaleY * halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - 2 * armScaleY * halfSize.y - forearmScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * armScaleY * halfSize.y + forearmScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleX * reversedAngle, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -2 * armScaleY * halfSize.y - forearmScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::translate(modelMatrix, {0, forearmScaleY * halfSize.y, 0});

		if (armAngleX >= 0)
			modelMatrix = glm::rotate(modelMatrix, forearmAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -forearmAngleX, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -forearmScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
	}

	// Left fist
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, fistScaleY * halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - 2 * armScaleY * halfSize.y - 2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * armScaleY * halfSize.y + 2 * forearmScaleY * halfSize.y + fistScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleX * reversedAngle, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, -armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -2 * armScaleY * halfSize.y - 2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * forearmScaleY * halfSize.y + fistScaleY * halfSize.y, 0});

		if (armAngleX >= 0)
			modelMatrix = glm::rotate(modelMatrix, forearmAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -forearmAngleX, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
	}

	// Right arm
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, armScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - armScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, armScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleX, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -armScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
	}

	// Right forearm
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, forearmScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - 2 * armScaleY * halfSize.y - forearmScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * armScaleY * halfSize.y + forearmScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleX, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -2 * armScaleY * halfSize.y - forearmScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::translate(modelMatrix, {0, forearmScaleY * halfSize.y, 0});

		if (armAngleX >= 0)
			modelMatrix = glm::rotate(modelMatrix, forearmAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -forearmAngleX, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -forearmScaleY * halfSize.y, 0});
		

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, shirtColor, isDeformed);
	}

	// Right fist
	if (!isAiming) {
		glm::vec3 scaleSize(0.35 * halfSize.x, fistScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {1.35 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y + 2 * bodyScaleY * halfSize.y - 2 * armScaleY * halfSize.y - 2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * armScaleY * halfSize.y + 2 * forearmScaleY * halfSize.y + fistScaleY * halfSize.y - halfSize.z, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleX, {1, 0, 0});
		modelMatrix = glm::rotate(modelMatrix, armAngleZ, {0, 0, 1});
		modelMatrix = glm::translate(modelMatrix, {0, -2 * armScaleY * halfSize.y - 2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y + halfSize.z, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * forearmScaleY * halfSize.y + fistScaleY * halfSize.y, 0});

		if (armAngleX >= 0)
			modelMatrix = glm::rotate(modelMatrix, forearmAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -forearmAngleX, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -2 * forearmScaleY * halfSize.y - fistScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
	}

	// Left thigh
	if (!isAiming) {
		glm::vec3 scaleSize(0.5 * halfSize.x, thighScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-0.5 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -thighScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, pantsColor, isDeformed);
	}

	// Left calf
	if (!isAiming) {
		glm::vec3 scaleSize(0.5 * halfSize.x, calfScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-0.5 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + calfScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -calfScaleY * halfSize.y - 2 * thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, calfScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, -calfAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, calfAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -calfScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, pantsColor, isDeformed);
	}

	// Left boot
	{
		glm::vec3 scaleSize(0.5 * halfSize.x, bootScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {-0.5 * halfSize.x, -halfSize.y + bootScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -bootScaleY * halfSize.y - 2 * calfScaleY * halfSize.y - 2 * thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * calfScaleY * halfSize.y + bootScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, -calfAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, calfAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -2 * calfScaleY * halfSize.y - bootScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);

		if (!isAiming) {
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
		}

		leftBootPos = modelMatrix[3];
	}

	// Right thigh
	if (!isAiming) {
		glm::vec3 scaleSize(0.5 * halfSize.x, thighScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0.5 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -thighScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, pantsColor, isDeformed);
	}

	// Right calf
	if (!isAiming) {
		glm::vec3 scaleSize(0.5 * halfSize.x, calfScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0.5 * halfSize.x, -halfSize.y + 2 * bootScaleY * halfSize.y + calfScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -calfScaleY * halfSize.y - 2 * thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, calfScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, calfAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -calfAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -calfScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);
		game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, {0, 0, 0}, isDeformed);
		game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, pantsColor, isDeformed);
	}

	// Right boot
	{
		glm::vec3 scaleSize(0.5 * halfSize.x, bootScaleY* halfSize.y, halfSize.z);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, center);
		modelMatrix = glm::rotate(modelMatrix, cameraAngleY, {0, 1, 0});
		modelMatrix = glm::translate(modelMatrix, {0.5 * halfSize.x, -halfSize.y + bootScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, bootScaleY * halfSize.y + 2 * calfScaleY * halfSize.y + 2 * thighScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, -thighAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, thighAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -bootScaleY * halfSize.y - 2 * calfScaleY * halfSize.y - 2 * thighScaleY * halfSize.y, 0});

		modelMatrix = glm::translate(modelMatrix, {0, 2 * calfScaleY * halfSize.y + bootScaleY * halfSize.y, 0});

		if (!simpleJump && !doubleJump && !freeFall)
			modelMatrix = glm::rotate(modelMatrix, calfAngleX, {1, 0, 0});
		else
			modelMatrix = glm::rotate(modelMatrix, -calfAngleX * rightLegDirBeforeJump, {1, 0, 0});

		modelMatrix = glm::translate(modelMatrix, {0, -2 * calfScaleY * halfSize.y - bootScaleY * halfSize.y, 0});

		modelMatrix = glm::scale(modelMatrix, scaleSize);

		if (!isAiming) {
			game->RenderSimpleMesh(game->meshes["unfilledCube"], game->shaders["homework2Shader"], modelMatrix, { 0, 0, 0 }, isDeformed);
			game->RenderSimpleMesh(game->meshes["filledCube"], game->shaders["homework2Shader"], modelMatrix, skinColor, isDeformed);
		}

		rightBootPos = modelMatrix[3];
	}
}
