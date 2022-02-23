#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Pickup.h"

#include "lab_m1/lab4/transform3D.h"

void m1::Player::drawWheel(const int index) {
    float offsetX, offsetY;

    if (index == 1 || index == 2)
        offsetX = size.first / 2;
    else
        offsetX = -size.first / 2;

    if (index == 2 || index == 3)
        offsetY = -size.second / 2;
    else
        offsetY = size.second / 2;

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 0);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.3 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(offsetX, (offsetY + wheelOffset) / 2.25, 1);
    modelMatrix *= transform3D::Scale(0.075 * size.first, 0.2 * size.second, 1);
    game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);
    
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(1.1 * offsetX, (offsetY + wheelOffset) / 2.25, 0);
    modelMatrix *= transform3D::Scale(0.1 * size.first, 0.25 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Player::drawWheels() {
    for (int i = 0; i < 4; i++)
        drawWheel(i);
}

void m1::Player::drawBody() {
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, 0, 2);
    modelMatrix *= transform3D::Scale(size.first, size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, 0, 3);
    modelMatrix *= transform3D::Scale(0.9 * size.first, 0.9 * size.second, 1);
    game->RenderMesh(game->getMesh("lightGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, 0, 4);
    modelMatrix *= transform3D::Scale(0.7 * size.first, 0.7 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, 0, 5);
    modelMatrix *= transform3D::Scale(0.6 * size.first, 0.6 * size.second, 1);
    game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(-size.first / 3, size.second / 2, 0);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.2 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(-size.first / 3, size.second / 1.9, 3);
    modelMatrix *= transform3D::Scale(0.05 * size.first, 0.05 * size.second, 1);
    game->RenderMesh(game->getMesh("lightGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(size.first / 3,size.second / 2, 0);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.2 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(size.first / 3, size.second / 1.9, 3);
    modelMatrix *= transform3D::Scale(0.05 * size.first, 0.05 * size.second, 1);
    game->RenderMesh(game->getMesh("lightGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, -size.second / 2, 0);
    modelMatrix *= transform3D::Scale(0.7 * size.first, 0.2 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(0, -size.second / 2, 5);
    modelMatrix *= transform3D::Scale(0.6 * size.first, 0.1 * size.second, 1);
    game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Player::drawCannon1() {
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 0, 6);
    modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.first, 1);
    game->RenderMesh(game->getMesh("blackCircle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 0, 7);
    modelMatrix *= transform3D::Scale(0.25 * size.first, 0.25 * size.first, 1);
    game->RenderMesh(game->getMesh("lightGreenCircle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, size.second / 2, 6);
    modelMatrix *= transform3D::Scale(0.25 * size.first, 0.9 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, size.second / 2, 7);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.8 * size.second, 1);
    game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 1.7 * size.second / 2, 8);
    modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 1.5 * size.second / 2, 8);
    modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 1.3 * size.second / 2, 8);
    modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Player::drawCannon2() {
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, size.second, 6);
    modelMatrix *= transform3D::Scale(0.25 * size.first, 0.3 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, size.second, 7);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.2 * size.second, 1);
    game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 1.1 * size.second, 8);
    modelMatrix *= transform3D::Scale(0.25 * size.first, 0.1 * size.second, 1);
    game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
    modelMatrix *= transform3D::RotateOZ(-cannonRadians);
    modelMatrix *= transform3D::Translate(0, 1.1 * size.second, 9);
    modelMatrix *= transform3D::Scale(0.15 * size.first, 0.05 * size.second, 1);
    game->RenderMesh(game->getMesh("lightGreenRectangle"), game->getShader("VertexColor"), modelMatrix);
}

void m1::Player::drawBars() {
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(size.first, size.second / 2, 20);
    modelMatrix *= transform3D::Scale(0.5 * size.first, 0.1 * size.second, 1);
    game->RenderMesh(game->getMesh("blackUnfilledRectangle"), game->getShader("VertexColor"), modelMatrix);

    if (currHealth > 0) {
        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(size.first - (1 - currHealth / maxHealth) * size.first / 4, size.second / 2, 20);
        modelMatrix *= transform3D::Scale(0.5 * size.first * currHealth / maxHealth, 0.1 * size.second, 1);
        game->RenderMesh(game->getMesh("redRectangle"), game->getShader("VertexColor"), modelMatrix);
    }

    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::RotateOZ(-bodyRadians);
    modelMatrix *= transform3D::Translate(size.first, size.second / 3, 20);
    modelMatrix *= transform3D::Scale(0.5 * size.first, 0.1 * size.second, 1);
    game->RenderMesh(game->getMesh("blackUnfilledRectangle"), game->getShader("VertexColor"), modelMatrix);

    if (currPowerUp > 0) {
        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(size.first - (1 - currPowerUp / maxPowerUp) * size.first / 4, size.second / 3, 20);
        modelMatrix *= transform3D::Scale(0.5 * size.first * currPowerUp / maxPowerUp, 0.1 * size.second, 1);
        game->RenderMesh(game->getMesh("greenRectangle"), game->getShader("VertexColor"), modelMatrix);
    }

    if (noOfBulletsFired && time - timeWhenWasFired < reloadTime) {
        float currDiff = time - timeWhenWasFired;

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(size.first, size.second / 6, 20);
        modelMatrix *= transform3D::Scale(0.5 * size.first, 0.1 * size.second, 1);
        game->RenderMesh(game->getMesh("blackUnfilledRectangle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(size.first - (1 - currDiff / reloadTime) * size.first / 4, size.second / 6, 20);
        modelMatrix *= transform3D::Scale(0.5 * size.first * currDiff / reloadTime, 0.1 * size.second, 1);
        game->RenderMesh(game->getMesh("yellowRectangle"), game->getShader("VertexColor"), modelMatrix);
    }
}

void m1::Player::drawFreshlySpawnedCircle() {
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::Scale(size.first * shrinkFactor, size.first * shrinkFactor, 1);
    game->RenderMesh(game->getMesh("blackUnfilledCircle"), game->getShader("VertexColor"), modelMatrix);
    
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::Scale(0.995 * size.first * shrinkFactor, 0.995 * size.first * shrinkFactor, 1);
    game->RenderMesh(game->getMesh("blackUnfilledCircle"), game->getShader("VertexColor"), modelMatrix);
    
    modelMatrix = game->visMatrix;
    modelMatrix *= transform3D::Translate(pos.x, pos.y, pos.z);
    modelMatrix *= transform3D::Scale(0.99 * size.first * shrinkFactor, 0.99 * size.first * shrinkFactor, 1);
    game->RenderMesh(game->getMesh("blackUnfilledCircle"), game->getShader("VertexColor"), modelMatrix);
}

m1::Player::Player(const glm::vec3 pos, const float bodyRadians, const float cannonRadians, const std::pair<float, float>& size,
                   const int speed, const float maxHealth, Game* const game) : Entity(pos, size, speed, game) {
    this->bodyRadians = bodyRadians; this->cannonRadians = cannonRadians;
    this->maxHealth = maxHealth; this->size = size;

    currHealth = maxHealth;

    wheelOffset = 0;
    cannonOffset = 0;

    wheelMoveDirection = 1;
    cannonMoveDirection = 1;

    wasFired = false;
    isMoving = false;

    currPowerUp = 100;
    maxPowerUp = 100;

    powerUp = false;
    reloadTime = 0.35;

    noOfBulletsFired = 0;
    timeWhenWasFired = 0;

    slowedDown = false;
    slownessTime = 2.5;

    timeSinceSupremeTank = 0;
    supremeTank = false;

    timeWhenWasSpawned = 0;
    freshlySpawned = true;

    shrinkFactor = size.first / 2;
    dir = 1;
}

void m1::Player::takeDamage(const float damage) {
    if (freshlySpawned)
        return;

    if (supremeTank)
        currHealth -= damage / 2;
    else
        currHealth -= damage;
}

void m1::Player::activatePowerUp() {
    wasFired = false;
    powerUp = true;
}

void m1::Player::activateSupremeTank() {
    supremeTank = true;
}

void m1::Player::increasePowerUp(const float value) {
    currPowerUp = std::min(maxPowerUp, currPowerUp + value);
}

void m1::Player::increaseHealth(const float health) {
    currHealth = std::min(maxHealth, currHealth + health);
}

void m1::Player::setPos(const glm::vec3 pos) {
    this->pos = pos;
}

void m1::Player::setBodyRadians(const float bodyRadians) {
    this->bodyRadians = bodyRadians;
}

void m1::Player::setSize(const std::pair<float, float>& size) {
    this->size = size;
}

void m1::Player::setCurrHealth(const float currHealth) {
    this->currHealth = currHealth;
}

void m1::Player::setMaxHealth(const float maxHealth) {
    this->maxHealth = maxHealth;
}

void m1::Player::setCannonRadians(const float cannonRadians) {
    this->cannonRadians = cannonRadians;
}

void m1::Player::setMovement(const bool isMoving) {
    this->isMoving = isMoving;
}

glm::vec3 m1::Player::getPos() {
    return pos;
}

std::pair<float, float> m1::Player::getSize() {
    return size;
}

glm::vec3 m1::Player::getCannonPos() {
    glm::vec3 cannonPos(0, size.second, 6);

    cannonPos = glm::vec3(cannonPos.x * cos(cannonRadians) - cannonPos.y * sin(cannonRadians),
                          cannonPos.x * sin(cannonRadians) + cannonPos.y * cos(cannonRadians),
                          cannonPos.z);
    cannonPos += glm::vec3(pos.x, pos.y, pos.z);

    return cannonPos;
}

glm::vec3 m1::Player::getCannonPosSupremeTank(const float radians) {
    glm::vec3 cannonPos(0, 1.3 * size.second, 6);

    cannonPos = glm::vec3(cannonPos.x * cos(radians) - cannonPos.y * sin(radians),
                          cannonPos.x * sin(radians) + cannonPos.y * cos(radians),
                          cannonPos.z);
    cannonPos += glm::vec3(pos.x, pos.y, pos.z);

    return cannonPos;
}

float m1::Player::getBodyRadians() {
    return bodyRadians;
}

float m1::Player::getCannonRadians() {
    return cannonRadians;
}

float m1::Player::getHealth() {
    return currHealth;
}

int m1::Player::getDir() {
    return dir;
}

bool m1::Player::canBeFired() {
    return !wasFired && !powerUp && !freshlySpawned;
}

bool m1::Player::canUsePowerUp() {
    return currPowerUp > 0;
}

float m1::Player::getSpeed() {
    return speed;
}

bool m1::Player::pickupCollision(const glm::vec3& pos, Pickup* const pickup) {
    glm::vec2 halfSize(pickup->getSize().first / 2, pickup->getSize().second / 2);
    glm::vec2 difference = pos - pickup->getPos();

    glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
    glm::vec2 closest = pickup->getPos();

    closest += clamped;
    difference = closest - glm::vec2(pos.x, pos.y);

    return glm::length(difference) < 1.05 * std::min(size.first / 2, size.second / 2);
}

bool m1::Player::obstacleCollision(const glm::vec3& pos, Obstacle* const obstacle) {
    glm::vec2 halfSize(obstacle->getSize().first / 2, obstacle->getSize().second / 2);
    glm::vec2 difference = pos - obstacle->getPos();

    glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
    glm::vec2 closest = obstacle->getPos();

    closest += clamped;
    difference = closest - glm::vec2(pos.x, pos.y);

    return glm::length(difference) < 1.05 * std::min(size.first / 2, size.second / 2);
}

bool m1::Player::canMove(const glm::vec3& pos) {
    for (const auto& obstacle : game->walls)
        if (obstacleCollision(pos, obstacle))
            return false;

    for (const auto& obstacle : game->obstacles)
        if (obstacleCollision(pos, obstacle)) {
            if (obstacle->getColor() == "red")
                takeDamage(2);
            else if (obstacle->getColor() == "blue" && !freshlySpawned) {
                if (!slowedDown) {
                    slowedDown = true;
                    speed /= 2.5;
                } else
                    timeSinceSlowedDown = 0;
            }

            return false;
        }

    return true;
}

bool m1::Player::isSupremeTank() {
    return supremeTank;
}

bool m1::Player::isFreshlySpawned() {
    return freshlySpawned;
}

void m1::Player::moveUp(const float dt) {
    if (canMove({pos.x, pos.y + speed * dt, pos.z})) {
        pos.y += speed * dt;
        game->logicSpace.y += speed * dt;
    }
}

void m1::Player::moveDown(const float dt) {
    if (canMove({pos.x, pos.y - speed * dt, pos.z})) {
        pos.y -= speed * dt;
        game->logicSpace.y -= speed * dt;
    }
}

void m1::Player::moveLeft(const float dt) {
    if (canMove({pos.x - speed * dt, pos.y, pos.z})) {
        pos.x -= speed * dt;
        game->logicSpace.x -= speed * dt;
    }
}

void m1::Player::moveRight(const float dt) {
    if (canMove({pos.x + speed * dt, pos.y, pos.z})) {
        pos.x += speed * dt;
        game->logicSpace.x += speed * dt;
    }
}

void m1::Player::update(const float dt) {
    time += dt;
    counter++;

    if (isMoving) {
        if (!(counter % 3))
            wheelMoveDirection *= -1;

        if (!(counter % 5))
            cannonMoveDirection *= -1;

        wheelOffset += 0.5 * wheelMoveDirection * dt;
        cannonOffset += 0.25 * cannonMoveDirection * dt;
    } else {
        wheelOffset = 0;
        cannonOffset = 0;

        wheelMoveDirection = 1;
        cannonMoveDirection = 1;
    }

    if (powerUp) {
        if (!(counter % 3) && !freshlySpawned) {
            if (!supremeTank) {
                bullets.push_back(new Bullet(getCannonPos(), {size.first / 8, size.second / 5}, cannonRadians, 2 * speed , 1, 1, game));
                noOfBulletsFired++;
            } else {
                int divisions = 20;
                float oldCannonRadians = cannonRadians;

                for (int i = 1; i <= divisions; i++) {
                    bullets.push_back(new Bullet(getCannonPosSupremeTank(cannonRadians), {size.first / 8, size.second / 5}, cannonRadians, 2 * speed, 1, 1, game));
                    cannonRadians += 2 * glm::pi<float>() / divisions;
                }

                cannonRadians = oldCannonRadians;
                noOfBulletsFired += divisions;
            }
        }

        if (!freshlySpawned)
            currPowerUp -= maxPowerUp / 2 * dt;

        if (currPowerUp <= 0)
            powerUp = false;
    } else if (wasFired && time - timeWhenWasFired >= reloadTime)
        wasFired = false;

    std::vector<Bullet*> remainingBullets;

    for (const auto& bullet : bullets)
        if (bullet->endOfLife())
            delete bullet;
        else {
            bullet->update(dt);

            bool collision = false;

            for (const auto& enemy : game->enemies)
                if (bullet->enemyCollision(bullet->getPos(), enemy)) {
                    if (dynamic_cast<Enemy3*>(enemy))
                        enemy->takeDamage(10 * (supremeTank ? 2 : 1));
                    else
                        enemy->takeDamage(20 * (supremeTank ? 2 : 1));

                    delete bullet;
                    collision = true;
                    break;
                }

            if (!collision)
                remainingBullets.push_back(bullet);
        }

    bullets.erase(bullets.begin(), bullets.end());

    for (const auto& bullet : remainingBullets)
        bullets.push_back(bullet);

    powerUp = false;

    if (slowedDown) {
        timeSinceSlowedDown += dt;

        if (timeSinceSlowedDown > slownessTime) {
            slowedDown = false;
            timeSinceSlowedDown = 0;
            speed *= 2.5;
        }
    }

    currPowerUp = std::min(maxPowerUp, currPowerUp + 2 * dt);

    if (supremeTank) {
        timeSinceSupremeTank += dt;

        if (timeSinceSupremeTank >= 10) {
            supremeTank = false;
            timeSinceSupremeTank = 0;
        }
    }

    if (freshlySpawned && time - timeWhenWasSpawned >= 5)
        freshlySpawned = false;

    if (freshlySpawned) {
        shrinkFactor += dir * dt;

        if (shrinkFactor < 0.4 * size.first || shrinkFactor > 0.75 * size.first)
            dir *= -1;
    }
}

void m1::Player::addBullet(Bullet* const bullet) {
    bullets.push_back(bullet);
    wasFired = true;
    timeWhenWasFired = time;
    noOfBulletsFired++;
}

void m1::Player::draw() {
    if (freshlySpawned)
        drawFreshlySpawnedCircle();

    drawWheels();
    drawBody();
    drawBars();

    for (const auto& bullet : bullets)
        bullet->draw();

    if (!supremeTank)
        drawCannon1();
    else {
        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, 0, 6);
        modelMatrix *= transform3D::Scale(0.3 * size.first, 0.3 * size.first, 1);
        game->RenderMesh(game->getMesh("blackCircle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, 0, 7);
        modelMatrix *= transform3D::Scale(0.25 * size.first, 0.25 * size.first, 1);
        game->RenderMesh(game->getMesh("lightGreenCircle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, size.second / 2, 6);
        modelMatrix *= transform3D::Scale(0.25 * size.first, 0.6 * size.second, 1);
        game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, size.second / 2, 7);
        modelMatrix *= transform3D::Scale(0.15 * size.first, 0.5 * size.second, 1);
        game->RenderMesh(game->getMesh("darkGreenRectangle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, 1.4 * size.second / 2, 8);
        modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
        game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, 1.2  * size.second / 2, 8);
        modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
        game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

        modelMatrix = game->visMatrix;
        modelMatrix *= transform3D::Translate(pos.x, pos.y + cannonOffset, pos.z);
        modelMatrix *= transform3D::RotateOZ(-bodyRadians);
        modelMatrix *= transform3D::Translate(0, size.second / 2, 8);
        modelMatrix *= transform3D::Scale(0.07 * size.first, 0.075 * size.second, 1);
        game->RenderMesh(game->getMesh("blackRectangle"), game->getShader("VertexColor"), modelMatrix);

        int divisions = 20;
        float oldCannonRadians = cannonRadians;

        for (int i = 1; i <= divisions; i++) {
            drawCannon2();
            cannonRadians += 2 * glm::pi<float>() / divisions;
        }

        cannonRadians = oldCannonRadians;
    }
}
