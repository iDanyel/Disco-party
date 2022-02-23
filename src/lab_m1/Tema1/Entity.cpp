#include "Entity.h"

m1::Entity::Entity(const glm::vec3& pos, const std::pair<float, float>& size,
				   const float speed, Game* const game) {
	this->pos = pos; this->size = size;
	this->speed = speed; this->game = game;

	time = 0;
	counter = 0;
}

bool m1::Entity::isOnScreen() {
	std::vector<glm::vec3> corners(4);

	corners[0] = pos + glm::vec3(-size.first / 2, size.second / 2, 0);
	corners[1] = pos + glm::vec3(-size.first / 2, -size.second / 2, 0);
	corners[2] = pos + glm::vec3(size.first / 2, -size.second / 2, 0);
	corners[3] = pos + glm::vec3(size.first / 2, size.second / 2, 0);

	for (const auto& corner : corners)
		if (corner.x >= game->logicSpace.x && corner.x <= game->logicSpace.x + game->logicSpace.width &&
			corner.y >= game->logicSpace.y && corner.y <= game->logicSpace.y + +game->logicSpace.height)
			return true;

	return false;
}
