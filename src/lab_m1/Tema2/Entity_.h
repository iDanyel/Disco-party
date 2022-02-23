#pragma once

#include "Game_.h"

namespace m1 {
	class Entity_ {
	protected:
		Game_* game;
		glm::mat4 modelMatrix;
		glm::vec3 center, size;

		float currTime;
		int frames;

	public:
		Entity_(const glm::vec3& center, const glm::vec3& size, Game_* const game);

		glm::vec3 getCenter();
		glm::vec3 getSize();
		
		virtual void update(const float dt) = 0;
		virtual void draw() = 0;
	};
};
