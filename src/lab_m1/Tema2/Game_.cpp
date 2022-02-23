#include "Game_.h"
#include "Player_.h"
#include "Enemy_.h"
#include "Map_.h"
#include "Map_.h"
#include "Obstacle_.h"
#include "Colliders_.h"
#include <time.h>

using namespace m1;

Game_::Game_() {
    srand(time(NULL));

    fov = glm::pi<float>() / 3;
    fovSpeed = 5;

    zNear = 0.1f;
    zFar = 200.0f;
    freeCameraSpeed = 20;

    playerCameraOffset = glm::vec3(0, 1, 6.5);
    paused = false;

    // Light and material properties
    lightPosition = glm::vec3(0, 30, 0);
    materialShininess = 30;
    materialKd = 0.75;
    materialKs = 0.5;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Game_::~Game_() {

}

void Game_::Init() {
    // Create filled circle
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(1, 0, 0))
        };

        std::vector<uint32_t> indices = {0} ;
        float angularStep = 2 * glm::pi<float>() / 100;

        for (int i = 1; i <= 100; i++) {
            float angle = i * angularStep;
            glm::vec3 vertex = glm::vec3(cos(angle), sin(angle), 0);

            vertices.push_back(VertexFormat(vertex));
            indices.push_back(i);
        }

        CreateMesh("filledCircle", vertices, indices, GL_TRIANGLE_FAN);
    }

    // Create filled cube
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1, -1,  1)),
            VertexFormat(glm::vec3( 1, -1,  1)),
            VertexFormat(glm::vec3(-1,  1,  1)),
            VertexFormat(glm::vec3( 1,  1,  1)),
            VertexFormat(glm::vec3(-1, -1, -1)),
            VertexFormat(glm::vec3( 1, -1, -1)),
            VertexFormat(glm::vec3(-1,  1, -1)),
            VertexFormat(glm::vec3( 1,  1, -1))
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,    1, 3, 2,
            2, 3, 7,    2, 7, 6,
            1, 7, 3,    1, 5, 7,
            6, 7, 4,    7, 5, 4,
            0, 4, 1,    1, 4, 5,
            2, 6, 4,    0, 2, 4
        };

        CreateMesh("filledCube", vertices, indices, GL_TRIANGLES);
    }

    // Create unfilled cube
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1, -1, -1)),
            VertexFormat(glm::vec3(-1, -1,  1)),
            VertexFormat(glm::vec3( 1, -1,  1)),
            VertexFormat(glm::vec3( 1, -1, -1)),
            VertexFormat(glm::vec3(-1,  1, -1)),
            VertexFormat(glm::vec3(-1,  1,  1)),
            VertexFormat(glm::vec3( 1,  1,  1)),
            VertexFormat(glm::vec3( 1,  1, -1))
        };

        std::vector<unsigned int> indices = {
            4, 5, 5, 6, 6, 7, 7, 4,
            0, 4, 4, 7, 7, 3, 3, 0,
            3, 7, 7, 6, 6, 2, 2, 3,
            5, 4, 4, 0, 0, 1, 1, 5,
            2, 1, 1, 5, 5, 6, 6, 2,
            0, 1, 1, 2, 2, 3, 3, 0
        };

        CreateMesh("unfilledCube", vertices, indices, GL_LINES);
    }

    // Create filled square
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1, -1, 0)),
            VertexFormat(glm::vec3(-1,  1, 0)),
            VertexFormat(glm::vec3( 1, -1, 0)),
            VertexFormat(glm::vec3( 1,  1, 0))
        };

        std::vector<unsigned int> indices = {
            0, 2, 1,
            1, 2, 3
        };

        CreateMesh("filledSquare", vertices, indices, GL_TRIANGLES);
    }

    // Create unfilled square
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1, -1, 0)),
            VertexFormat(glm::vec3(-1,  1, 0)),
            VertexFormat(glm::vec3( 1, -1, 0)),
            VertexFormat(glm::vec3( 1,  1, 0))
        };

        std::vector<unsigned int> indices = {
            0, 1, 1, 3, 3, 2, 2, 0
        };

        CreateMesh("unfilledSquare", vertices, indices, GL_LINES);
    }

    {
        Shader* shader = new Shader("homework2Shader");

        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders_", "VertexShader_.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders_", "FragmentShader_.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    map = new Map_(15, 15, {5, 10, 5}, startingPosition, this);
    player = new Player_(startingPosition, {1, 4, 0.5}, 5, this);

    freeCamera = new implemented::Camera(true, false, false);
    hud_camera = new implemented::Camera(false, false, false);
    firstPersonCamera = new implemented::Camera(true, false, false);

    thirdPersonCamera = new implemented::Camera(false, true, false);
    reversedThirdPersonCamera = new implemented::Camera(false, true, true);

    thirdPersonCamera->distanceToTarget = glm::distance(player->getCenter(), player->getCenter() - player->getDirZ() * playerCameraOffset.z);
    reversedThirdPersonCamera->distanceToTarget = glm::distance(player->getCenter(), player->getCenter() + player->getDirZ() * playerCameraOffset.z);

    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

    camera = thirdPersonCamera;
    thirdPersonCamera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
    thirdPersonCamera->TranslateUpwardGlobal(playerCameraOffset.y);

    generateEnemies(20);
    generatePortal();

    timeSinceLastPickup = 0;
    timeSinceLastEnemy = 0;

    int randomPickup = rand() % 2;

    if (!randomPickup)
        lifePickups.push_back(new Obstacle_(map->getRandomFreeCellPos(), {1, 1, 1}, {1, 0, 0}, false, this));
    else
        timePickups.push_back(new Obstacle_(map->getRandomFreeCellPos(), {1, 1, 1}, {1, 1, 0}, false, this));
}

