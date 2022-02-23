#include "Game__.h"
#include "DanceFloor.h"
#include "DiscoBall.h"
#include "Dancer.h"
#include "Wall.h"
#include <time.h>

using namespace m1;

Game__::Game__() : ball({0, 4, 0}, {}, {0, -1, 0}, 5, false) {
    srand(time(NULL));

    fov = RADIANS(60.0f);
    zNear = 0.1f;
    zFar = 200.0f;
    cameraSpeed = 5.0f;

    kd = 0.5f;
    ks = 0.5f;
    shininess = 30.0f;
    cutOffAngle = RADIANS(15.0f);
    lightRadius = 1.5f;

    paused = false;
    discoBallRotationTime = 0;

    lightCellIlluminationMode = true;
    reflectorIlluminationMode = true;
    discoBalllIlluminationMode = true;
}

Game__::~Game__() {

}

void Game__::Init() {
    // Load spehere
    {
        Mesh* mesh = new Mesh("sphere");

        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Load box
    {
        Mesh* mesh = new Mesh("box");

        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create filled cone
    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
        std::vector<glm::vec3> basePoints;

        float angle = 0;

        for (int i = 0; i < 100; i++) {
            glm::vec3 point;

            point.x = cos(angle);
            point.y = 0;
            point.z = sin(angle);

            basePoints.push_back(point);
            angle += 2 * glm::pi<float>() / 100;
        }

        vertices.push_back({{0, 1, 0}});

        for (int i = 0; i < 100; i++)
            vertices.push_back({basePoints[i]});

        for (int i = 1; i <= 100; i++) {
            indices.push_back(0);
            indices.push_back(i);
            
            if (i == 100)
                indices.push_back(1);
            else
                indices.push_back(i + 1);
        }

        CreateMesh("filledCone", vertices, indices, GL_TRIANGLES);
    }

    // Create filled cube
    {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-0.5, -0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5, -0.5,  0.5)),
            VertexFormat(glm::vec3(-0.5,  0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5,  0.5,  0.5)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5)),
            VertexFormat(glm::vec3( 0.5, -0.5, -0.5)),
            VertexFormat(glm::vec3(-0.5,  0.5, -0.5)),
            VertexFormat(glm::vec3( 0.5,  0.5, -0.5))
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
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5)),
            VertexFormat(glm::vec3(-0.5, -0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5, -0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5, -0.5, -0.5)),
            VertexFormat(glm::vec3(-0.5,  0.5, -0.5)),
            VertexFormat(glm::vec3(-0.5,  0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5,  0.5,  0.5)),
            VertexFormat(glm::vec3( 0.5,  0.5, -0.5))
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
            VertexFormat(glm::vec3(-0.5, -0.5, 0)),
            VertexFormat(glm::vec3(-0.5,  0.5, 0)),
            VertexFormat(glm::vec3( 0.5, -0.5, 0)),
            VertexFormat(glm::vec3( 0.5,  0.5, 0))
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
            VertexFormat(glm::vec3(-0.5, -0.5, 0)),
            VertexFormat(glm::vec3(-0.5,  0.5, 0)),
            VertexFormat(glm::vec3( 0.5, -0.5, 0)),
            VertexFormat(glm::vec3( 0.5,  0.5, 0))
        };

        std::vector<unsigned int> indices = {
            0, 1, 1, 3, 3, 2, 2, 0
        };

        CreateMesh("unfilledSquare", vertices, indices, GL_LINES);
    }

    {
        Shader* shader = new Shader("homework3Shader");

        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders__", "VertexShader__.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders__", "FragmentShader__.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        mapTextures["randomTexture"] = CreateRandomTexture(16, 16);
    }

    camera = new implemented::Camera(true, false, false);
    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

    danceFloor = new DanceFloor({0, -0.005, 0}, {8, 8}, {1, 0.01, 1}, this);
    discoBall = new DiscoBall({0, 4, 0}, {1.5, 1.5, 1.5}, this);

    generateReflectors();
    generateWalls();
    generateDancers(5);

    camera->TranslateUpwardGlobal(1);
    camera->TranslateForward(-5);
}

