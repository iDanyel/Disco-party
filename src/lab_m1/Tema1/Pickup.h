#pragma once

#include "Entity.h"

namespace m1 {
	class Pickup : Entity {
	private:
		int type, dir;
		float shrinkFactor, lifeSpan;

	public:
		Pickup(const glm::vec3& pos, const std::pair<float, float>& size,
			   const int type, const float lifeSpan, Game* const game);

		bool endOfLife();

		glm::vec3 getPos() override;
		std::pair<float, float> getSize() override;
		float getSpeed() override;
		int getType();
		float getShrinkFactor();

		void update(const float dt) override;
		void draw() override;
	};
};
