#include "Entity_.h"

// Public methods
m1::Entity_::Entity_(const glm::vec3& center, const glm::vec3& size, Game_* const game) {
	this->center = center, this->size = size;  this->game = game;

	currTime = 0;
	frames = 0;
}

glm::vec3 m1::Entity_::getCenter() {
	return center;
}

glm::vec3 m1::Entity_::getSize() {
	return size;
}
