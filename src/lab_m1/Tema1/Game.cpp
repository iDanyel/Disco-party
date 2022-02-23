#include <vector>
#include <random>
#include <ctime>
#include <time.h>

#include "Game.h"

#include "Player.h"

#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"

#include "Bullet.h"
#include "Obstacle.h"
#include "Pickup.h"

#include "lab_m1/lab4/transform3D.h"

using namespace m1;

Game::Game() {
    srand(time(NULL));
    gameTime = 0;
    timeAtLastPickup = 0;
    score = 0;
    wave = 0;
    paused = false;
}

Game::~Game() {

}

void Game::Init() {
    auto camera = GetSceneCamera();

    GetCameraInput()->SetActive(false);
    camera->SetPosition(glm::vec3(0, 0, 100));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    logicSpaceSize.first = 30;
    logicSpaceSize.second = 20;

    logicSpace.x = -logicSpaceSize.first / 2;
    logicSpace.y = -logicSpaceSize.second / 2;

    logicSpace.width = logicSpaceSize.first;
    logicSpace.height = logicSpaceSize.second;

    map.x = -2 * logicSpaceSize.first;
    map.y = -2 * logicSpaceSize.second;

    map.width = 4 *logicSpaceSize.first;
    map.height = 4 * logicSpaceSize.second;

    AddMeshToList(createCircle("blackCircle", {0, 0, 0}, 1, 100, {0, 0, 0}));
    AddMeshToList(createCircle("orangeCircle", {0, 0, 0}, 1, 100, {1, 0.388, 0.054}));
    AddMeshToList(createCircle("blueCircle", {0, 0, 0}, 1, 100, {0.023, 0.270, 0.925}));
    AddMeshToList(createCircle("purpleCircle", {0, 0, 0}, 1, 100, {0.768, 0.168, 0.6}));
    AddMeshToList(createCircle("darkGreenCircle", {0, 0, 0}, 1, 100, {0, 0.501, 0.25}));
    AddMeshToList(createCircle("lightGreenCircle", {0, 0, 0}, 1, 100, {0.133, 0.694, 0.298}));
    AddMeshToList(createCircle("lightBlueCircle", {0, 0, 0}, 1, 100, {0, 0.501, 1}));
    AddMeshToList(createRectangle("blackRectangle", {0, 0, 0}, {1, 1}, {0, 0, 0}));
    AddMeshToList(createRectangle("darkGreenRectangle", {0, 0, 0}, {1, 1}, {0, 0.501, 0.25}));
    AddMeshToList(createRectangle("lightGreenRectangle", {0, 0, 0}, {1, 1}, {0.133, 0.694, 0.298}));
    AddMeshToList(createRectangle("blackUnfilledRectangle", {0, 0, 0}, {1, 1}, {0, 0, 0}, false));
    AddMeshToList(createRectangle("redRectangle", {0, 0, 0}, {1, 1}, {1, 0, 0}));
    AddMeshToList(createRectangle("greenRectangle", {0, 0, 0}, {1, 1}, {0, 1, 0}));
    AddMeshToList(createRectangle("yellowRectangle", {0, 0, 0}, {1, 1}, {0.933, 0.901, 0.105}));
    AddMeshToList(createRectangle("blueGrayRectangle", {0, 0, 0}, {1, 1}, {0.439, 0.572, 0.745}));
    AddMeshToList(createRectangle("turquoiseRectangle", {0, 0, 0}, {1, 1}, {0, 0.635, 0.909}));
    AddMeshToList(createCircle("blackUnfilledCircle", {0, 0, 0}, 1, 100, {0, 0, 0}, false));
    AddMeshToList(createRectangle("grayDoubleColoredRectangle", {0, 0, 0}, {1, 1}, {0.298, 0.298, 0.298}, {0.5, 0.5, 0.5}));
    AddMeshToList(createRectangle("redDoubleColoredRectangle", {0, 0, 0}, {1, 1}, {0.6, 0.023, 0.043}, {0.905, 0.094, 0.125}));
    AddMeshToList(createRectangle("blueDoubleColoredRectangle", {0, 0, 0}, {1, 1}, {0.043, 0.054, 0.376}, {0.145, 0.172, 0.831}));
    AddMeshToList(createRectangle("limeRectangle", {0, 0, 0}, {1, 1}, {0.407, 0.933, 0.105}));
    AddMeshToList(createRectangle("smaraldRectangle", {0, 0, 0}, {1, 1}, {0.215, 0.643, 0.098}));
    AddMeshToList(createRectangle("darkBlueRectangle", {0, 0, 0}, {1, 1}, {0.023, 0.270, 0.925}));
    AddMeshToList(createRectangle("lightBlueRectangle", {0, 0, 0}, {1, 1}, {0, 0.501, 1}));
    AddMeshToList(createRectangle("lightPurpleRectangle", {0, 0, 0}, {1, 1}, {0.639, 0.286, 0.643}));
    AddMeshToList(createRectangle("darkPurpleRectangle", {0, 0, 0}, {1, 1}, {0.768, 0.168, 0.6}));
    AddMeshToList(createTriangle("blackTriangle", {0, 0, 0}, {1, 1}, {0, 0, 0}));
    AddMeshToList(createTriangle("blackReversedTriangle", {0, 0, 0}, {1, 1}, {0, 0, 0}, true));
    AddMeshToList(createTriangle("darkPurpleTriangle", {0, 0, 0}, {1, 1}, {0.768, 0.168, 0.6}));
    AddMeshToList(createTriangle("darkPurpleReversedTriangle", {0, 0, 0}, {1, 1}, {0.768, 0.168, 0.6}, true));
    AddMeshToList(createRectangle("orangeRectangle", {0, 0, 0}, {1, 1}, {1, 0.388, 0.054}));
    AddMeshToList(createRectangle("blueRectangle", {0, 0, 0}, {1, 1}, {0.043, 0.054, 0.376}));
    AddMeshToList(createRectangle("yellowRectangle", {0, 0, 0}, {1, 1}, {1, 0.788, 0.054}));
    AddMeshToList(createRectangle("lightYellowRectangle", {0, 0, 0}, {1, 1}, {1, 0.929, 0.121}));
    AddMeshToList(createRectangle("lightOrangeRectangle", {0, 0, 0}, {1, 1}, {1, 0.560, 0.121}));
    AddMeshToList(createRectangle("lightGrayRectangle", {0, 0, 0}, {1, 1}, {0.5, 0.5, 0.5}));
    AddMeshToList(createRectangle("darkGrayRectangle", {0, 0, 0}, {1, 1}, {0.298, 0.298, 0.298}));
    AddMeshToList(createRectangle("darkRedRectangle", {0, 0, 0}, {1, 1}, {0.7, 0.023, 0.043}));

    player = new Player({0, 0, 0}, 0, 0, {2.5, 3}, 8, 100, this);

    setMapCells(map, {4, 4});
    setMapBorders(map, {4, 4 });
    generateObstacles(map, {4, 4}, 100);
}