Mesh* Game__::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices, const GLenum primitive) {
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

void Game__::FrameStart() {
    glClearColor(0.047, 0.019, 0.278, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);

    lightCells = danceFloor->computeLights();
}

void Game__::Update(float dt) {
    if (paused)
        return;

    discoBallRotationTime += dt;
    danceFloor->update(dt);

    for (const auto& dancer : dancers)
        dancer->update(dt);

    for (auto& reflector : reflectors) {
        reflector.timeSinceLastDirSwitch += dt;

        if (reflector.timeSinceLastDirSwitch > reflector.randomTime / 10) {
            reflector.timeSinceLastDirSwitch = 0;
            reflector.dir1 *= -1;
            reflector.dir2 *= -1;
            reflector.dir3 *= -1;
        }

        reflector.color.x += reflector.dir1 * reflector.randomFactor;
        reflector.color.y += reflector.dir2 * reflector.randomFactor;
        reflector.color.z += reflector.dir3 * reflector.randomFactor;
    }

    for (auto& reflector : reflectors) {
        reflector.timeSinceLastRotationDirSwitch += dt;

        if (reflector.timeSinceLastRotationDirSwitch > 1.5) {
            reflector.timeSinceLastRotationDirSwitch = 0;
            reflector.rotationDir1 *= -1;
            reflector.rotationDir2 *= -1;
        }

        reflector.angleX += reflector.rotationDir1 * reflector.randomAngleX * reflector.rotationAxis.x;
        reflector.angleZ += reflector.rotationDir2 * reflector.randomAngleZ * reflector.rotationAxis.z;

        modelMatrix = glm::mat4(1);

        if (reflector.rotationAxis.x)
            modelMatrix = glm::rotate(modelMatrix, reflector.rotationDir1 * reflector.randomAngleX, {1, 0, 0});

        if (reflector.rotationAxis.z)
            modelMatrix = glm::rotate(modelMatrix, reflector.rotationDir2 * reflector.randomAngleZ, {0, 0, 1});

        reflector.dir = modelMatrix * glm::vec4(reflector.dir, 1);
    }
}

void Game__::FrameEnd() {
    if (lightCellIlluminationMode)
        danceFloor->draw();
    else
        danceFloor->draw(true);

    if (discoBalllIlluminationMode)
        discoBall->draw();

    for (const auto& dancer : dancers)
        dancer->draw();

    for (const auto& wall : walls)
        wall->draw();

    drawFloor();
    drawCeiling();

    if (reflectorIlluminationMode) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDepthMask(GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (const auto& reflector : reflectors) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, reflector.pos);
            modelMatrix = glm::rotate(modelMatrix, reflector.angleX, {1, 0, 0});
            modelMatrix = glm::rotate(modelMatrix, reflector.angleZ, {0, 0, 1});
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -reflector.pos.y, 0));
            modelMatrix = glm::scale(modelMatrix, {tan(cutOffAngle) * reflector.pos.y, reflector.pos.y, tan(cutOffAngle) * reflector.pos.y});
            RenderSimpleMesh(meshes["filledCone"], shaders["homework3Shader"], modelMatrix, {}, true, true, false, false, reflector.color);
        }

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
    }
}