Mesh* Game_::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const GLenum primitive) {
    unsigned int VAO = 0;

    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    meshes[name]->SetDrawMode(primitive);
    return meshes[name];
}

void Game_::FrameStart() {
    glClearColor(0.047, 0.019, 0.278, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);

    window->HidePointer();
}

void Game_::Update(float deltaTimeSeconds) {
    if (paused)
        return;

    timeSinceLastPickup += deltaTimeSeconds;

    if (enemies.size() < 50)
        timeSinceLastEnemy += deltaTimeSeconds;

    if (timeSinceLastPickup >= 5) {
        int randomPickup = rand() % 2;

        if (!randomPickup)
            lifePickups.push_back(new Obstacle_(map->getRandomFreeCellPos(), {1, 1, 1}, {1, 0, 0}, false, this));
        else
            timePickups.push_back(new Obstacle_(map->getRandomFreeCellPos(), {1, 1, 1}, {1, 1, 0}, false, this));

        timeSinceLastPickup = 0;
    }

    if (timeSinceLastEnemy >= 5) {
        generateEnemies(1);
        timeSinceLastEnemy = 0;
    }

    player->update(deltaTimeSeconds);
    portal->setAngle(portal->getAngle() - deltaTimeSeconds);

    std::vector<Obstacle_*> remainingLifePickups;

    for (const auto& lifePickup : lifePickups)
        if (lifePickup->getTime() >= 10)
            delete lifePickup;
        else {
            lifePickup->setAngle(lifePickup->getAngle() - deltaTimeSeconds);
            lifePickup->update(deltaTimeSeconds);
            remainingLifePickups.push_back(lifePickup);
        }

    lifePickups.erase(lifePickups.begin(), lifePickups.end());

    for (const auto& lifePickup : remainingLifePickups)
        lifePickups.push_back(lifePickup);

    std::vector<Obstacle_*> remainingTimePickups;

    for (const auto& timePickup : timePickups)
        if (timePickup->getTime() >= 10)
            delete timePickup;
        else {
            timePickup->setAngle(timePickup->getAngle() - deltaTimeSeconds);
            timePickup->update(deltaTimeSeconds);
            remainingTimePickups.push_back(timePickup);
        }
        

    timePickups.erase(timePickups.begin(), timePickups.end());

    for (const auto& timePickup : remainingTimePickups)
        timePickups.push_back(timePickup);

    std::vector<Enemy_*> remainingEnemies;

    for (const auto& enemy : enemies)
        if (enemy->endOfLife())
            delete enemy;
        else {
            enemy->update(deltaTimeSeconds);
            remainingEnemies.push_back(enemy);
        }

    enemies.erase(enemies.begin(), enemies.end());

    for (const auto& enemy : remainingEnemies)
        enemies.push_back(enemy);

    if (player->won()) {
        std::cout << "You won!\n";
        exit(1);
    }

    if (player->gameOver()) {
        std::cout << "Game over!\n";
        exit(1);
    }
}