void Game::FrameStart() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);
}

void Game::Update(float dt) {
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5), true);
    visMatrix = VisualizationTransf(logicSpace, viewSpace);

    if (paused)
        return;

    player->update(dt);

    std::vector<Enemy*> remainingEnemies;
    
    for (const auto& enemy : enemies) {
        enemy->update(dt);

        if (!player->isFreshlySpawned() && enemy->playerCollision(enemy->getPos(), player)) {
            if (dynamic_cast<Enemy3*>(enemy))
                player->takeDamage(70);
            else
                player->takeDamage(30);

            if (dynamic_cast<Enemy1*>(enemy))
                for (const auto& bullet : ((Enemy1*)enemy)->bullets)
                    bullets.push_back(bullet);
            else if (dynamic_cast<Enemy2*>(enemy))
                for (const auto& bullet : ((Enemy2*)enemy)->bullets)
                    bullets.push_back(bullet);

            delete enemy;
        } else if (enemy->getHealth() <= 0) {
            player->increasePowerUp(5);
            player->increaseHealth(10);
            
            if (dynamic_cast<Enemy1*>(enemy)) {
                for (const auto& bullet : ((Enemy1*)enemy)->bullets)
                    bullets.push_back(bullet);

                score += 15;
            } else if (dynamic_cast<Enemy2*>(enemy)) {
                for (const auto& bullet : ((Enemy2*)enemy)->bullets)
                    bullets.push_back(bullet);

                score += 25;
            } else
                score += 50;

            delete enemy;
        } else
            remainingEnemies.push_back(enemy);
    }

    enemies.erase(enemies.begin(), enemies.end());

    for (const auto& enemy : remainingEnemies)
        enemies.push_back(enemy);

    std::vector<Bullet*> remainingBullets;

    for (const auto& bullet : bullets)
        if (bullet->endOfLife())
            delete bullet;
        else {
            bullet->update(dt);

            if (bullet->playerCollision(bullet->getPos(), player)) {
                player->takeDamage(1);
                delete bullet;
            } else
                remainingBullets.push_back(bullet);
        }

    bullets.erase(bullets.begin(), bullets.end());

    for (const auto& bullet : remainingBullets)
        bullets.push_back(bullet);

    std::vector<Pickup*> remainingPickups;

    for (const auto& pickup : pickups)
        if (pickup->endOfLife())
            delete pickup;
        else {
            pickup->update(dt);

            if (player->pickupCollision(player->getPos(), pickup)) {
                if (pickup->getType() == 1)
                    player->increaseHealth(50);
                else if (pickup->getType() == 2)
                    player->increasePowerUp(50);
                else if (pickup->getType() == 3)
                    player->activateSupremeTank();

                score += 10;
                delete pickup;
            } else
                remainingPickups.push_back(pickup);
        }

    pickups.erase(pickups.begin(), pickups.end());

    for (const auto& pickup : remainingPickups)
        pickups.push_back(pickup);

    gameTime += dt;

    if (enemies.empty()) {
        generateEnemies(map, {2.5, 3}, 8, ++wave);
        std::cout << "Wave " << wave << " is coming!\n";
    }

    if (gameTime - timeAtLastPickup >= 5) {
        generatePickups(map, {1, 1}, 10, 3);
        timeAtLastPickup = gameTime;
    }
}