void Game__::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const std::vector<LightSource>& lightCells, const bool simple,
                              const bool transparent, const bool reflector, const bool discoBall, const glm::vec3& color, const Texture2D* texture) {
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

    // Used for illumination mode
    glUniform1i(glGetUniformLocation(shader->program, "lightCellIlluminationMode"), lightCellIlluminationMode);
    glUniform1i(glGetUniformLocation(shader->program, "reflectorIlluminationMode"), reflectorIlluminationMode);
    glUniform1i(glGetUniformLocation(shader->program, "discoBalllIlluminationMode"), discoBalllIlluminationMode);

    // Used for moving / pausing
    glUniform1f(glGetUniformLocation(shader->program, "discoBallRotationTime"), discoBallRotationTime);

    // Used for object's color
    glUniform1f(glGetUniformLocation(shader->program, "kd"), kd);
    glUniform1f(glGetUniformLocation(shader->program, "ks"), ks);
    glUniform1f(glGetUniformLocation(shader->program, "shininess"), shininess);
    glUniform1f(glGetUniformLocation(shader->program, "lightRadius"), lightRadius);
    glUniform3fv(glGetUniformLocation(shader->program, "eyePos"), 1, glm::value_ptr(camera->position));
    glUniform3fv(glGetUniformLocation(shader->program, "objectColor"), 1, glm::value_ptr(color));

    glUniform1i(glGetUniformLocation(shader->program, "simple"), simple);
    glUniform1i(glGetUniformLocation(shader->program, "transparent"), transparent);

    // Used for object's texture
    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
        glUniform1i(glGetUniformLocation(shader->program, "isTextured"), true);
    } else {
        glUniform1i(glGetUniformLocation(shader->program, "isTextured"), false);
        glUniform1i(glGetUniformLocation(shader->program, "fixedTexCoord"), true);
    }

    // Used for cell lights
    if (lightCells.empty())
        glUniform1i(glGetUniformLocation(shader->program, "lightCell"), false);
    else {
        glUniform1i(glGetUniformLocation(shader->program, "lightCell"), true);

        glm::vec3 lightCellPos[9];
        glm::vec3 lightCellColor[9];
        float lightCellIntensity[9];

        for (int i = 0; i < 9; i++) {
            lightCellPos[i] = lightCells[i].pos;
            lightCellColor[i] = lightCells[i].color;
            lightCellIntensity[i] = lightCells[i].intensity;
        }

        glUniform3fv(glGetUniformLocation(shader->program, "lightCellPos"), 9, glm::value_ptr(lightCellPos[0]));
        glUniform3fv(glGetUniformLocation(shader->program, "lightCellColor"), 9, glm::value_ptr(lightCellColor[0]));
        glUniform1fv(glGetUniformLocation(shader->program, "lightCellIntensity"), 9, &lightCellIntensity[0]);
    }

    // Used for reflectors
    glm::vec3 reflectorPos[4];
    glm::vec3 reflectorColor[4];
    glm::vec3 reflectorDir[4];
    float reflectorIntensity[4];

    for (int i = 0; i < 4; i++) {
        reflectorPos[i] = reflectors[i].pos;
        reflectorColor[i] = reflectors[i].color;
        reflectorDir[i] = reflectors[i].dir;
        reflectorIntensity[i] = reflectors[i].intensity;
    }

    glUniform1i(glGetUniformLocation(shader->program, "reflector"), reflector);
    glUniform3fv(glGetUniformLocation(shader->program, "reflectorPos"), 4, glm::value_ptr(reflectorPos[0]));
    glUniform3fv(glGetUniformLocation(shader->program, "reflectorColor"), 4, glm::value_ptr(reflectorColor[0]));
    glUniform3fv(glGetUniformLocation(shader->program, "reflectorDir"), 4, glm::value_ptr(reflectorDir[0]));
    glUniform1fv(glGetUniformLocation(shader->program, "reflectorIntensity"), 4, &reflectorIntensity[0]);
    glUniform1f(glGetUniformLocation(shader->program, "cutOffAngle"), cutOffAngle);

    // Used for disco ball
    glUniform1i(glGetUniformLocation(shader->program, "discoBall"), discoBall);
    glUniform3fv(glGetUniformLocation(shader->program, "discoBallPos"), 1, glm::value_ptr(ball.pos));
    glUniform1f(glGetUniformLocation(shader->program, "discoBallIntensity"), ball.intensity);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

Texture2D* Game__::CreateRandomTexture(unsigned int width, unsigned int height) {
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    for (int i = 0; i < size; i++)
        data[i] = rand() % 255;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();

    texture->Init(textureID, width, height, channels);
    SAFE_FREE_ARRAY(data);
    return texture;
}

