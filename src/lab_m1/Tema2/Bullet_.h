#pragma once

#include "Entity_.h"

namespace m1 {
	class Bullet_ : public Entity_ {
	private:
		glm::vec3 forwardVector, upVector, rightVector;
		float speed, lifeSpan, angleX, angleY;
		float time;

	public:
		Bullet_(const glm::vec3& center, const glm::vec3& size, const float speed, const float lifeSpan, const float angleX, const float angleY,
			    const glm::vec3& forwardVector, const glm::vec3& rightVector, const glm::vec3& upVector, Game_* const game);

		bool endOfLife();

		void update(const float dt) override;
		void draw() override;
	};
};