void Game::FrameEnd() {
    if (paused) {
        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(logicSpace.x + 1, logicSpace.y + logicSpace.height - 1, 60);
        modelMatrix *= transform3D::Scale(0.7, 1.5, 1);
        RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(logicSpace.x + 1, logicSpace.y + logicSpace.height - 1, 61);
        modelMatrix *= transform3D::Scale(0.5, 1.3, 1);
        RenderMesh(getMesh("redRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(logicSpace.x + 2, logicSpace.y + logicSpace.height - 1, 60);
        modelMatrix *= transform3D::Scale(0.7, 1.5, 1);
        RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(logicSpace.x + 2, logicSpace.y + logicSpace.height - 1, 61);
        modelMatrix *= transform3D::Scale(0.5, 1.3, 1);
        RenderMesh(getMesh("redRectangle"), getShader("VertexColor"), modelMatrix);
    }

    if (player->getHealth() <= 0)
        restartGame();

    for (const auto& wall : walls)
        if (wall->isOnScreen())
            wall->draw();

    for (const auto& cell : cells)
        if (cell->isOnScreen())
            cell->draw();
    
    for (const auto& obstacle : obstacles)
        if (obstacle->isOnScreen())
            obstacle->draw();

    player->draw();
    
    for (const auto& enemy : enemies)
        enemy->draw();

    for (const auto& bullet : bullets)
        bullet->draw();

    for (const auto& pickup : pickups)
        pickup->draw();

    drawMiniMap(2);
}

void Game::OnInputUpdate(float deltaTime, int mods) {
    if (paused)
        return;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        if (player->canUsePowerUp())
            player->activatePowerUp();

    bool movementType1 = false;
    bool movementType2 = false;

    bool movementType3 = false;
    bool movementType4 = false;

    player->setMovement(false);

    // Up
    if (window->KeyHold(GLFW_KEY_W) || window->KeyHold(GLFW_KEY_UP))
        movementType1 = true;

    // Down
    if (window->KeyHold(GLFW_KEY_S) || window->KeyHold(GLFW_KEY_DOWN))
        movementType2 = true;

    // Left
    if (window->KeyHold(GLFW_KEY_A) || window->KeyHold(GLFW_KEY_LEFT))
        movementType3 = true;

    // Right
    if (window->KeyHold(GLFW_KEY_D) || window->KeyHold(GLFW_KEY_RIGHT))
        movementType4 = true;

    if (movementType1 && movementType2 && movementType3 && movementType4) {
        player->setBodyRadians(0);
        return;
    }

    if (movementType1 && movementType3 && movementType4) {
        player->setBodyRadians(0);
        return;
    }

    if (movementType2 && movementType3 && movementType4) {
        player->setBodyRadians(glm::pi<float>());
        return;
    }

    if (movementType3 && movementType1 && movementType2) {
        player->setBodyRadians(glm::pi<float>() / 2);
        return;
    }

    if (movementType4 && movementType1 && movementType2) {
        player->setBodyRadians(3 * glm::pi<float>() / 2);
        return;
    }

    if (movementType1 && movementType3) {
        player->moveUp(deltaTime);
        player->moveLeft(deltaTime);
        player->setBodyRadians(glm::pi<float>() / 4);
        player->setMovement(true);
        return;
    }
    
    if (movementType1 && movementType4) {
        player->moveUp(deltaTime);
        player->moveRight(deltaTime);
        player->setBodyRadians(7 * glm::pi<float>() / 4);
        player->setMovement(true);
        return;
    }
    
    if (movementType2 && movementType3) {
        player->moveDown(deltaTime);
        player->moveLeft(deltaTime);
        player->setBodyRadians(3 * glm::pi<float>() / 4);
        player->setMovement(true);
        return;
    }
    
    if (movementType2 && movementType4) {
        player->moveDown(deltaTime);
        player->moveRight(deltaTime);
        player->setBodyRadians(5 * glm::pi<float>() / 4);
        player->setMovement(true);
        return;
    }
    
    if (movementType1) {
        player->moveUp(deltaTime);
        player->setBodyRadians(0);
        player->setMovement(true);
        return;
    }
    
    if (movementType2) {
        player->moveDown(deltaTime);
        player->setBodyRadians(glm::pi<float>());
        player->setMovement(true);
        return;
    }
    
    if (movementType3) {
        player->moveLeft(deltaTime);
        player->setBodyRadians(glm::pi<float>() / 2);
        player->setMovement(true);
        return;
    }
    
    if (movementType4) {
        player->moveRight(deltaTime);
        player->setBodyRadians(3 * glm::pi<float>() / 2);
        player->setMovement(true);
        return;
    }
}

void Game::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_P)
        paused = true;

    if (key == GLFW_KEY_R)
        paused = false;
}