void m1::Game__::generateDancers(const int no) {
    glm::vec3 danceFloorPos = danceFloor->getPos();
    glm::ivec2 danceFloorGridSize = danceFloor->getGridSize();
    glm::vec3 danceFloorCellSize = danceFloor->getCellSize();

    glm::vec3 bottomLeftCenter, topRightCenter;

    bottomLeftCenter.x = danceFloorPos.x + (1 - danceFloorGridSize.x) * danceFloorCellSize.x / 2;
    bottomLeftCenter.y = danceFloorPos.y;
    bottomLeftCenter.z = danceFloorPos.y - (1 - danceFloorGridSize.y) * danceFloorCellSize.z / 2;

    topRightCenter.x = danceFloorPos.x - (1 - danceFloorGridSize.x) * danceFloorCellSize.x / 2;
    topRightCenter.y = danceFloorPos.y;
    topRightCenter.z = danceFloorPos.y + (1 - danceFloorGridSize.y) * danceFloorCellSize.z / 2;

    for (int i = 1; i <= no; i++) {
        float x = danceFloorPos.x + (1 - danceFloorGridSize.x) * danceFloorCellSize.x / 2 + (rand() % 10 * (danceFloorGridSize.x - 1) * danceFloorCellSize.x) / 10;
        float z = danceFloorPos.y + (1 - danceFloorGridSize.y) * danceFloorCellSize.z / 2 + (rand() % 10 * (danceFloorGridSize.y - 1) * danceFloorCellSize.z) / 10;

        dancers.push_back(new Dancer({x, 0.5, z}, {0.5, 1, 0.5}, {bottomLeftCenter, topRightCenter}, 1.5 + rand() % 3, this));
    }
}

void m1::Game__::generateWalls() {
    glm::vec3 danceFloorPos = danceFloor->getPos();
    glm::ivec2 danceFloorGridSize = danceFloor->getGridSize();
    glm::vec3 danceFloorCellSize = danceFloor->getCellSize();

    float height = 4 + discoBall->getSize().y / 2 + 0.025;

    for (int i = 0; i < danceFloorGridSize.x / 2; i++) {
        walls.push_back(new Wall(danceFloorPos + glm::vec3(-danceFloorGridSize.x * danceFloorCellSize.x / 2 - 0.005, height / 2 - 0.015, i * danceFloorCellSize.z + danceFloorCellSize.z / 2), {0.01, height, 1}, this));
        walls.push_back(new Wall(danceFloorPos + glm::vec3(danceFloorGridSize.x * danceFloorCellSize.x / 2 + 0.005, height / 2 - 0.015, i * danceFloorCellSize.z + danceFloorCellSize.z / 2), {0.01, height, 1}, this));
    }

    for (int i = 1; i <= danceFloorGridSize.x / 2; i++) {
        walls.push_back(new Wall(danceFloorPos + glm::vec3(-danceFloorGridSize.x * danceFloorCellSize.x / 2 - 0.005, height / 2 - 0.015, -i * danceFloorCellSize.z + danceFloorCellSize.z / 2), {0.01, height, 1}, this));
        walls.push_back(new Wall(danceFloorPos + glm::vec3(danceFloorGridSize.x * danceFloorCellSize.x / 2 + 0.005, height / 2 - 0.015, -i * danceFloorCellSize.z + danceFloorCellSize.z / 2), {0.01, height, 1}, this));
    }

    for (int j = 0; j < danceFloorGridSize.y / 2; j++)
        walls.push_back(new Wall(danceFloorPos + glm::vec3(j * danceFloorCellSize.x + danceFloorCellSize.x / 2, height / 2 - 0.015, -danceFloorGridSize.y * danceFloorCellSize.z / 2 - 0.005), {1, height, 0.01}, this));

     for (int j = 1; j <= danceFloorGridSize.y / 2; j++)
        walls.push_back(new Wall(danceFloorPos + glm::vec3(-j * danceFloorCellSize.x + danceFloorCellSize.x / 2, height / 2 - 0.015, -danceFloorGridSize.y * danceFloorCellSize.z / 2 - 0.005), {1, height, 0.01}, this));
}

