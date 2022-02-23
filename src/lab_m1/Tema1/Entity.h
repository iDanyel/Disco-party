#pragma once

#include "Game.h"
#include "iostream"

namespace m1 {
	class Entity {
	public:
		Game* game;
		glm::mat4 modelMatrix;

		glm::vec3 pos;
		float speed, time;

		std::pair<float, float> size;
		unsigned long long counter;

		Entity(const glm::vec3& pos, const std::pair<float, float>& size,
			   const float speed, Game* const game);

		virtual glm::vec3 getPos() = 0;
		virtual float getSpeed() = 0;
		virtual std::pair<float, float> getSize() = 0;

		bool isOnScreen();

		virtual void update(const float dt) = 0;
		virtual void draw() = 0;
	};
};