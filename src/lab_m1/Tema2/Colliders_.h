#pragma once

#include "Game_.h"

namespace colliders {
	bool Sphere_Sphere_collision(const glm::vec3& center1, const float radius1, const glm::vec3& center2, const float radius2);
	bool Sphere_AABB_collision(const glm::vec3& center, const float radius, const std::pair<glm::vec3, glm::vec3>& p);
	bool AABB_AABB_collision(const std::pair<glm::vec3, glm::vec3>& p1, const std::pair<glm::vec3, glm::vec3>& p2);
};