void Game::OnKeyRelease(int key, int mods) {
    
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    if (paused)
        return;

    player->setCannonRadians(convertAngle(getMouseAngle({mouseX, window->GetResolution().y - mouseY}), -glm::pi<float>() / 2));
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (paused)
        return;

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        if (player->canBeFired()) {
            radians = convertAngle(getMouseAngle({mouseX, window->GetResolution().y - mouseY}), -glm::pi<float>() / 2);

            if (!player->isSupremeTank())
                player->addBullet(new Bullet(player->getCannonPos(), {player->getSize().first / 8, player->getSize().second / 5}, radians, 2 * player->getSpeed(), 1, 1, this));
            else {
                int divisions = 20;
                float oldRadians = radians;

                for (int i = 1; i <= divisions; i++) {
                    player->addBullet(new Bullet(player->getCannonPosSupremeTank(radians), {player->getSize().first / 8, player->getSize().second / 5}, radians, 2 * player->getSpeed(), 1, 1, this));
                    radians += 2 * glm::pi<float>() / divisions;
                }

                radians = oldRadians;
            }
      }
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Game::OnWindowResize(int width, int height) {

}

glm::mat4 m1::Game::VisualizationTransf(const LogicSpace& logicSpace, const ViewportSpace& viewSpace) {
    float sx = viewSpace.width / logicSpace.width;
    float sy = viewSpace.height / logicSpace.height;

    float tx = viewSpace.x - sx * logicSpace.x;
    float ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat4(
        sx, 0, 0, tx,
        0, sy, 0, ty,
        0, 0, 1, 0,
        0, 0, 0, 1));
}

void m1::Game::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear) {
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    float x = viewSpace.x;
    float y = viewSpace.y;

    float width = viewSpace.width;
    float height = viewSpace.height;

    GetSceneCamera()->SetOrthographic(x, x + width, y, y + height, 0.1, 400);
    GetSceneCamera()->Update();
}

bool m1::Game::obstacleObstacleCollision(Obstacle* const obstacle1, Obstacle* const obstacle2) {
    glm::vec3 pos1 = obstacle1->getPos(), pos2 = obstacle2->getPos();
    std::pair<float, float> size1 = obstacle1->getSize(), size2 = obstacle2->getSize();

    glm::vec3 leftBottomCorner1(pos1.x - size1.first / 2, pos1.y - size1.second / 2, pos1.z);
    glm::vec3 leftBottomCorner2(pos2.x - size2.first / 2, pos2.y - size2.second / 2, pos2.z);

    bool collisionX = leftBottomCorner1.x < leftBottomCorner2.x + size2.first &&
                      leftBottomCorner1.x + size1.first > leftBottomCorner2.x;

    bool collisionY = leftBottomCorner1.y < leftBottomCorner2.y + size2.second &&
                      leftBottomCorner1.y + size1.second > leftBottomCorner2.y;
    
    return collisionX && collisionY;
}

bool m1::Game::isAValidRandomization(const glm::vec3& pos, const std::pair<float, float>& size) {
    Obstacle newObstacle(pos, size, "", 1, this);

    for (const auto& obstacle : obstacles)
        if (obstacleObstacleCollision(&newObstacle, obstacle))
            return false;

    if (obstacleObstacleCollision(&newObstacle, &Obstacle(player->getPos(), player->getSize(), "", 1, this)))
        return false;

    return true;
}

bool m1::Game::isAValidRandomizationV2(const glm::vec3& pos, const std::pair<float, float>& size) {
    for (const auto& wall : walls) {
        glm::vec2 halfSize(wall->getSize().first / 2, wall->getSize().second / 2);
        glm::vec2 difference = pos - wall->getPos();

        glm::vec2 clamped = glm::clamp(difference, -halfSize, halfSize);
        glm::vec2 closest = wall->getPos();

        closest += clamped;
        difference = closest - glm::vec2(pos.x, pos.y);

        if (glm::length(difference) < std::min(size.first / 2, size.second / 2))
            return false;
    }

    float radius1 = std::min(size.first, size.second);
    float radius2 = std::min(player->getSize().first, player->getSize().second);

    return !(getEuclidianDistance(pos, player->getPos()) <= radius1 + radius2);
}

void m1::Game::setMapBorders(const Map& map, const std::pair<float, float>& cellSize) {
    for (int i = map.y; i <= map.y + map.height; i += cellSize.second)
        if (i == map.y || i == map.y + map.height)
            for (int j = map.x; j <= map.x + map.width; j += cellSize.first)
                walls.push_back(new Obstacle({j + cellSize.first / 2, i + cellSize.second / 2, 0}, cellSize, "gray", 1, this));
        else {
            walls.push_back(new Obstacle({map.x + cellSize.first / 2, i + cellSize.second / 2, 0}, cellSize, "gray", 1, this));
            walls.push_back(new Obstacle({map.x + map.width + cellSize.first / 2, i + cellSize.second / 2, 0}, cellSize, "gray", 1, this));
   }
}

