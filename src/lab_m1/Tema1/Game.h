#pragma once

#include "components/simple_scene.h"

namespace m1 {
    class Entity;
    class Enemy;

    class Game : public gfxc::SimpleScene {
    public:
        friend class Entity;
        friend class Player;

        friend class Enemy1;
        friend class Enemy2;
        friend class Enemy3;

        friend class Bullet;
        friend class Obstacle;
        friend class Pickup;

        struct ViewportSpace {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}

            int x, y, width, height;
        };

        struct LogicSpace {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}

            float x, y, width, height;
        };

        struct Map {
            int x, y, width, height;
        };

         Game();
         ~Game();
         
        void Init() override;

        Mesh* createTriangle(const std::string& name, const glm::vec3& pos, const std::pair<float, float>& size,
                             const glm::vec3& color, const bool reversed = false, const bool filled = true);
        Mesh* createCircle(const std::string& name, const glm::vec3& center, const float& radius,
                           const int& divisions, const glm::vec3& color, const bool& filled = true);
        Mesh* createRectangle(const std::string& name, const glm::vec3& center,
                              const std::pair<float, float>& length, const glm::vec3& color, const bool& filled = true);
        Mesh* createRectangle(const std::string& name, const glm::vec3& center, const std::pair<float, float>& length,
                              const glm::vec3& color1, const glm::vec3& color2, const bool& filled = true);

        Mesh* getMesh(const std::string& name);
        Shader* getShader(const std::string& name);

        float getEuclidianDistance(const glm::vec2& point1, const glm::vec2& point2);

        float getMouseAngle(const glm::ivec2& coordinates);
        float getAngle(const glm::vec2& point1, const glm::vec2& point2);

        float convertAngle(const float radians, const float offset);

        std::vector<glm::vec3> getRectangleCorners(const glm::vec3& pos, const std::pair<float, float>& size, const float radians);

        bool playerBordersCollision(Player* const player, const std::vector<Obstacle*> walls);

        bool playerObstacleCollision(Player* const player, Obstacle* const obstacle);
        
    private:
        void FrameStart() override;
        void Update(float dt) override;
        void FrameEnd() override;
        
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::mat4 VisualizationTransf(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear);

        bool obstacleObstacleCollision(Obstacle* const obstacle1, Obstacle* const obstacle2);

        bool isAValidRandomization(const glm::vec3& pos, const std::pair<float, float>& size);
        bool isAValidRandomizationV2(const glm::vec3& pos, const std::pair<float, float>& size);

        void setMapBorders(const Map& map, const std::pair<float, float>& cellSize);
        void setMapCells(const Map& map, const std::pair<float, float>& cellSize);
        void generateObstacles(const Map& map, const std::pair<float, float>& obstacleSize, const int no);
        void generateEnemies(const Map& map, const std::pair<float, float>& enemySize, const float maxSpeed, const int no);
        void generatePickups(const Map& map, const std::pair<float, float>& pickupSize, const float lifeSpan, const int no);
        void drawMiniMap(const float zoom);
        void restartGame();

     protected:
         float gameTime;
         float timeAtLastPickup;

         Map map;
         Player* player;

         ViewportSpace viewSpace;
         LogicSpace logicSpace;

         glm::mat4 modelMatrix;
         glm::mat4 visMatrix;

         std::pair<float, float> logicSpaceSize;

         float radians;

         std::vector<Obstacle*> walls;
         std::vector<Obstacle*> cells;
         std::vector<Obstacle*> obstacles;

         std::vector<Enemy*> enemies;
         std::vector<Bullet*> bullets;
         std::vector<Pickup*> pickups;

         float score;
         int wave;

         bool paused;
    };
}
