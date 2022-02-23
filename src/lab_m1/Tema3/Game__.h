#pragma once

#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"

namespace m1 {
    class Game__ : public gfxc::SimpleScene {
    public:
        Game__();
        ~Game__();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const GLenum primitive);

    private:
        friend class DanceFloor;
        friend class DiscoBall;
        friend class Dancer;
        friend class Wall;

        struct LightSource;

        void FrameStart() override;
        void Update(float dt) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const std::vector<LightSource>& lightCells, const bool simple,
                              const bool transparent, const bool reflector, const bool discoBall , const glm::vec3& color, const Texture2D* texture = nullptr);
        Texture2D* Game__::CreateRandomTexture(unsigned int width, unsigned int height);
        void generateDancers(const int no);
        void generateWalls();
        void generateReflectors();

        void drawFloor();
        void drawCeiling();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        struct LightSource {
            LightSource(const glm::vec3& pos, const glm::vec3& color, const glm::vec3& dir, const float intensity, const bool spot)
                : pos(pos), color(color), dir(dir), intensity(intensity), spot(spot) {
                timeSinceLastDirSwitch = 0;

                int randomNo1 = rand() % 2;
                int randomNo2 = rand() % 2;
                int randomNo3 = rand() % 2;

                if (randomNo1 == 1)
                    dir1 = 1;
                else
                    dir1 = -1;

                if (randomNo2 == 1)
                    dir2 = 1;
                else
                    dir2 = -1;

                if (randomNo3 == 1)
                    dir3 = 1;
                else
                    dir3 = -1;

                randomFactor = (float)(10 + rand() % 20) / 5000;
                randomTime = 3 + rand() % 5;
            }

            glm::vec3 pos, color, dir;
            float intensity;
            bool spot;

            float timeSinceLastDirSwitch;
            int dir1, dir2, dir3;
            float randomFactor, randomTime;
            glm::vec3 rotationAxis;
            float timeSinceLastRotationDirSwitch;
            int rotationDir1, rotationDir2;
            float angleX, angleZ;
            float randomAngleX, randomAngleZ;
        };

        implemented::Camera* camera;
        DanceFloor* danceFloor;
        DiscoBall* discoBall;

        std::vector<Dancer*> dancers;
        std::vector<Wall*> walls;

        glm::mat4 projectionMatrix;
        glm::mat4 modelMatrix;

        float fov, zNear, zFar, cameraSpeed;
        float kd, ks, shininess, cutOffAngle, lightRadius;

        std::unordered_map<std::string, Texture2D*> mapTextures;

        std::vector<LightSource> lightCells;
        std::vector<LightSource> reflectors;
        LightSource ball;

        bool paused;
        float discoBallRotationTime;

        bool lightCellIlluminationMode;
        bool reflectorIlluminationMode;
        bool discoBalllIlluminationMode;
    };
}
