#include "Enemy.h"

m1::Enemy::Enemy(const glm::vec3& pos, const std::pair<float, float>& size,
				 const float speed, const float maxHealth, Game* const game) : Entity(pos, size, speed, game) {
	this->maxHealth = maxHealth;
	currHealth = maxHealth;
}

float m1::Enemy::getHealth() {
	return currHealth;
}
