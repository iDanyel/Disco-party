#include "Pickup.h"

#include "lab_m1/lab4/transform3D.h"

m1::Pickup::Pickup(const glm::vec3& pos, const std::pair<float, float>& size,
				   const int type, const float lifeSpan, Game* const game) : Entity(pos, size, 0, game) {
	this->type = type; this->lifeSpan = lifeSpan;

	shrinkFactor = size.first / 2;
	dir = 1;
}

bool m1::Pickup::endOfLife() {
	return lifeSpan <= 0;
}

glm::vec3 m1::Pickup::getPos() {
	return pos;
}

std::pair<float, float> m1::Pickup::getSize() {
	return size;
}

float m1::Pickup::getSpeed() {
	return speed;
}

int m1::Pickup::getType() {
	return type;
}

float m1::Pickup::getShrinkFactor() {
	return shrinkFactor;
}

void m1::Pickup::update(const float dt) {
	time += dt;
	counter++;

	shrinkFactor += dir * 1.2 * dt;
	lifeSpan -= dt;

	if (shrinkFactor < 0.5 * size.first || shrinkFactor > 1.2 * size.first)
		dir *= -1;
}

void m1::Pickup::draw() {
	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
	modelMatrix *= transform3D::Scale(size.first * shrinkFactor, size.second * shrinkFactor, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 1);
	modelMatrix *= transform3D::Scale(0.9 * size.first * shrinkFactor, 0.9 * size.second * shrinkFactor, 1);

	if (type == 1)
		game->RenderMesh(game->getMesh("darkRedRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("darkBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 2);
	modelMatrix *= transform3D::Scale(0.3 * size.first * shrinkFactor, 0.8 * size.second * shrinkFactor, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 3);
	modelMatrix *= transform3D::Scale(0.2 * size.first * shrinkFactor, 0.7 * size.second * shrinkFactor, 1);

	if (type == 1)
		game->RenderMesh(game->getMesh("redRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("greenRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 2);
	modelMatrix *= transform3D::Scale(0.8 * size.first * shrinkFactor, 0.3 * size.second * shrinkFactor, 1);
	game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

	modelMatrix = game->visMatrix;
	modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z + 3);
	modelMatrix *= transform3D::Scale(0.7 * size.first * shrinkFactor, 0.2 * size.second * shrinkFactor, 1);
	
	if (type == 1)
		game->RenderMesh(game->getMesh("redRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 2)
		game->RenderMesh(game->getMesh("greenRectangle"), game->getShader("VertexColor"), modelMatrix);
	else if (type == 3)
		game->RenderMesh(game->getMesh("lightBlueRectangle"), game->getShader("VertexColor"), modelMatrix);
}
