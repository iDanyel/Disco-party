#include "Dancer.h"

m1::Dancer::Dancer(const glm::vec3& pos, const glm::vec3& size, const std::pair<glm::vec3, glm::vec3>& area, const float speed, Game__* const game) {
	this->pos = pos; this->size = size; this->area = area; this->speed = speed; this->game = game;

	angle = RADIANS(rand() % 360);
	rotAngle = 0;
	rotDir = 1;
	corners = 0;
}

glm::vec3 m1::Dancer::getPos() {
	return pos;
}

bool m1::Dancer::canMove(const float dt) {
	glm::vec3 newPos = pos;

	newPos.x += speed * cos(angle) * dt;
	newPos.z += speed * sin(angle) * dt;

	return newPos.x >= area.first.x && newPos.x <= area.second.x && newPos.z >= area.second.z && newPos.z <= area.first.z;
}

void m1::Dancer::update(const float dt) {
	if (corners == 10) {
		spinningTime += dt;

		if (spinningTime <= 1.5)
			rotAngle += rotDir * 2 * speed * dt;
		else
			corners = 0;
	} else if (!canMove(dt)) {
		rotAngle += rotDir * 0.5 * speed * dt;
		angle = RADIANS(rand() % 360);
		rotDir *= -1;
		corners++;

		if (corners == 10)
			spinningTime = 0;
	} else {
		rotAngle += rotDir * 0.5 * speed * dt;
		pos.x += speed * cos(angle) * dt;
		pos.z += speed * sin(angle) * dt;
	}
}

void m1::Dancer::draw() {
	std::vector<Game__::LightSource> currLightCells = game->lightCells;

	std::sort(currLightCells.begin(), currLightCells.end(), [&](const auto& light1, const auto& light2) {
		return glm::distance(pos, light1.pos) < glm::distance(pos, light2.pos);
	});

	game->modelMatrix = glm::mat4(1);
	game->modelMatrix = glm::translate(game->modelMatrix, pos);
	game->modelMatrix = glm::rotate(game->modelMatrix, rotAngle, {0, 1, 0});
	game->modelMatrix = glm::scale(game->modelMatrix, size);
	game->RenderSimpleMesh(game->meshes["box"], game->shaders["homework3Shader"], game->modelMatrix, currLightCells, false, false, true, true, {0, 0, 0});
}