void m1::Game::setMapCells(const Map& map, const std::pair<float, float>& cellSize) {
    int counter = 0;

    for (int i = map.y + cellSize.second; i <= map.y + map.height - cellSize.second; i += cellSize.second)
        for (int j = map.x + cellSize.first; j <= map.x + map.width - cellSize.first; j += cellSize.first) {
            if (!(counter % 2))
                cells.push_back(new Obstacle({j + cellSize.first / 2, i + cellSize.second / 2, 0}, cellSize, "lightGray", 2, this));
            else
                cells.push_back(new Obstacle({j + cellSize.first / 2, i + cellSize.second / 2, 0}, cellSize, "darkGray", 2, this));

            counter++;
        }
}

void m1::Game::generateObstacles(const Map& map, const std::pair<float, float>& obstacleSize, const int no) {
    std::unordered_map<int, std::string> colors;

    colors[0] = "red";
    colors[1] = "blue";

    for (int i = 1; i <= no; i++)
        for (int j = 1; j <= 10; j++) {
            float posX = map.x + 3 * obstacleSize.first / 2;
            float posY = map.y + 3 * obstacleSize.second / 2;

            posX += (rand() % ((map.width - 4) / (int)obstacleSize.first)) * obstacleSize.first;
            posY += (rand() % ((map.height - 4) / (int)obstacleSize.second)) * obstacleSize.second;

            if (isAValidRandomization({posX, posY, 0}, obstacleSize)) {
                obstacles.push_back(new Obstacle({posX, posY, 0}, obstacleSize, colors[rand() % 2], 3, this));
                break;
       }
}
}

void m1::Game::generateEnemies(const Map& map, const std::pair<float, float>& enemySize, const float maxSpeed, const int no) {
    for (int i = 1; i <= no; i++) {
        float posX = (rand() % (map.width * 100)) / 100;
        float posY = (rand() % (map.height * 100)) / 100;

        int enemyType = rand() % 3;
        float offset = std::min(50, (int)enemies.size() * 10);
 
        for (int j = 0; j < 10; j++)
            if (isAValidRandomizationV2({map.x + posX, map.y + posY, 0}, enemySize)) {
                if (enemyType == 1)
                    enemies.push_back(new Enemy1({map.x + posX, map.y + posY, offset}, enemySize, rand() % (int)maxSpeed + 1, 0, 100, this));
                else if (enemyType == 2)
                    enemies.push_back(new Enemy2({map.x + posX, map.y + posY, offset}, enemySize, rand() % (int)maxSpeed + 1, 0, 150, this));
                else
                    enemies.push_back(new Enemy3({map.x + posX, map.y + posY, offset}, enemySize, 0.5 * (rand() % (int)maxSpeed + 1), 0, 200, this));

                break;
            }
    }
}

void m1::Game::generatePickups(const Map& map, const std::pair<float, float>& pickupSize, const float lifeSpan, const int no) {
    for (int i = 1; i <= no; i++)
        for (int j = 1; j <= 10; j++) {
            float posX = map.x + 5;
            float posY = map.y + 5;

            posX += (rand() % ((map.width - 5) / (int)pickupSize.first)) * pickupSize.first;
            posY += (rand() % ((map.height - 5) / (int)pickupSize.second)) * pickupSize.second;

            if (isAValidRandomization({ posX, posY, 0 }, pickupSize)) {
                pickups.push_back(new Pickup({posX, posY, 0}, pickupSize, rand() % 3 + 1, lifeSpan, this));
                break;
            }
        }
}

