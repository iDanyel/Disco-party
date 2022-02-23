#pragma once

#include "Game_.h"

namespace m1 {
	class Map_ {
	private:
		struct Wall {
			bool visited = false;
			bool topWall = true;
			bool bottomWall = true;
			bool leftWall = true;
			bool rightWall = true;
		};

		Game_* game;
		int n, m, freeCells;
		glm::vec3 obstacleSize;
		std::vector<Obstacle_*> mazeCells;;
		std::vector<std::vector<Wall>> walls;
		std::vector<std::vector<int>> map;
		std::vector<std::vector<int>> map_;
		Obstacle_* floor;

		bool isInside(int x, int y);
		void generateMaze(int x, int y);

	public:
		Map_(const int n, const int m, const glm::vec3& obstacleSize, glm::vec3& startingPosition, Game_* const game);

		std::vector<Obstacle_*> getMazeCells();
		glm::vec3 getRandomFreeCellPos();
		glm::vec3 getObstacleSize();

		void draw();
	};
};
