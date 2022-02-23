#include "Obstacle.h"

#include "lab_m1/lab4/transform3D.h"

m1::Obstacle::Obstacle(const glm::vec3& pos, const std::pair<float, float>& size,
					   const std::string& color, const int type, Game* const game) : Entity(pos, size, 0, game) {
	this->pos = pos; this->size = size; this->color = color;
	this->type = type;this->game = game;
}

glm::vec3 m1::Obstacle::getPos() {
	return pos;
}

std::pair<float, float> m1::Obstacle::getSize() {
	return size;
}

std::string m1::Obstacle::getColor() {
	return color;
}

float m1::Obstacle::getSpeed() {
	return 0;
}

void m1::Obstacle::update(const float dt) {
	
}

void m1::Obstacle::draw() {
	float diagonal = sqrt(size.first * size.first + size.second * size.second);

	if (type == 1) {
		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 10);
		modelMatrix *= transform3D::Scale(size.first, size.second, 1);
		game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 9);
		modelMatrix *= transform3D::Scale(0.9 * size.first, 0.9 * size.second, 1);
		game->RenderMesh(game->getMesh(color + "DoubleColoredRectangle"), game->getShader("VertexColor"), modelMatrix);

		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 8);
		modelMatrix *= transform3D::RotateOZ(asin(size.second / diagonal));
		modelMatrix *= transform3D::Scale(0.9 * diagonal, 0.05 * size.second, 1);
		game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
	} else if (type == 2) {
		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 9);
		modelMatrix *= transform3D::Scale(size.first, size.second, 1);
		game->RenderMesh(game->getMesh(color + "Rectangle"), game->getShader("VertexColor"), modelMatrix);
	} else {
		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 7);
		modelMatrix *= transform3D::Scale(size.first, size.second, 1);
		game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 6);
		modelMatrix *= transform3D::Scale(0.9 * size.first, 0.9 * size.second, 1);
		game->RenderMesh(game->getMesh(color + "DoubleColoredRectangle"), game->getShader("VertexColor"), modelMatrix);

		modelMatrix = game->visMatrix;
		modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z - 5);
		modelMatrix *= transform3D::RotateOZ(asin(size.second / diagonal));
		modelMatrix *= transform3D::Scale(0.9 * diagonal, 0.05 * size.second, 1);
		game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
	}
}