void m1::Game::drawMiniMap(const float zoom) {
    glm::ivec2 resolution = window->GetResolution();
    LogicSpace newLogicSpace = logicSpace;

    newLogicSpace.x -= newLogicSpace.width / zoom;
    newLogicSpace.y -= newLogicSpace.height / zoom;

    newLogicSpace.width *= zoom;
    newLogicSpace.height *= zoom;

    modelMatrix = visMatrix;
    modelMatrix *= transform3D::Translate(logicSpace.x + logicSpace.width, logicSpace.y + logicSpace.height, 50);
    modelMatrix *= transform3D::Scale(1.0175 * logicSpace.width / 2, 1.025 * logicSpace.height / 2, 1);
    RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

    viewSpace = ViewportSpace(3 * resolution.x / 4, 3 * resolution.y / 4, resolution.x / 4, resolution.y / 4);
    SetViewportArea(viewSpace, glm::vec3(0.5), true);
    visMatrix = VisualizationTransf(newLogicSpace, viewSpace);

    // Player
    {
        float radius = std::max(player->getSize().first, player->getSize().second);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(player->getPos().x, player->getPos().y, player->getPos().z);
        modelMatrix *= transform3D::Scale(0.5 * radius, 0.5 * radius, 1);
        RenderMesh(getMesh("blackCircle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(player->getPos().x, player->getPos().y, player->getPos().z + 1);
        modelMatrix *= transform3D::Scale(0.4 * radius, 0.4 * radius, 1);
        RenderMesh(getMesh("darkGreenCircle"), getShader("VertexColor"), modelMatrix);
    }

    for (const auto& bullet : player->bullets) {
        float radius = std::max(bullet->getSize().first, bullet->getSize().second);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z);
        modelMatrix *= transform3D::Scale(1.5 * radius, 1.5 * radius, 1);
        RenderMesh(getMesh("blackCircle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z + 1);
        modelMatrix *= transform3D::Scale(radius, radius, 1);
        RenderMesh(getMesh("darkGreenCircle"), getShader("VertexColor"), modelMatrix);
    }

    // Enemies
    for (const auto& enemy : enemies) {
        float radius = std::max(enemy->getSize().first, enemy->getSize().second);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(enemy->getPos().x, enemy->getPos().y, enemy->getPos().z);
        modelMatrix *= transform3D::Scale(0.5 * radius, 0.5 * radius, 1);
        RenderMesh(getMesh("blackCircle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(enemy->getPos().x, enemy->getPos().y, enemy->getPos().z + 1);
        modelMatrix *= transform3D::Scale(0.4 * radius, 0.4 * radius, 1);

        if (dynamic_cast<Enemy1*>(enemy))
            RenderMesh(getMesh("orangeCircle"), getShader("VertexColor"), modelMatrix);
        if (dynamic_cast<Enemy2*>(enemy))
            RenderMesh(getMesh("blueCircle"), getShader("VertexColor"), modelMatrix);
        else
            RenderMesh(getMesh("purpleCircle"), getShader("VertexColor"), modelMatrix);

        for (const auto& bullet : enemy->bullets) {
            float radius = std::max(bullet->getSize().first, bullet->getSize().second);

            modelMatrix = visMatrix;
            modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z);
            modelMatrix *= transform3D::Scale(1.5 * radius, 1.5 * radius, 1);
            RenderMesh(getMesh("blackCircle"), getShader("VertexColor"), modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z + 1);
            modelMatrix *= transform3D::Scale(radius, radius, 1);

            if (bullet->getType() == 2)
                RenderMesh(getMesh("orangeCircle"), getShader("VertexColor"), modelMatrix);
            if (bullet->getType() == 3)
                RenderMesh(getMesh("blueCircle"), getShader("VertexColor"), modelMatrix);
            else
                RenderMesh(getMesh("purpleCircle"), getShader("VertexColor"), modelMatrix);
        }
    }

    // After bullets
    for (const auto& bullet : bullets) {
        float radius = std::max(bullet->getSize().first, bullet->getSize().second);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z);
        modelMatrix *= transform3D::Scale(1.5 * radius, 1.5 * radius, 1);
        RenderMesh(getMesh("blackCircle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(bullet->getPos().x, bullet->getPos().y, bullet->getPos().z + 1);
        modelMatrix *= transform3D::Scale(radius, radius, 1);

        if (bullet->getType() == 2)
            RenderMesh(getMesh("orangeCircle"), getShader("VertexColor"), modelMatrix);
        if (bullet->getType() == 3)
            RenderMesh(getMesh("blueCircle"), getShader("VertexColor"), modelMatrix);
        else
            RenderMesh(getMesh("purpleCircle"), getShader("VertexColor"), modelMatrix);
    }

    // Walls
    for (const auto& wall : walls) {
        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(wall->getPos().x, wall->getPos().y, wall->getPos().z);
        modelMatrix *= transform3D::Scale(wall->getSize().first, wall->getSize().second, 1);
        RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(wall->getPos().x, wall->getPos().y, wall->getPos().z + 1);
        modelMatrix *= transform3D::Scale(0.9 * wall->getSize().first, 0.9 * wall->getSize().second, 1);
        RenderMesh(getMesh("darkGrayRectangle"), getShader("VertexColor"), modelMatrix);
    }

    // Obstacles
    for (const auto& obstacle : obstacles) {
        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(obstacle->getPos().x, obstacle->getPos().y, obstacle->getPos().z - 2);
        modelMatrix *= transform3D::Scale(obstacle->getSize().first, obstacle->getSize().second, 1);
        RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(obstacle->getPos().x, obstacle->getPos().y, obstacle->getPos().z - 1);
        modelMatrix *= transform3D::Scale(0.9 * obstacle->getSize().first, 0.9 * obstacle->getSize().second, 1);

        if (obstacle->getColor() == "red")
            RenderMesh(getMesh("darkRedRectangle"), getShader("VertexColor"), modelMatrix);
        else if (obstacle->getColor() == "blue")
            RenderMesh(getMesh("blueRectangle"), getShader("VertexColor"), modelMatrix);
    }

    // Pickups
    for (const auto& pickup : pickups) {
        float shrinkFactor = pickup->getShrinkFactor();

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(pickup->getPos().x, pickup->getPos().y, pickup->getPos().z);
        modelMatrix *= transform3D::Scale(pickup->getSize().first * shrinkFactor, pickup->getSize().second * shrinkFactor, 1);
        RenderMesh(getMesh("blackRectangle"), getShader("VertexColor"), modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform3D::Translate(pickup->getPos().x, pickup->getPos().y, pickup->getPos().z + 1);
        modelMatrix *= transform3D::Scale(0.8 * pickup->getSize().first * shrinkFactor, 0.8 * pickup->getSize().second * shrinkFactor, 1);

        if (pickup->getType() == 1)
            RenderMesh(getMesh("redRectangle"), getShader("VertexColor"), modelMatrix);
        else if (pickup->getType() == 2)
            RenderMesh(getMesh("greenRectangle"), getShader("VertexColor"), modelMatrix);
        else if (pickup->getType() == 3)
            RenderMesh(getMesh("lightBlueRectangle"), getShader("VertexColor"), modelMatrix);
    }
}

void m1::Game::restartGame() {
    std::cout << "Yor score is: " << score << "!\n\n";

    for (const auto& bullet : player->bullets)
        delete bullet;

    delete player;

    for (const auto& enemy : enemies) {
        for (const auto& bullet : enemy->bullets)
            delete bullet;

        delete enemy;
    }

    for (const auto& bullet : bullets)
        delete bullet;

    for (const auto& pickup : pickups)
        delete pickup;

    for (const auto& obstacle : obstacles)
        delete obstacle;

    enemies.erase(enemies.begin(), enemies.end());
    bullets.erase(bullets.begin(), bullets.end());
    pickups.erase(pickups.begin(), pickups.end());
    obstacles.erase(obstacles.begin(), obstacles.end());

    player = new Player({0, 0, 0}, 0, 0, {2.5, 3}, 8, 100, this);

    generateObstacles(map, {4, 4}, 100);

    logicSpace.x = -logicSpace.width / 2;
    logicSpace.y = -logicSpace.height / 2;

    gameTime = 0;
    timeAtLastPickup = 0;
    score = 0;
    wave = 0;
    paused = false;
}

float m1::Game::getEuclidianDistance(const glm::vec2& point1, const glm::vec2& point2) {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

float m1::Game::getMouseAngle(const glm::ivec2& coordinates) {
    glm::ivec2 windowCenter = window->GetResolution() / 2;
    float distance1 = fabs(coordinates.x - windowCenter.x);
    float distance2 = getEuclidianDistance(coordinates, windowCenter);

    if (!distance2)
        return 0;

    float radians = acos(distance1 / distance2);

    if (coordinates.x <= windowCenter.x && coordinates.y >= windowCenter.y)
        radians = glm::pi<float>() - radians;
    else if (coordinates.x <= windowCenter.x && coordinates.y <= windowCenter.y)
        radians += glm::pi<float>();
    else if (coordinates.x >= windowCenter.x && coordinates.y <= windowCenter.y)
        radians = 2 * glm::pi<float>() - radians;

    return radians;
}

float m1::Game::getAngle(const glm::vec2& point1, const glm::vec2& point2) {
    float distance = getEuclidianDistance(point1, point2);

    if (!distance)
        return 0;

    float radians = asin(fabs(point2.y - point1.y) / distance);

    if (point2.x <= point1.x && point2.y >= point1.y)
        radians = glm::pi<float>() - radians;
    else if (point2.x <= point1.x && point2.y <= point1.y)
        radians += glm::pi<float>();
    else if (point2.x >= point1.x && point2.y <= point1.y)
        radians = 2 * glm::pi<float>() - radians;

    return radians;
}

float m1::Game::convertAngle(const float radians, const float offset) {
    if (radians + offset <= 0)
        return radians + offset + 2 * glm::pi<float>();

    if (radians + offset >= 2 * glm::pi<float>())
        return radians + offset - 2 * glm::pi<float>();

    return radians + offset;
}

std::vector<glm::vec3> m1::Game::getRectangleCorners(const glm::vec3& pos, const std::pair<float, float>& size, const float radians) {
    std::vector<glm::vec3> currentCorners(4), rotatedCorners(4);

    currentCorners[0] = pos + glm::vec3(-size.first / 2, size.second / 2, 0);
    currentCorners[1] = pos + glm::vec3(-size.first / 2, -size.second / 2, 0);
    currentCorners[2] = pos + glm::vec3(size.first / 2, -size.second / 2, 0);
    currentCorners[3] = pos + glm::vec3(size.first / 2, size.second / 2, 0);

    for (int i = 0; i < 4; i++) {
        rotatedCorners[i].x = currentCorners[i].x * cos(radians) - currentCorners[i].y * sin(radians);
        rotatedCorners[i].y = currentCorners[i].x * sin(radians) + currentCorners[i].y * cos(radians);
        rotatedCorners[i].z = currentCorners[i].z;
}

    return rotatedCorners;
}

bool m1::Game::playerBordersCollision(Player* const player, const std::vector<Obstacle*> walls) {
    for (const auto& wall : walls)
        if (playerObstacleCollision(player, wall))
            return true;

    return false;
}

bool m1::Game::playerObstacleCollision(Player* const player, Obstacle* const obstacle) {
    glm::vec3 pos1 = player->getPos(), pos2 = obstacle->getPos();
    std::pair<float, float> size1 = player->getSize(), size2 = obstacle->getSize();

    if (getEuclidianDistance({pos1.x, pos1.y}, {pos2.x, pos2.y}) <= (std::min(size1.first, size1.second) + std::min(size2.first, size2.second)) / 2)
        return true;

    return false;
}

Mesh* m1::Game::createTriangle(const std::string& name, const glm::vec3& pos, const std::pair<float, float>& size,
                               const glm::vec3& color, const bool reversed, const bool filled) {
    Mesh* triangle = new Mesh(name);

    std::vector<VertexFormat> vertices;

    if (!reversed) {
        glm::vec3 leftBottomCorner((3 * pos.x - size.first) / 3, (3 * pos.y - size.second) / 3, pos.z);

        vertices = {
            VertexFormat(leftBottomCorner, color),
            VertexFormat(leftBottomCorner + glm::vec3(0, size.second, 0), color),
            VertexFormat(leftBottomCorner + glm::vec3(size.first, 0, 0), color)
        };
    } else {
        glm::vec3 leftBottomCorner((3 * pos.x + size.first) / 3, (3 * pos.y - size.second) / 3, pos.z);

        vertices = {
            VertexFormat(leftBottomCorner, color),
            VertexFormat(leftBottomCorner + glm::vec3(0, size.second, 0), color),
            VertexFormat(leftBottomCorner - glm::vec3(size.first, 0, 0), color)
        };
    }

    std::vector<uint32_t> indices = {0, 1, 2};

    if (!filled)
        triangle->SetDrawMode(GL_LINE_LOOP);

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* m1::Game::createCircle(const std::string& name, const glm::vec3& pos, const float& radius,
                             const int& divisions, const glm::vec3& color, const bool& filled) {
    Mesh* circle = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(pos + glm::vec3(radius, 0, 0), color)
    };

    std::vector<uint32_t> indices = {0};
    float angularStep = 2 * glm::pi<float>() / divisions;

    for (int i = 1; i <= divisions; i++) {
        float angle = i * angularStep;
        glm::vec3 vertex = pos + glm::vec3(radius * cos(angle), radius * sin(angle), 0);

        vertices.push_back(VertexFormat(vertex, color));
        indices.push_back(i);
}

    if (!filled)
        circle->SetDrawMode(GL_LINE_LOOP);
    else
        circle->SetDrawMode(GL_TRIANGLE_FAN);

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* m1::Game::createRectangle(const std::string& name, const glm::vec3& center,
                                const std::pair<float, float>& length, const glm::vec3& color, const bool& filled) {
    Mesh* rectangle = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(center + glm::vec3(-length.first / 2, -length.second / 2, 0), color),
        VertexFormat(center + glm::vec3(length.first / 2, -length.second / 2, 0), color),
        VertexFormat(center + glm::vec3(-length.first / 2, length.second / 2, 0), color),
        VertexFormat(center + glm::vec3(length.first / 2, length.second / 2, 0), color)
};

    std::vector<uint32_t> indices;

    if (!filled) {
        indices = {0, 2, 3, 1};
        rectangle->SetDrawMode(GL_LINE_LOOP);
} else
        indices = {0, 2, 3, 0, 3, 1};

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* m1::Game::createRectangle(const std::string& name, const glm::vec3& center, const std::pair<float, float>& length,
                                const glm::vec3& color1, const glm::vec3& color2, const bool& filled) {
    Mesh* rectangle = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(center + glm::vec3(-length.first / 2, -length.second / 2, 0), color1),
        VertexFormat(center + glm::vec3(length.first / 2, -length.second / 2, 0), color1),
        VertexFormat(center + glm::vec3(-length.first / 2, length.second / 2, 0), color1),
        VertexFormat(center + glm::vec3(length.first / 2, -length.second / 2, 0), color2),
        VertexFormat(center + glm::vec3(-length.first / 2, length.second / 2, 0), color2),
        VertexFormat(center + glm::vec3(length.first / 2, length.second / 2, 0), color2)
};

    std::vector<uint32_t> indices;

    if (!filled) {
        indices = {0, 2, 5, 3};
        rectangle->SetDrawMode(GL_LINE_LOOP);
}
    else
        indices = {0, 2, 1, 4, 5, 3};

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* m1::Game::getMesh(const std::string& name) {
    return meshes[name];
}

Shader* m1::Game::getShader(const std::string& name) {
    return shaders[name];
}