void m1::Game__::generateReflectors() {
    glm::vec3 danceFloorPos = danceFloor->getPos();
    glm::ivec2 danceFloorGridSize = danceFloor->getGridSize();
    glm::vec3 danceFloorCellSize = danceFloor->getCellSize();

    glm::vec3 bottomLeftCenter, topRightCenter;

    bottomLeftCenter.x = danceFloorPos.x + (1 - danceFloorGridSize.x) * danceFloorCellSize.x / 2;
    bottomLeftCenter.y = danceFloorPos.y;
    bottomLeftCenter.z = danceFloorPos.y - (1 - danceFloorGridSize.y) * danceFloorCellSize.z / 2;

    topRightCenter.x = danceFloorPos.x - (1 - danceFloorGridSize.x) * danceFloorCellSize.x / 2;
    topRightCenter.y = danceFloorPos.y;
    topRightCenter.z = danceFloorPos.y + (1 - danceFloorGridSize.y) * danceFloorCellSize.z / 2;

    // Reflector 1
    {
        float r = (float)(rand() % 255) / 255;
        float g = (float)(rand() % 255) / 255;
        float b = (float)(rand() % 255) / 255;

        reflectors.push_back({{bottomLeftCenter.x + tan(cutOffAngle) * 3, 4 + discoBall->getSize().y / 2, bottomLeftCenter.z - tan(cutOffAngle) * 3}, {r, g, b}, {0, -1, 0}, 10, true});

        reflectors[0].rotationAxis = {1, 0, 1};
        reflectors[0].timeSinceLastRotationDirSwitch = 0;
        reflectors[0].rotationDir1 = 1;
        reflectors[0].rotationDir2 = 1;
        reflectors[0].angleX = 0;
        reflectors[0].angleZ = 0;
        reflectors[0].randomAngleX = (float)(1 + rand() % 10) / 2000;
        reflectors[0].randomAngleZ = (float)(1 + rand() % 10) / 2000;
    }

    // Reflector 2
    {
        float r = (float)(rand() % 255) / 255;
        float g = (float)(rand() % 255) / 255;
        float b = (float)(rand() % 255) / 255;

        reflectors.push_back({{topRightCenter.x - tan(cutOffAngle) * 3, 4 + discoBall->getSize().y / 2, topRightCenter.z + tan(cutOffAngle) * 3}, {r, g, b}, {0, -1, 0}, 10, true});

        reflectors[1].rotationAxis = {1, 0, 1};
        reflectors[1].timeSinceLastRotationDirSwitch = 0;
        reflectors[1].rotationDir1 = -1;
        reflectors[1].rotationDir2 = -1;
        reflectors[1].angleX = 0;
        reflectors[1].angleZ = 0;
        reflectors[1].randomAngleX = (float)(1 + rand() % 10) / 2000;
        reflectors[1].randomAngleZ = (float)(1 + rand() % 10) / 2000;
    }

    // Reflector 3
    {
        float r = (float)(rand() % 255) / 255;
        float g = (float)(rand() % 255) / 255;
        float b = (float)(rand() % 255) / 255;

        reflectors.push_back({{bottomLeftCenter.x + tan(cutOffAngle) * 3, 4 + discoBall->getSize().y / 2, topRightCenter.z + tan(cutOffAngle) * 3}, {r, g, b}, {0, -1, 0}, 10, true});

        reflectors[2].rotationAxis = {1, 0, 1};
        reflectors[2].timeSinceLastRotationDirSwitch = 0;
        reflectors[2].rotationDir1 = -1;
        reflectors[2].rotationDir2 = 1;
        reflectors[2].angleX = 0;
        reflectors[2].angleZ = 0;
        reflectors[2].randomAngleX = (float)(1 + rand() % 10) / 2000;
        reflectors[2].randomAngleZ = (float)(1 + rand() % 10) / 2000;
    }

    // Reflector 4
    {
        float r = (float)(rand() % 255) / 255;
        float g = (float)(rand() % 255) / 255;
        float b = (float)(rand() % 255) / 255;

        reflectors.push_back({{topRightCenter.x - tan(cutOffAngle) * 3, 4 + discoBall->getSize().y / 2, bottomLeftCenter.z - tan(cutOffAngle) * 3}, {r, g, b}, {0, -1, 0}, 10, true});

        reflectors[3].rotationAxis = {1, 0, 1};
        reflectors[3].timeSinceLastRotationDirSwitch = 0;
        reflectors[3].rotationDir1 = 1;
        reflectors[3].rotationDir2 = -1;
        reflectors[3].angleX = 0;
        reflectors[3].angleZ = 0;
        reflectors[3].randomAngleX = (float)(1 + rand() % 10) / 2000;
        reflectors[3].randomAngleZ = (float)(1 + rand() % 10) / 2000;
    }
}

