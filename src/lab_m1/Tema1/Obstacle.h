#pragma once

#include "Entity.h"

namespace m1 {
	class Obstacle : public Entity {
	private:
		std::string color;
		int type;

	public:
		Obstacle(const glm::vec3& pos, const std::pair<float, float>& size,
				 const std::string& color, const int type, Game* const game);

		glm::vec3 getPos() override;
		std::pair<float, float> getSize() override;
		float getSpeed() override;
		std::string getColor();
		
		void update(const float dt) override;
		void draw() override;
	};
};
