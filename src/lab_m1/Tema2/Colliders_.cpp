#include "Colliders_.h"

bool colliders::Sphere_Sphere_collision(const glm::vec3& center1, const float radius1, const glm::vec3& center2, const float radius2) {
	float distance = sqrt((center1.x - center2.x) * (center1.x - center2.x) +
					      (center1.y - center2.y) * (center1.y - center2.y) +
						  (center1.z - center2.z) * (center1.z - center2.z));

	return distance < radius1 + radius2;
}

bool colliders::Sphere_AABB_collision(const glm::vec3& center, const float radius, const std::pair<glm::vec3, glm::vec3>& p) {
	glm::vec3 leftBottomCorner = p.first - p.second / 2.0f;
	glm::vec3 rightTopCorner = p.first + p.second / 2.0f;

	float x = std::max(leftBottomCorner.x, std::min(center.x, rightTopCorner.x));
	float y = std::max(leftBottomCorner.y, std::min(center.y, rightTopCorner.y));
	float z = std::max(leftBottomCorner.z, std::min(center.z, rightTopCorner.z));

	float distance = sqrt((x - center.x) * (x - center.x) +
						  (y - center.y) * (y - center.y) +
						  (z - center.z) * (z - center.z));

	return distance < radius;
}

// Public methods
bool colliders::AABB_AABB_collision(const std::pair<glm::vec3, glm::vec3>& p1, const std::pair<glm::vec3, glm::vec3>& p2) {
	glm::vec3 leftBottomCorner1 = p1.first - p1.second / 2.0f;
	glm::vec3 rightTopCorner1 = p1.first + p1.second / 2.0f;

	glm::vec3 leftBottomCorner2 = p2.first - p2.second / 2.0f;
	glm::vec3 rightTopCorner2 = p2.first + p2.second / 2.0f;

	return leftBottomCorner1.x <= rightTopCorner2.x && rightTopCorner1.x >= leftBottomCorner2.x &&
		   leftBottomCorner1.y <= rightTopCorner2.y && rightTopCorner1.y >= leftBottomCorner2.y &&
		   leftBottomCorner1.z <= rightTopCorner2.z && rightTopCorner1.z >= leftBottomCorner2.z;
}