void m1::Game__::drawFloor() {
    glm::vec3 danceFloorPos = danceFloor->getPos();
    glm::ivec2 danceFloorGridSize = danceFloor->getGridSize();
    glm::vec3 danceFloorCellSize = danceFloor->getCellSize();

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, danceFloorPos - glm::vec3(0, 0.01, 0));
    modelMatrix = glm::scale(modelMatrix, {danceFloorGridSize.x * danceFloorCellSize.x, 0.01, danceFloorGridSize.y * danceFloorCellSize.z});
    RenderSimpleMesh(meshes["box"], shaders["homework3Shader"], modelMatrix, {}, true, false, false, true, {0, 0, 0});
}

void m1::Game__::drawCeiling() {
    glm::vec3 danceFloorPos = danceFloor->getPos();
    glm::ivec2 danceFloorGridSize = danceFloor->getGridSize();
    glm::vec3 danceFloorCellSize = danceFloor->getCellSize();

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, discoBall->getPos() + glm::vec3(0, discoBall->getSize().y / 2, 0));
    modelMatrix = glm::scale(modelMatrix, {danceFloorGridSize.x * danceFloorCellSize.x, 0.01, danceFloorGridSize.y * danceFloorCellSize.z});
    RenderSimpleMesh(meshes["box"], shaders["homework3Shader"], modelMatrix, {}, true, false, false, true, {0, 0, 0});
}

void Game__::OnInputUpdate(float deltaTime, int mods) {
    if (window->KeyHold(GLFW_KEY_UP) || window->KeyHold(GLFW_KEY_W))
        camera->MoveForward(cameraSpeed * deltaTime);
    
    if (window->KeyHold(GLFW_KEY_DOWN) || window->KeyHold(GLFW_KEY_S))
        camera->MoveForward(-cameraSpeed * deltaTime);
    
    if (window->KeyHold(GLFW_KEY_RIGHT) || window->KeyHold(GLFW_KEY_D))
        camera->MoveRight(cameraSpeed * deltaTime);
    
    if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_A))
        camera->MoveRight(-cameraSpeed * deltaTime);
    
    if (window->KeyHold(GLFW_KEY_SPACE))
        camera->TranslateUpwardGlobal(cameraSpeed * deltaTime);
    
    if (window->KeyHold(GLFW_KEY_LEFT_SHIFT))
        camera->TranslateUpwardGlobal(-cameraSpeed * deltaTime);
}

void Game__::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_P)
        if (!paused)
            paused = true;

    if (key == GLFW_KEY_R)
        if (paused)
            paused = false;

    if (key == GLFW_KEY_1)
        lightCellIlluminationMode = !lightCellIlluminationMode;

    if (key == GLFW_KEY_2)
        reflectorIlluminationMode = !reflectorIlluminationMode;

    if (key == GLFW_KEY_3)
        discoBalllIlluminationMode = !discoBalllIlluminationMode;
}

void Game__::OnKeyRelease(int key, int mods) {

}

void Game__::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float sensivityOX = 0.002f;
        float sensivityOY = 0.002f;

        camera->rotateOY(-sensivityOY * deltaX);
        camera->rotateOX(-sensivityOX * deltaY);
    }
}

void Game__::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

}

void Game__::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}

void Game__::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Game__::OnWindowResize(int width, int height) {

}