void Game_::FrameEnd() {
    player->draw();
    map->draw();

    for (const auto& enemy : enemies)
        enemy->draw();

    portal->draw();

    for (const auto& lifePickup : lifePickups)
        lifePickup->draw();

    for (const auto& timePickup : timePickups)
        timePickup->draw();
}

void Game_::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const bool isDeformed) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set shader uniform "View" to viewMatrix
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    // Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Used for object's color
    glUniform3fv(glGetUniformLocation(shader->program, "objectColor"), 1, glm::value_ptr(color));

    // Used for deformation
    glUniform1i(glGetUniformLocation(shader->program, "deformation"), isDeformed);

    if (paused)
        glUniform1f(glGetUniformLocation(shader->program, "engineTime"), timeWhenPaused);
    else
        glUniform1f(glGetUniformLocation(shader->program, "engineTime"), Engine::GetElapsedTime());

    // Used for light
    glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));
    glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(player->getCenter() + glm::vec3(0, 1, 0)));
    glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
    glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);
    glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);
    glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void m1::Game_::generateEnemies(int no) {
    for (int i = 0; i < no; i++) {
        enemies.push_back(new Enemy_(map->getRandomFreeCellPos(), {1, 4, 0.5}, 3 + rand() % 3, this));
        enemies.back()->setShirtColor({0.968, 0.482, 0.031});

        if (colliders::AABB_AABB_collision({enemies.back()->getCenter(), enemies.back()->getSize()}, {player->getCenter(), player->getSize()}) ||
            glm::distance(enemies.back()->getCenter(), player->getCenter()) <= 5) {
                delete enemies.back();
                enemies.pop_back();
        }
    }
}

void m1::Game_::generatePortal() {
    float maxDistance = 0;
    glm::vec3 bestPos;

    for (int i = 0; i < 100; i++) {
        glm::vec3 pos = map->getRandomFreeCellPos();

        if (glm::distance(startingPosition, pos) > maxDistance) {
            maxDistance = glm::distance(startingPosition, pos);
            bestPos = pos;
        }
    }

    portal = new Obstacle_(bestPos, {1, 1, 1}, {0, 0, 1}, false, this);
}

void Game_::OnInputUpdate(float deltaTime, int mods) {
    if (paused) {
        if (window->KeyHold(GLFW_KEY_UP) || window->KeyHold(GLFW_KEY_W))
            camera->MoveForward(freeCameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_DOWN) || window->KeyHold(GLFW_KEY_S))
            camera->MoveForward(-freeCameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_RIGHT) || window->KeyHold(GLFW_KEY_D))
            camera->MoveRight(freeCameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_A))
            camera->MoveRight(-freeCameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_SPACE))
            camera->TranslateUpwardGlobal(freeCameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
            camera->TranslateUpwardGlobal(-freeCameraSpeed * deltaTime);

        return;
    }

    bool isMoving = false;

    if (window->KeyHold(GLFW_KEY_UP) || window->KeyHold(GLFW_KEY_W))
        if (player->canMove('u', deltaTime)) {
            if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
                player->setMovement(false, true);
            else
                player->setMovement();

            player->moveForward(deltaTime);
            camera->MoveForward(player->getCurrSpeed() * deltaTime);
            isMoving = true;
        }

    if (window->KeyHold(GLFW_KEY_DOWN) || window->KeyHold(GLFW_KEY_S))
        if (player->canMove('d', deltaTime)) {
            if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
                player->setMovement(false, true);
            else
                player->setMovement();

            player->moveForward(-deltaTime);
            camera->MoveForward(-player->getCurrSpeed() * deltaTime);
            isMoving = true;
        }

    if (window->KeyHold(GLFW_KEY_RIGHT) || window->KeyHold(GLFW_KEY_D))
        if (player->canMove('r', deltaTime)) {
            if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
                player->setMovement(false, true);
            else
                player->setMovement();

            player->moveRight(deltaTime);
            camera->MoveRight(player->getCurrSpeed() * deltaTime);
            isMoving = true;
        }

    if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_A))
        if (player->canMove('l', deltaTime)) {
            if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
                player->setMovement(false, true);
            else
                player->setMovement();

            player->moveRight(-deltaTime);
            camera->MoveRight(-player->getCurrSpeed() * deltaTime);
            isMoving = true;
        }

    if (!isMoving)
        player->setMovement(false, false);
}

