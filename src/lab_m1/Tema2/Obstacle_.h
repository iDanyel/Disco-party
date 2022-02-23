#pragma once

#include "Entity_.h"

namespace m1 {
	class Obstacle_ : public Entity_ {
	private:
		glm::vec3 color;
		bool noBorder;
		float angle;

	public:
		Obstacle_(const glm::vec3& center, const glm::vec3& size, const glm::vec3& color, const bool noBorder, Game_* const game);

		float getAngle();
		void setAngle(const float angle);
		float getTime();

		void update(const float dt) override;
		void draw() override;
	};
};
