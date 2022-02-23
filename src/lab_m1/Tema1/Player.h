#pragma once

#include "Entity.h"

namespace m1 {
    class Player : public Entity {
    private:
        float bodyRadians, cannonRadians;
        float shrinkFactor;

        float wheelOffset;
        float cannonOffset;

        int wheelMoveDirection;
        int cannonMoveDirection;

        bool isMoving;
        bool wasFired;
        bool powerUp;

        float currHealth, maxHealth;
        float currPowerUp, maxPowerUp;

        float timeWhenWasFired;
        float reloadTime;

        bool slowedDown;
        float slownessTime;
        float timeSinceSlowedDown;
        float timeSinceSupremeTank;

        bool supremeTank;
        int noOfBulletsFired;

        float timeWhenWasSpawned;
        bool freshlySpawned;
        int dir;

        void drawWheel(const int index);
        void drawWheels();
        void drawBody();
        void drawCannon1();
        void drawCannon2();
        void drawBars();
        void drawFreshlySpawnedCircle();

    public:
        Player(const glm::vec3 pos, const float bodyRadians, const float cannonRadians, const std::pair<float, float>& size,
               const int speed, const float maxHealth, Game* const game);

        void takeDamage(const float damage);
        void activatePowerUp();
        void activateSupremeTank();

        void increasePowerUp(const float value);
        void increaseHealth(const float health);

        void setCannonRadians(const float cannonRadians);
        void setMovement(const bool isMoving);

        void addBullet(Bullet* const bullet);

        glm::vec3 getPos() override;
        std::pair<float, float> getSize() override;
        float getSpeed() override;
        glm::vec3 getCannonPos();
        glm::vec3 getCannonPosSupremeTank(const float radians);
        float getBodyRadians();
        float getCannonRadians();
        float getHealth();
        int getDir();
        bool canBeFired();
        bool canUsePowerUp();

        void setPos(const glm::vec3 pos);
        void setBodyRadians(const float bodyRadians);
        void setSize(const std::pair<float, float>& size);
        void setCurrHealth(const float currHealth);
        void setMaxHealth(const float maxHealth);

        void moveUp(const float dt);
        void moveDown(const float dt);
        void moveLeft(const float dt);
        void moveRight(const float dt);

        bool pickupCollision(const glm::vec3& pos, Pickup* const pickup);
        bool obstacleCollision(const glm::vec3& pos, Obstacle* const obstacle);
        bool canMove(const glm::vec3& pos);
        bool isSupremeTank();
        bool isFreshlySpawned();

        void update(const float dt) override;
        void draw() override;

        std::vector<Bullet*> bullets;
    };
}