void Game_::OnKeyPress(int key, int mods) {
    if (!paused) {
        if (key == GLFW_KEY_SPACE)
            if (player->canJump())
                player->jump();

        if (key == GLFW_KEY_1)
            if (camera != firstPersonCamera) {
                camera = thirdPersonCamera;
                camera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
                camera->TranslateUpwardGlobal(playerCameraOffset.y);
                camera->angleX = 0;
            }

        if (key == GLFW_KEY_2)
            if (camera != firstPersonCamera) {
                camera = reversedThirdPersonCamera;
                camera->Set(player->getCenter() + player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
                camera->TranslateUpwardGlobal(playerCameraOffset.y);
                camera->angleX = 0;
            }
    }

    if (key == GLFW_KEY_P) {
        camera = thirdPersonCamera;
        camera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
        camera->TranslateUpwardGlobal(playerCameraOffset.y);
        player->setAiming(false);
        camera->angleX = 0;

        camera = freeCamera;
        camera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
        camera->TranslateUpwardGlobal(2 * playerCameraOffset.y);
        paused = true;
        camera->angleX = 0;

        timeWhenPaused = Engine::GetElapsedTime();
    }
   
    if (key == GLFW_KEY_R) {
        camera = thirdPersonCamera;
        camera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
        camera->TranslateUpwardGlobal(playerCameraOffset.y);
        player->setAiming(false);
        paused = false;
        camera->angleX = 0;
    }
}

void Game_::OnKeyRelease(int key, int mods) {
   
}

void Game_::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    float sensivityOX = 0.005f;
    float sensivityOY = 0.01f;

    if (!paused)
        player->rotate(-sensivityOY * deltaX);

    camera->rotateOY(-sensivityOY * deltaX);
    window->SetPointerPosition(window->GetResolution().x / 2, window->GetResolution().y / 2);

    if (camera == freeCamera) {
        float newAngleX = camera->angleX - sensivityOX * deltaY;

        if (newAngleX >= -glm::pi<float>() / 2 && newAngleX <= glm::pi<float>() / 2)
            camera->rotateOX(-sensivityOX * deltaY);
    } else if (camera != firstPersonCamera) {
        float newAngleX = camera->angleX - sensivityOX * deltaY;

        if (newAngleX >= -glm::pi<float>() / 2 && newAngleX <= glm::pi<float>() / 7.5)
            camera->rotateOX(-sensivityOX * deltaY);
    } else {
        float newAngleX = camera->angleX - sensivityOX * deltaY;

        if (newAngleX >= -glm::pi<float>() / 7.5 && newAngleX <= glm::pi<float>() / 7.5)
            camera->rotateOX(-sensivityOX * deltaY);
    }
}

void Game_::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (paused)
        return;

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        if (player->canFire())
            player->addBullet();

    if (button == GLFW_MOUSE_BUTTON_RIGHT + 1) {
        camera = firstPersonCamera;
        camera->forward = player->getForwardVector();
        camera->right = player->getRightVector();
        camera->up = player->getUpVector();
        camera->position = player->getCenter();
        camera->TranslateUpwardGlobal(0.5);
        player->setAiming(true);
        camera->angleX = 0;
    }
}

void Game_::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    if (paused)
        return;

    if (button == GLFW_MOUSE_BUTTON_RIGHT + 1) {
        camera = thirdPersonCamera;
        camera->Set(player->getCenter() - player->getDirZ() * playerCameraOffset.z, player->getCenter(), {0, 1, 0});
        camera->TranslateUpwardGlobal(playerCameraOffset.y);
        player->setAiming(false);
        camera->angleX = 0;
    }
}

void Game_::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Game_::OnWindowResize(int width, int height) {

}
