#include "Map_.h"
#include "Obstacle_.h"

bool m1::Map_::isInside(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m;
}

void m1::Map_::generateMaze(int x, int y) {
	walls[x][y].visited = true;

	std::vector<std::pair<std::pair<int, int>, int>> neighbours;

	if (isInside(x + 1, y) && !walls[x + 1][y].visited)
		neighbours.push_back({{x + 1, y}, 0});

	if (isInside(x - 1, y) && !walls[x - 1][y].visited)
		neighbours.push_back({{x - 1, y}, 1});

	if (isInside(x, y + 1) && !walls[x][y + 1].visited)
		neighbours.push_back({{x, y + 1}, 2});

	if (isInside(x, y - 1) && !walls[x][y - 1].visited)
		neighbours.push_back({{x, y - 1}, 3});

	if (neighbours.empty())
		return;

	std::random_shuffle(neighbours.begin(), neighbours.end());

	for (int i = 0; i < neighbours.size(); i++) {
		int newX = neighbours[i].first.first;
		int newY = neighbours[i].first.second;

		if (walls[newX][newY].visited)
			continue;

		switch (neighbours[i].second) {
		case 0:
			walls[x][y].bottomWall = false;
			walls[newX][newY].topWall = false;
			break;

		case 1:
			walls[x][y].topWall = false;
			walls[newX][newY].bottomWall = false;
			break;

		case 2:
			walls[x][y].rightWall = false;
			walls[newX][newY].leftWall = false;
			break;

		case 3:
			walls[x][y].leftWall = false;
			walls[newX][newY].rightWall = false;
			break;
		}

		generateMaze(newX, newY);
	}
}

