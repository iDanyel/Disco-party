#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"
#include <random>

namespace m1 {
    class Game_ : public gfxc::SimpleScene {
    public:
        Game_();
        ~Game_();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const GLenum primitive);

    private:
        friend class Human_;
        friend class Player_;
        friend class Enemy_;
        friend class Map_;
        friend class Obstacle_;
        friend class Bullet_;

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const bool isDeformed = false);
        void generateEnemies(int no);
        void generatePortal();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        implemented::Camera* camera;
        implemented::Camera* freeCamera;
        implemented::Camera* hud_camera;
        implemented::Camera* firstPersonCamera;
        implemented::Camera* thirdPersonCamera;
        implemented::Camera* reversedThirdPersonCamera;

        glm::mat4 projectionMatrix;
        glm::mat4 modelMatrix;

        float timeSinceLastPickup;
        float timeSinceLastEnemy;
        float timeWhenPaused;

        float fov, fovSpeed;
        float zNear, zFar;
        float freeCameraSpeed;

        glm::vec3 playerCameraOffset;
        glm::vec3 startingPosition;
        glm::vec3 lightPosition;

        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        Map_* map;
        Player_* player;
        std::vector<Enemy_*> enemies;
        Obstacle_* portal;
        std::vector<Obstacle_*> lifePickups;
        std::vector<Obstacle_*> timePickups;

        bool paused;
    };
}