m1::Map_::Map_(const int n, const int m, const glm::vec3& obstacleSize, glm::vec3& startingPosition, Game_* const game) : walls(3 * n), map(3 * n) {
	this->n = n; this->m = m; this->obstacleSize = obstacleSize; this->game = game;

	freeCells = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			walls[i].push_back({});

	int startX = 1 + rand() % (n - 1), startY = 1 + rand() % (m - 1);

	generateMaze(startX, startY);

	for (int i = 0; i < 3 * n; i++)
		for (int j = 0; j < 3 * m; j++)
			map[i].push_back({});

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int cell[3][3];

			for (int a = 0; a < 3; a++)
				for (int b = 0; b < 3; b++)
					cell[a][b] = 1;

			if (!walls[i][j].bottomWall) {
				cell[2][1] = 0;
				cell[1][1] = 0;
			}

			if (!walls[i][j].topWall) {
				cell[0][1] = 0;
				cell[1][1] = 0;
			}

			if (!walls[i][j].leftWall) {
				cell[1][0] = 0;
				cell[1][1] = 0;
			}

			if (!walls[i][j].rightWall) {
				cell[1][2] = 0;
				cell[1][1] = 0;
			}

			for (int a = 0; a < 3; a++)
				for (int b = 0; b < 3; b++)
					map[3 * i + a][3 * j + b] = cell[a][b];
		}

	// Matrix compression
	glm::vec3 size = obstacleSize;
	glm::vec3 offset(-3 * n * size.x / 2 + size.x / 2, 0, 0);
	glm::vec3 color = {0.15, 0, 0.054};

	// Floor
	floor = new Obstacle_(glm::vec3(0, -0.05f, 0), {3 * n * size.x, 0.1f, 3 * m * size.z}, {0.219, 0, 0.054}, false, game);

	// Borders
	mazeCells.push_back(new Obstacle_(glm::vec3(0, size.y / 2, 0) + offset, {size.x, size.y, 3 * m * size.z}, color, false, game));
	mazeCells.push_back(new Obstacle_(glm::vec3((3 * n - 1) * size.x, size.y / 2, 0) + offset, { size.x, size.y, 3 * m * size.z}, color, false, game));

	mazeCells.push_back(new Obstacle_(glm::vec3((3 * n - 1) * size.x / 2, size.y / 2, -(3 * m - 1) * size.z / 2) + offset, {(3 * n - 2) * size.x, size.y, size.z},color, false, game));
	mazeCells.push_back(new Obstacle_(glm::vec3((3 * n - 1) * size.x / 2, size.y / 2, (3 * m - 1) * size.z / 2) + offset, {(3 * n - 2) * size.x, size.y, size.z}, color, false, game));

	{
		for (int i = 0; i < 3 * n; i++)
			map_.push_back(map[i]);

		for (int i = 1; i < 3 * n - 1; i++)
			for (int j = 1; j < 3 * m - 1; j++)
				if (map_[i][j] == 1) {
					// Walls
					int startX = i, startY = j;
					int endX = i + 1, endY = j + 1;

					while (endY < 3 * m - 1 && map_[i][endY] == 1)
						endY++;

					while (endX < 3 * n - 1) {
						bool stop = false;

						for (int l = startY; l < endY; l++)
							if (map_[endX][l] != 1) {
								stop = true;
								break;
							}

						if (stop)
							break;

						endX++;
					}

					endX--, endY--;

					for (int k = startX; k <= endX; k++)
						for (int l = startY; l <= endY; l++)
							map_[k][l] = -1;

					float randomHeight = size.y + rand() % (int)(size.y / 2);

					glm::vec3 size_((endX - startX + 1) * size.x, randomHeight, (endY - startY + 1) * size.z);
					glm::vec3 offset_(-3 * n * size.x / 2 + size_.x / 2, 0, -3 * m * size.z / 2 + size_.z / 2);
					glm::vec3 color_ = {0.254, 0.007, 0.066};

					mazeCells.push_back(new Obstacle_(glm::vec3(i * size.x, randomHeight / 2, j * size.z) + offset_, size_, color_, false, game));
				} else if (!map_[i][j]) {
					freeCells++;

					if (i == 3 * startX + 1 && j == 3 * startY + 1) {
						glm::vec3 size_(size.x, size.y, size.z);
						glm::vec3 offset_(-3 * n * size.x / 2 + size_.x / 2, 0, -3 * m * size.z / 2 + size_.z / 2);

						startingPosition.x = i * size.x;
						startingPosition.y = 2;
						startingPosition.z = j * size.z;

						startingPosition += glm::vec3(-3 * n * size.x / 2 + size_.x / 2, 0, -3 * m * size.z / 2 + size_.z / 2);
					}
				}
	}
}

std::vector<m1::Obstacle_*> m1::Map_::getMazeCells() {
	return mazeCells;
}

glm::vec3 m1::Map_::getRandomFreeCellPos() {
	int randomNo = 1 + rand() % freeCells, currNo = 0;

	for (int i = 1; i < 3 * n - 1; i++)
		for (int j = 1; j < 3 * m - 1; j++)
			if (!map_[i][j]) {
				currNo++;

				if (currNo == randomNo) {
					glm::vec3 size_(obstacleSize.x, obstacleSize.y, obstacleSize.z);
					glm::vec3 offset_(-3 * n * obstacleSize.x / 2 + size_.x / 2, 0, -3 * m * obstacleSize.z / 2 + size_.z / 2);
					glm::vec3 currPos;

					currPos.x = i * obstacleSize.x;
					currPos.y = 2;
					currPos.z = j * obstacleSize.z;

					currPos += glm::vec3(-3 * n * obstacleSize.x / 2 + size_.x / 2, 0, -3 * m * obstacleSize.z / 2 + size_.z / 2);
					return currPos;
				}
			}

	return glm::vec3(INT_MAX);
}

glm::vec3 m1::Map_::getObstacleSize() {
	return obstacleSize;
}

void m1::Map_::draw() {
	floor->draw();

	for (const auto& mazeCell : mazeCells)
		mazeCell->draw();
}
