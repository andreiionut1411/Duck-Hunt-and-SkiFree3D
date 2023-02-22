#include "lab_m1/Tema3/Tema3.h"
#include <random>

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

#define ANGLE_OF_SLOPE (0.1 * M_PI)
#define SLOPE_SCALE 12
#define PRESENT_TYPE 0
#define ROCK_TYPE 1
#define LIGHT_TYPE 2
#define TREE_TYPE 3
#define BULLET_TYPE 4
#define NORMAL 1
#define POINTS 2
#define CRATE 3
#define SHIELD 4
#define SPEED 5


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "snow_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["snow"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "ski_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["ski"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "present_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["present1"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "present_texture2.jpg").c_str(), GL_REPEAT);
        mapTextures["present2"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab9", "textures", "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["present3"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "present_texture4.jpg").c_str(), GL_REPEAT);
        mapTextures["present4"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "present_texture5.jpg").c_str(), GL_REPEAT);
        mapTextures["present5"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "rock_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["rock"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "metal_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["metal"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "trunk_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["trunk"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "tree_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["tree"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "shield_texture.png").c_str(), GL_REPEAT);
        mapTextures["shield"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "white_texture.png").c_str(), GL_REPEAT);
        mapTextures["white"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "cabin_texture.png").c_str(), GL_REPEAT);
        mapTextures["cabin"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "bullet_texture.png").c_str(), GL_REPEAT);
        mapTextures["bullet"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "jetski_texture.jpg").c_str(), GL_REPEAT);
        mapTextures["jetski"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "droid_texture.png").c_str(), GL_REPEAT);
        mapTextures["droid"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Tema3", "chopper_texture.png").c_str(), GL_REPEAT);
        mapTextures["chopper"] = texture;
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cone");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("square");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* heart = new Mesh("heart");
        heart->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "heart.fbx");
        meshes[heart->GetMeshID()] = heart;
    }

    {
        Mesh* shield = new Mesh("shield");
        shield->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "shield.fbx");
        meshes[shield->GetMeshID()] = shield;
    }

    {
        Mesh* cabin = new Mesh("cabin");
        cabin->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "cabin.fbx");
        meshes[cabin->GetMeshID()] = cabin;
    }

    {
        Mesh* gun = new Mesh("gun1");
        gun->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "gun1.fbx");
        meshes[gun->GetMeshID()] = gun;
    }

    {
        Mesh* gun = new Mesh("gun2");
        gun->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "gun2.fbx");
        meshes[gun->GetMeshID()] = gun;
    }

    {
        Mesh* gun = new Mesh("gun3");
        gun->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "gun3.fbx");
        meshes[gun->GetMeshID()] = gun;
    }

    {
        Mesh* yeti = new Mesh("yeti");
        yeti->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "yeti.fbx");
        meshes[yeti->GetMeshID()] = yeti;
    }

    {
        Mesh* yeti = new Mesh("yeti1");
        yeti->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "yeti1.fbx");
        meshes[yeti->GetMeshID()] = yeti;
    }

    {
        Mesh* yeti = new Mesh("yeti2");
        yeti->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "yeti2.fbx");
        meshes[yeti->GetMeshID()] = yeti;
    }

    {
        Mesh* yeti = new Mesh("yeti3");
        yeti->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "yeti3.fbx");
        meshes[yeti->GetMeshID()] = yeti;
    }

    {
        Mesh* bullet = new Mesh("bullet");
        bullet->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "bullet.fbx");
        meshes[bullet->GetMeshID()] = bullet;
    }

    {
        Mesh* jetski = new Mesh("jetski");
        jetski->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "jetski.fbx");
        meshes[jetski->GetMeshID()] = jetski;
    }

    {
        Mesh* person = new Mesh("person");
        person->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "person.fbx");
        meshes[person->GetMeshID()] = person;
    }

    {
        Mesh* droid = new Mesh("droid");
        droid->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "droid.fbx");
        meshes[droid->GetMeshID()] = droid;
    }

    {
        Mesh* title = new Mesh("title");
        title->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "title.fbx");
        meshes[title->GetMeshID()] = title;
    }

    {
        Mesh* head = new Mesh("yeti_head");
        head->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "yeti_head.fbx");
        meshes[head->GetMeshID()] = head;
    }

    {
        Mesh* head = new Mesh("ski_head");
        head->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "ski_head.fbx");
        meshes[head->GetMeshID()] = head;
    }

    {
        Mesh* head = new Mesh("jet_head");
        head->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "jet_head.fbx");
        meshes[head->GetMeshID()] = head;
    }

    {
        Mesh* chopper = new Mesh("chopper");
        chopper->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema3"), "chopper.fbx");
        meshes[chopper->GetMeshID()] = chopper;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    initializeGame();
    SetCamera();
    text = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    text->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", 128);
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::initializeGame() {
    objects.clear();
    bullets.clear();
    initializePlayer();
    generateInitialLayout();

    distance = 0.0f;
    totalDistance = 0.0f;
    score = 0;
    yetiAngle = 0;
    yetiRight = true;
    yetiOnField = false;
    yetiDead = false;
    distanceYetiToPlayer = 5;
    timeBetweenAnimation = 0;
    enemySkiOnField = false;
    enemySkiDead = false;
    enemyJetOnField = false;
    enemyJetDead = false;
    distanceEnemyToPlayer = -5;
    enemyUp = false;
    timeBetweenShots = 0;
    consecShots = false;
    distanceToFirstEnemyDeath = 0;
    noMove = false;
    snowPlanePosition = glm::vec3(-1); // This means that we don't render the second snow plane
    distancefromLastDeath = 0;
    maxPlayerSpeed = 1.5;
}

void Tema3::SetCamera() {
    camera = GetSceneCamera();
    camera->SetPerspective(60, window->props.aspectRatio, 0.01f, 200);
    glm::vec3 cameraPosition;

    if (snowPlanePosition.z == -1 || snowPlanePosition.z > playerPosition.z) {
        cameraPosition = glm::vec3(playerPosition.x, playerPosition.y + 2.45, playerPosition.z + 2.2);
    }
    else {
        cameraPosition = glm::vec3(playerPosition.x, playerPosition.y + 2.45, snowPlanePosition.z + 2.2);
    }

    // Because the whole world is rotated, we also rotate the camera's position
    glm::mat4 modelMatrix = glm::mat4(1);
    if (snowPlanePosition.z != -1 && snowPlanePosition.z <= playerPosition.z) {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2, playerPosition.z - snowPlanePosition.z));
    }

    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    cameraPosition = glm::vec3(modelMatrix * glm::vec4(cameraPosition, 1));

    camera->m_transform->SetWorldPosition(cameraPosition);
    camera->m_transform->SetWorldRotation(glm::vec3(-30, 0, 0));
    camera->Update();
}

// For the HUD, we will use a new camera and a new viewport to render over the actual game
void Tema3::SetCameraHUD() {
    camera->m_transform->SetWorldPosition(glm::vec3(0, 5, 0));
    camera->m_transform->SetWorldRotation(glm::vec3(-90, 0, 0));
    camera->Update();
}

// The function populates the slope randomly in the begining of the game.
void Tema3::generateInitialLayout() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_position_x(-50, 50);
    std::uniform_int_distribution<> distr_position_z(0, 40);
    std::uniform_int_distribution<> distr_type(0, 3);

    
    for (float i = 0.5; i < 0.8 * SLOPE_SCALE; i += distanceBetweenObjects) {
        float x = distr_position_x(gen) / 100.0;
        float z = distr_position_z(gen) / 100.0;
        int type = distr_type(gen);

        objects.push_back(ObjectOnSlope(glm::vec3(playerPosition.x + x * SLOPE_SCALE, 0,
            playerPosition.z + i + z), type));
    }

    updateLights();
}

void Tema3::initializePlayer() {
    playerPosition = glm::vec3(0.0f, 0.12f, 0.0f);
    invulnerableTime = maxInvulnerableTime;
    speedUpTime = 0;
    playerLives = maxPlayerLives;
    playerHasShield = false;
    gunPartsCollected = 0;

    // If the type is -1, it means, that the bullet was not yet shot
    playerBullet = ObjectOnSlope(glm::vec3(0), -1);
}

// As the player goes down the slope, new items spawn. This function does that.
void Tema3::addProceduralObjects() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_position_x(-50, 50);
    std::uniform_int_distribution<> distr_position_z(0, (int)(distanceBetweenObjects * 100));
    std::uniform_int_distribution<> distr_type(0, 3);

    float x = distr_position_x(gen) / 100.0;
    float z = distr_position_z(gen) / 100.0;
    int type = distr_type(gen);

    // The object is added in front of the skier, at 0.2 of the slope to the slope edge
    objects.push_back(ObjectOnSlope(glm::vec3(playerPosition.x + x * SLOPE_SCALE,
        0, playerPosition.z + 0.8 * SLOPE_SCALE + z), type));

    // The distance until the next spawn is reset.
    distance = 0;
    updateLights();
}

// The function verifies if any of the objects that were in the scene left
// the slope, in which case we erase them. When we erase them, we need to also
// update the lights because one of the sources of light might have despawned.
void Tema3::verifyObjectsInScene() {
    int i = 0;
    bool despawn = false;

    while (i < objects.size()) {
        if (objects[i].getPosition().x < playerPosition.x - SLOPE_SCALE ||
            objects[i].getPosition().x > playerPosition.x + SLOPE_SCALE ||
            objects[i].getPosition().z < playerPosition.z - SLOPE_SCALE ||
            objects[i].getPosition().z > playerPosition.z + SLOPE_SCALE) {

            objects.erase(objects.begin() + i);
            i--;
            despawn = true;
        }
        i++;
    }

    if (despawn) updateLights();
}

void Tema3::verifyBulletCollision() {
    float playerLeftMost = playerPosition.x - playerBoundingBox.x;
    float playerRightMost = playerPosition.x + playerBoundingBox.x;
    float playerUpMost = playerPosition.z + playerBoundingBox.z;
    float playerDownMost = playerPosition.z - playerBoundingBox.z;

    for (int i = 0; i < bullets.size(); i++) {
        float objLeftMost = bullets[i].getPosition().x - bullets[i].getBoundingBox().x;
        float objRightMost = bullets[i].getPosition().x + bullets[i].getBoundingBox().x;
        float objUpMost = bullets[i].getPosition().z + bullets[i].getBoundingBox().z;
        float objDownMost = bullets[i].getPosition().z - bullets[i].getBoundingBox().z;
        bool intersectionOverX = false;
        bool intersectionOverZ = false;

        if ((playerLeftMost < objLeftMost && playerRightMost >= objLeftMost) ||
            (playerLeftMost >= objLeftMost && playerLeftMost < objRightMost)) {
            intersectionOverX = true;
        }

        if ((playerDownMost < objDownMost && objDownMost <= playerUpMost) ||
            (playerDownMost >= objDownMost && playerDownMost < objUpMost)) {
            intersectionOverZ = true;
        }

        if (intersectionOverX && intersectionOverZ) {
            if (invulnerableTime >= maxInvulnerableTime) {
                invulnerableTime = 0;
                bullets.erase(bullets.begin() + i);
                i--;

                if (playerHasShield) playerHasShield = false;
                else playerLives--;
            }

            break;
        }
    }
}

void Tema3::verifyCollision() {
    bool despawn = false;
    float playerLeftMost = playerPosition.x - playerBoundingBox.x;
    float playerRightMost = playerPosition.x + playerBoundingBox.x;
    float playerUpMost = playerPosition.z + playerBoundingBox.z;
    float playerDownMost = playerPosition.z - playerBoundingBox.z;

    for (int i = 0; i < objects.size(); i++) {
        float objLeftMost = objects[i].getPosition().x - objects[i].getBoundingBox().x;
        float objRightMost = objects[i].getPosition().x + objects[i].getBoundingBox().x;
        float objUpMost = objects[i].getPosition().z + objects[i].getBoundingBox().z;
        float objDownMost = objects[i].getPosition().z - objects[i].getBoundingBox().z;
        bool intersectionOverX = false;
        bool intersectionOverZ = false;

        if ((playerLeftMost < objLeftMost && playerRightMost >= objLeftMost) ||
            (playerLeftMost >= objLeftMost && playerLeftMost < objRightMost)) {
            intersectionOverX = true;
        }

        if ((playerDownMost < objDownMost && objDownMost <= playerUpMost) ||
            (playerDownMost >= objDownMost && playerDownMost < objUpMost)) {
            intersectionOverZ = true;
        }

        if (intersectionOverX && intersectionOverZ) {

            // If we get into a present, it dissapears and the player gets the points
            if (objects[i].getType() == PRESENT_TYPE) {
                if (objects[i].getTypeOfPresent() == NORMAL) {
                    score += 10;
                }
                else if (objects[i].getTypeOfPresent() == POINTS) {
                    score += 50;
                }
                else if (objects[i].getTypeOfPresent() == SHIELD) {
                    playerHasShield = true;
                }
                else if (objects[i].getTypeOfPresent() == CRATE) {
                    if (gunPartsCollected < 3) gunPartsCollected++;
                }
                else if (objects[i].getTypeOfPresent() == SPEED) {
                    if (speedUpTime <= 0) maxPlayerSpeed = maxPlayerSpeed * 2;
                    speedUpTime = maxSpeedUpTime;
                }

                objects.erase(objects.begin() + i);
                i--;
                despawn = true;
            }
            else {
                // If the player is not invulnerable, then we reset the timer
                if (invulnerableTime >= maxInvulnerableTime) {
                    invulnerableTime = 0;
                    objects.erase(objects.begin() + i);
                    i--;
                    despawn = true;

                    if (playerHasShield) playerHasShield = false;
                    else playerLives--;
                }
            }

            // We can't hit 2 objects at the same time
            break;
        }
    }

    if (despawn) updateLights();

    verifyBulletCollision();
}

void Tema3::RenderSnow() {
    glm::mat4 modelMatrix = glm::mat4(1);
    bool snowMoves = true;

    // We translate the slope with the player, but we don't move it up. The slope will be at height 0.
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));

    if (snowPlanePosition.z != -1) {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(snowPlanePosition.x, 0.0f, snowPlanePosition.z - 3));
        snowMoves = false;
    }
    else {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(playerPosition.x, 0.0f, playerPosition.z));
    }

    modelMatrix = glm::rotate(modelMatrix, (float)M_PI_2, glm::vec3(1, 0, 0)); // The square needs to be flat first of all
    modelMatrix = glm::scale(modelMatrix, glm::vec3(SLOPE_SCALE));

    // Only the slope will be "moving" inside the texture
    RenderSimpleMesh(meshes["square"], shaders["TemaShader"], modelMatrix, snowMoves, mapTextures["snow"]);

    if (snowPlanePosition.x != -1) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, snowPlanePosition);
        modelMatrix = glm::rotate(modelMatrix, (float)M_PI_2, glm::vec3(1, 0, 0)); // The square needs to be flat first of all
        modelMatrix = glm::scale(modelMatrix, glm::vec3(SLOPE_SCALE));
        modelMatrix = glm::rotate(modelMatrix, (float)-ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
        RenderSimpleMesh(meshes["square"], shaders["TemaShader"], modelMatrix, false, mapTextures["snow"]);
    }
}

void Tema3::RenderObjects() {
    for (m1::ObjectOnSlope obj : objects) {
        RenderObject(obj.getPosition(), obj);
    }
}

void Tema3::RenderObject(glm::vec3 position, m1::ObjectOnSlope object) {
    int type = object.getType();

    if (type == PRESENT_TYPE) {
        RenderPresent(position, object.getTypeOfPresent());
    }
    else if (type == ROCK_TYPE) {
        RenderRock(position);
    }
    else if (type == LIGHT_TYPE) {
        RenderLight(position);
    }
    else if (type == TREE_TYPE) {
        RenderTree(position);
    }
}

void Tema3::RenderPresent(glm::vec3 position, int type) {
    string textureName = "present" + to_string(type);

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0)); // We elevate a little bit the present box
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));
    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], modelMatrix, false, mapTextures[textureName]);
}

void Tema3::RenderRock(glm::vec3 position) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.04f, 0.0f)); // We elevate a little the rock
    
    glm::mat4 matrix = glm::translate(modelMatrix, glm::vec3(-0.1, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(0.15));
    RenderSimpleMesh(meshes["sphere"], shaders["TemaShader"], matrix, false, mapTextures["rock"]);

    matrix = glm::scale(modelMatrix, glm::vec3(0.18));
    RenderSimpleMesh(meshes["sphere"], shaders["TemaShader"], matrix, false, mapTextures["rock"]);

    matrix = glm::translate(modelMatrix, glm::vec3(0.09, -0.025, 0));
    matrix = glm::scale(matrix, glm::vec3(0.13));
    RenderSimpleMesh(meshes["sphere"], shaders["TemaShader"], matrix, false, mapTextures["rock"]);
}

void Tema3::RenderLight(glm::vec3 position) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, position);

    // We render the pole of the light
    glm::mat4 matrix = glm::translate(modelMatrix, glm::vec3(0, 0.6f, 0));
    matrix = glm::scale(matrix, glm::vec3(0.1, 1.2, 0.05));
    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], matrix, false, mapTextures["metal"]);

    // We render the top of the light
    matrix = glm::translate(modelMatrix, glm::vec3(0, 1.2f, 0));
    matrix = glm::scale(matrix, glm::vec3(0.8, 0.1, 0.07));
    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], matrix, false, mapTextures["metal"]);
}

void Tema3::RenderTree(glm::vec3 position) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, position);

    // We render the tree trunk
    glm::mat4 matrix = glm::translate(modelMatrix, glm::vec3(0, 0.2f, 0));
    matrix = glm::scale(matrix, glm::vec3(0.06, 0.4, 0.06));
    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], matrix, false, mapTextures["trunk"]);

    // We render the first layer of leaves
    matrix = glm::translate(modelMatrix, glm::vec3(0, 0.5f, 0));
    matrix = glm::scale(matrix, glm::vec3(0.3, 0.2, 0.3));
    RenderSimpleMesh(meshes["cone"], shaders["TemaShader"], matrix, false, mapTextures["tree"]);

    // We render the second layer of leaves
    matrix = glm::translate(modelMatrix, glm::vec3(0, 0.7f, 0));
    matrix = glm::scale(matrix, glm::vec3(0.15, 0.2, 0.15));
    RenderSimpleMesh(meshes["cone"], shaders["TemaShader"], matrix, false, mapTextures["tree"]);
}

void Tema3::RenderSkier(glm::vec3 position, bool isPlayer) {
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 matrix;

    if (snowPlanePosition.z != -1 && snowPlanePosition.z <= playerPosition.z) {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2, playerPosition.z - snowPlanePosition.z));
    }

    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));

    if (snowPlanePosition.z == -1 || snowPlanePosition.z > playerPosition.z) {
        modelMatrix = glm::translate(modelMatrix, position);
    }
    else {
        modelMatrix = glm::translate(modelMatrix, snowPlanePosition);
    }
    modelMatrix = glm::rotate(modelMatrix, playerAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, (float)M_PI_2, glm::vec3(0, 1, 0));
    matrix = modelMatrix;

    if (snowPlanePosition.x != -1 && playerPosition.z >= snowPlanePosition.z) {
        matrix = glm::rotate(modelMatrix, (float)-ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    }
    
    matrix = glm::translate(matrix, glm::vec3(0, -0.1, 0));
    matrix = glm::rotate(matrix, (float)-M_PI_2, glm::vec3(1, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(0.05, 0.08, 0.08));

    RenderSimpleMesh(meshes["person"], shaders["TemaShader"], matrix, false, mapTextures["white"]);

    matrix = glm::translate(modelMatrix, glm::vec3(-0.012 - 0.025, -0.112, 0.05));
    if (snowPlanePosition.x != -1 && playerPosition.z >= snowPlanePosition.z) {
        matrix = glm::rotate(matrix, (float)-ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    }
    matrix = glm::scale(matrix, glm::vec3(0.025, 0.02, 0.4));

    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], matrix, false, mapTextures["ski"]);

    matrix = glm::translate(modelMatrix, glm::vec3(0.012 + 0.025, -0.112, 0.05));
    if (snowPlanePosition.x != -1 && playerPosition.z >= snowPlanePosition.z) {
        matrix = glm::rotate(matrix, (float)-ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    }
    matrix = glm::scale(matrix, glm::vec3(0.025, 0.02, 0.4));

    RenderSimpleMesh(meshes["box"], shaders["TemaShader"], matrix, false, mapTextures["ski"]);

    if (playerHasShield && isPlayer && snowPlanePosition.z == -1) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(playerPosition.x,
            playerPosition.y + 0.15, playerPosition.z + 0.5));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.15, -0.5));
        modelMatrix = glm::rotate(modelMatrix, playerAngle + (float)M_PI_2, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.15, 0.5));
        modelMatrix = glm::rotate(modelMatrix, (float)M_PI_2, glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));
        RenderSimpleMesh(meshes["shield"], shaders["TemaShader"], modelMatrix, false, mapTextures["shield"]);
    }
}

void Tema3::updatePointLights() {
    for (int i = 0; i < objects.size(); i++) {
        pointLightPositions[i] = objects[i].getLightPosition();
        pointLightColors[i] = objects[i].getLightColor();
    }
}

void Tema3::updateSpotLights() {
    numberOfLightPoles = 0;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].getType() == LIGHT_TYPE) {
            spotLight[2 * numberOfLightPoles] = objects[i].getLightPosition();
            spotLight[2 * numberOfLightPoles + 1] = objects[i].getSecondLightPosition();
            numberOfLightPoles++;
        }
    }
}

// This function will be used in the begining and every time an object spawns
// on the slope or despawns. The function updates the position of all the objects,
// so that we have an array of positions for the shader.
void Tema3::updateLights() {
    updatePointLights();
    updateSpotLights();
}

void Tema3::RenderLives() {
    for (int i = 0; i < playerLives; i++) {
        glm::mat4 matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(4.5 - 0.5 * i, 0, -2.5));
        matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, (float)M_PI, glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, glm::vec3(0.4));
        RenderMesh(meshes["heart"], shaders["Simple"], matrix);
    }
}

void Tema3::RenderTitle() {
    glm::mat4 matrix = glm::mat4(1);
    matrix = glm::translate(matrix, glm::vec3(3, 0, -2));
    matrix = glm::rotate(matrix, (float)-M_PI_2, glm::vec3(1, 0, 0));
    RenderMesh(meshes["title"], shaders["Simple"], matrix);
}

void Tema3::RenderSpeedBar() {
    glm::mat4 matrix = glm::mat4(1);
    matrix = glm::translate(matrix, glm::vec3(3.2 + speedUpTime / (maxSpeedUpTime), 0, -0.9));
    matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(speedUpTime / maxSpeedUpTime, 0.2, 0));
    RenderSimpleMesh(meshes["square"], shaders["TemaShader"], matrix, false, mapTextures["white"]);
}

void Tema3::RenderGunParts() {
    string meshName;

    if (gunPartsCollected == 1) meshName = "gun1";
    else if (gunPartsCollected == 2) meshName = "gun2";
    else if (gunPartsCollected == 3) meshName = "gun3";
    else return;

    glm::mat4 matrix = glm::mat4(1);
    matrix = glm::translate(matrix, glm::vec3(4.15, 0, -2));
    matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(0.8, -0.8, 1));
    RenderMesh(meshes[meshName], shaders["Simple"], matrix);
}

void Tema3::RenderBullets() {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    glm::mat4 matrix;

    for (int i = 0; i < bullets.size(); i++) {
        matrix = glm::translate(modelMatrix, glm::vec3(bullets[i].getPosition().x, -0.2, bullets[i].getPosition().z));
        matrix = glm::scale(matrix, glm::vec3(6.5, 6, 6));
        matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["bullet"], shaders["TemaShader"], matrix, false, mapTextures["bullet"]);
    }

    if (playerBullet.getType() != -1) {
        float angle = acos(glm::dot(glm::vec3(1, 0, 0), glm::normalize(playerBulletDirection)));

        if (playerBulletDirection.z > 0) {
            angle = 2 * M_PI - angle;
        }

        matrix = glm::translate(modelMatrix, glm::vec3(playerBullet.getPosition().x, -0.2, playerBullet.getPosition().z));
        matrix = glm::rotate(matrix, angle - (float)M_PI_2, glm::vec3(0, 1, 0));
        matrix = glm::scale(matrix, glm::vec3(6.5, 6, 6));
        RenderSimpleMesh(meshes["bullet"], shaders["TemaShader"], matrix, false, mapTextures["bullet"]);
    }
}

void Tema3::RenderHeads() {
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 matrix;

    if (yetiDead) {
        matrix = glm::translate(modelMatrix, glm::vec3(3.5, 0, -1.4));
        matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(0.5, -0.5, 1));
        RenderMesh(meshes["yeti_head"], shaders["Simple"], matrix);
    }

    if (enemySkiDead) {
        matrix = glm::translate(modelMatrix, glm::vec3(4, 0, -1.4));
        matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(0.5, -0.5, 1));
        RenderMesh(meshes["ski_head"], shaders["Simple"], matrix);
    }

    if (enemyJetDead) {
        matrix = glm::translate(modelMatrix, glm::vec3(4.6, 0, -1.4));
        matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(0.5, -0.5, 1));
        RenderMesh(meshes["jet_head"], shaders["Simple"], matrix);
    }
}

void Tema3::RenderHUD() {
    if (gameIsOn) {
        text->RenderText("Score: " + to_string(score), 0.05 * window->GetResolution().x, 0.07 * window->GetResolution().y, 0.25);
        text->RenderText("Distance: " + to_string((int)totalDistance) + "m", 0.05 * window->GetResolution().x, 0.1 * window->GetResolution().y, 0.25);

        if (gunPartsCollected == 3) {
            text->RenderText("PRESS SPACE TO SHOOT", 0.33 * window->GetResolution().x, 0.9 * window->GetResolution().y, 0.3);
        }

        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);
        SetCameraHUD();

        RenderLives();
        RenderGunParts();
        RenderHeads();
        RenderSpeedBar();
    }
    else if (startMenu) {
        text->RenderText("START GAME", 0.32 * window->GetResolution().x, 14 * window->GetResolution().y / 30, 0.6);
        text->RenderText("EXIT", 0.42 * window->GetResolution().x, 18 * window->GetResolution().y / 30, 0.6);

        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);
        SetCameraHUD();
        RenderTitle();
    }
    else if (gameOver) {
        text->RenderText("GAME OVER", 0.34 * window->GetResolution().x, 0.2 * window->GetResolution().y, 0.6);
        text->RenderText("Score: " + to_string(score), 0.38 * window->GetResolution().x, 0.4 * window->GetResolution().y, 0.5);
        text->RenderText("Distance: " + to_string((int)totalDistance) + "m", 0.3 * window->GetResolution().x, 0.5 * window->GetResolution().y, 0.5);

        text->RenderText("TRY AGAIN", 0.415 * window->GetResolution().x, 24 * window->GetResolution().y / 30, 0.3);
        text->RenderText("MENU", 23 * window->GetResolution().x / 50, 26 * window->GetResolution().y / 30, 0.3);
        text->RenderText("EXIT", 23 * window->GetResolution().x / 50, 28 * window->GetResolution().y / 30, 0.3);
    }
    else if (gameWon) {
        text->RenderText("YOU WIN", 0.37 * window->GetResolution().x, 0.2 * window->GetResolution().y, 0.6);
        text->RenderText("Score: " + to_string(score), 0.38 * window->GetResolution().x, 0.4 * window->GetResolution().y, 0.5);
        text->RenderText("Distance: " + to_string((int)totalDistance) + "m", 0.3 * window->GetResolution().x, 0.5 * window->GetResolution().y, 0.5);

        text->RenderText("TRY AGAIN", 0.415 * window->GetResolution().x, 24 * window->GetResolution().y / 30, 0.3);
        text->RenderText("MENU", 23 * window->GetResolution().x / 50, 26 * window->GetResolution().y / 30, 0.3);
        text->RenderText("EXIT", 23 * window->GetResolution().x / 50, 28 * window->GetResolution().y / 30, 0.3);
    }
}

void Tema3::RenderCabin() {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, -1));
    modelMatrix = glm::rotate(modelMatrix, (float)-M_PI_2, glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0015, 0.0015, 0.002));
    RenderSimpleMesh(meshes["cabin"], shaders["TemaShader"], modelMatrix, false, mapTextures["cabin"]);
}

void Tema3::RenderYeti() {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(playerPosition.x, 0.5, playerPosition.z - distanceYetiToPlayer));

    if (distanceYetiToPlayer > 0) {
        modelMatrix = glm::rotate(modelMatrix, yetiAngle, glm::vec3(0, 0, 1));
        RenderMesh(meshes["yeti"], shaders["Simple"], modelMatrix);
    }
    else if (timeBetweenAnimation < maxTimeBetweenAnimation)
        RenderMesh(meshes["yeti1"], shaders["Simple"], modelMatrix);
    else if (timeBetweenAnimation < 2 * maxTimeBetweenAnimation)
        RenderMesh(meshes["yeti2"], shaders["Simple"], modelMatrix);
    else if (timeBetweenAnimation < 8 * maxTimeBetweenAnimation)
        RenderMesh(meshes["yeti3"], shaders["Simple"], modelMatrix);
    else
        playerLives = 0;
}

void Tema3::RenderEnemy1() {
    RenderSkier(enemySkiPosition, false);
}

void Tema3::RenderEnemy2() {
    glm::mat4 matrix = glm::mat4(1);
    matrix = glm::rotate(matrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    matrix = glm::translate(matrix, glm::vec3(enemyJetPosition.x, 0.25, enemyJetPosition.z));
    matrix = glm::rotate(matrix, playerAngle, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, (float)-M_PI_2, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, (float)-M_PI_2, glm::vec3(1, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(0.006));
    RenderSimpleMesh(meshes["jetski"], shaders["TemaShader"], matrix, false, mapTextures["jetski"]);

    matrix = glm::mat4(1);
    matrix = glm::rotate(matrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    matrix = glm::translate(matrix, glm::vec3(enemyJetPosition.x, 0.18, enemyJetPosition.z));
    matrix = glm::rotate(matrix, playerAngle, glm::vec3(0, 1, 0));
    matrix = glm::translate(matrix, glm::vec3(-0.15, 0, 0));
    matrix = glm::scale(matrix, glm::vec3(0.015));
    matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, (float)M_PI, glm::vec3(0, 1, 0));
    RenderSimpleMesh(meshes["droid"], shaders["TemaShader"], matrix, false, mapTextures["droid"]);
}

void Tema3::RenderChopper() {
    glm::mat4 matrix = glm::mat4(1);
    matrix = glm::translate(matrix, glm::vec3(1.5, 0.3, 4));
    matrix = glm::rotate(matrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    matrix = glm::translate(matrix, glm::vec3(snowPlanePosition.x, 0, snowPlanePosition.z));
    matrix = glm::rotate(matrix, (float)-ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, (float)M_PI_2, glm::vec3(0, 1, 0));
    matrix = glm::scale(matrix, glm::vec3(0.2));
    RenderSimpleMesh(meshes["chopper"], shaders["TemaShader"], matrix, false, mapTextures["chopper"]);
}

void Tema3::RenderScene() {
    SetCamera();
    if (gameIsOn) {
        // We let the player know that it is invulnerable
        if (((int)(invulnerableTime * 4) % 2 == 1 || invulnerableTime >= maxInvulnerableTime) &&
            distanceYetiToPlayer > 0)
            RenderSkier(playerPosition, true);

        // If the cabin is far away ther is no reason to keep rendering it
        if (yetiOnField) RenderYeti();
        if (enemySkiOnField) RenderEnemy1();
        if (enemyJetOnField) RenderEnemy2();

        RenderBullets();
    }
    
    if (snowPlanePosition.z != -1) {
        RenderChopper();
        RenderSkier(playerPosition, true);
    }

    if (playerPosition.z < 5) RenderCabin();
    RenderObjects();
    RenderSnow();

    RenderHUD();
}

void Tema3::movePlayer(float deltaTimeSeconds) {
    verifyCollision();

    // The player stays in place if he is perpendicular on the slope
    if (playerAngle != 0 && playerAngle != (float)M_PI) {

        // We make so that the player moves faster if it going striaght down, than
        // if it is going sideways.
        if (snowPlanePosition.z != -1 && playerPosition.z >= snowPlanePosition.z) {
            if (playerSpeed > 0) {
                playerSpeed -= deltaTimeSeconds * 0.5;
            }
            else {
                playerSpeed = 0;
            }
        }
        else {
            playerSpeed = -maxPlayerSpeed * sin(playerAngle) * 1.2; // sin is negative
        }

        playerPosition.x += deltaTimeSeconds * cos(playerAngle) * playerSpeed;
        playerPosition.z -= deltaTimeSeconds * sin(playerAngle) * playerSpeed; // The angle is mirrored
        distance += deltaTimeSeconds * playerSpeed;
        totalDistance += deltaTimeSeconds * playerSpeed * 12;
    }
}

void Tema3::moveYeti(float deltaTimeSeconds) {
    if (yetiRight) {
        yetiAngle += 2.5 * deltaTimeSeconds;

        if (yetiAngle > 0.3) yetiRight = false;
    }
    else {
        yetiAngle -= 2.5 * deltaTimeSeconds;

        if (yetiAngle < -0.3) yetiRight = true;
    }
}

void Tema3::moveEnemy1(float deltaTimeSeconds) {
    if (!enemyUp) {
        distanceEnemyToPlayer += deltaTimeSeconds;
        if (distanceEnemyToPlayer > maxEnemyDistance) enemyUp = true;
    }
    else {
        distanceEnemyToPlayer -= deltaTimeSeconds;
        if (distanceEnemyToPlayer < 0) enemyUp = false;
    }

    enemySkiPosition = playerPosition;
    enemySkiPosition.x += 2.5;
    enemySkiPosition.z += distanceEnemyToPlayer;

    timeBetweenShots += deltaTimeSeconds;

    if (timeBetweenShots >= maxTimeBetweenShots) {
        timeBetweenShots = 0;
        bullets.push_back(ObjectOnSlope(enemySkiPosition, BULLET_TYPE));
    }

    if (playerBullet.getPosition().x >= enemySkiPosition.x && playerBullet.getType() != -1) {
        enemySkiDead = true;
        playerBullet = ObjectOnSlope(glm::vec3(0, 0, 0), -1); // We delete the bullet
        distanceToFirstEnemyDeath = totalDistance;
    }
}

void Tema3::moveEnemy2(float deltaTimeSeconds) {

    if (!enemyUp) {
        distanceEnemyToPlayer += deltaTimeSeconds;

        if (distanceEnemyToPlayer >= maxEnemyDistance) enemyUp = true;
    }
    else {
        distanceEnemyToPlayer -= deltaTimeSeconds;

        if (distanceEnemyToPlayer <= 0) enemyUp = false;
    }

    enemyJetPosition = playerPosition;
    enemyJetPosition.x += 2.5;
    enemyJetPosition.z += distanceEnemyToPlayer;

    timeBetweenShots += deltaTimeSeconds;

    if (consecShots == false) {
        if (timeBetweenShots >= maxTimeBetweenShots) {
            consecShots = true;
            timeBetweenShots = 0;
            bullets.push_back(ObjectOnSlope(enemyJetPosition, BULLET_TYPE));
        }
    }
    else {
        // The second enemy will shoot in rounds of 2
        if (timeBetweenShots >= maxTimeBetweenConsecShots) {
            consecShots = false;
            timeBetweenShots = 0;
            bullets.push_back(ObjectOnSlope(enemyJetPosition, BULLET_TYPE));
        }
    }

    if (playerBullet.getPosition().x >= enemyJetPosition.x && playerBullet.getType() != -1) {
        enemyJetDead = true;
        playerBullet = ObjectOnSlope(glm::vec3(0, 0, 0), -1); // We delete the bullet
        distancefromLastDeath = totalDistance;
    }
}

void Tema3::movePlayerBullet(float deltaTimeSeconds) {
    if (playerBullet.getType() != -1) {
        glm::vec3 newPosition = playerBullet.getPosition();

        if (enemySkiOnField) playerBulletDirection = glm::normalize(enemySkiPosition - playerBullet.getPosition());
        else if (enemyJetOnField) playerBulletDirection = glm::normalize(enemyJetPosition - playerBullet.getPosition());

        newPosition = newPosition + deltaTimeSeconds * playerBulletSpeed * playerBulletDirection;
        playerBullet.setPosition(newPosition);

        // If the bullet is too far away, we despawn it
        if (glm::distance(playerPosition, newPosition) >= 10) playerBullet = ObjectOnSlope(glm::vec3(0), -1);
    }
}

void Tema3::moveBullets(float deltaTimeSeconds) {
    for (int i = 0; i < bullets.size(); i++) {
        glm::vec3 newPosition = bullets[i].getPosition();
        newPosition.x -= bulletSpeed * deltaTimeSeconds;

        // If the bullet has long passed the player, then we despawn it so we have
        // less objects to calculate later
        if (glm::distance(newPosition, playerPosition) > 10) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
        else {
            bullets[i].setPosition(newPosition);
        }
    }
}

void Tema3::verifyCollisionBulletYeti() {
    if (playerBullet.getType() != -1 && yetiOnField) {
        // If the bullet was show before and it has passed the yeti, then we don't care
        if (playerBullet.getPosition().z <= playerPosition.z - distanceYetiToPlayer &&
            playerBullet.getPosition().z + 1 >= playerPosition.z - distanceYetiToPlayer) {
            playerBullet = ObjectOnSlope(glm::vec3(0), -1);
            yetiDead = true;
        }
    }
}

void Tema3::Update(float deltaTimeSeconds)
{
    if (deltaTimeSeconds < 1 && gameIsOn) {
        verifyObjectsInScene();
        moveBullets(deltaTimeSeconds);

        if (distanceYetiToPlayer > 0) {
            movePlayer(deltaTimeSeconds);
            moveYeti(deltaTimeSeconds);
            movePlayerBullet(deltaTimeSeconds);
            verifyCollisionBulletYeti();
        }

        if (distance > distanceBetweenObjects && !enemyJetDead) {
            addProceduralObjects();
        }

        if (!gameIsOn) window->Close();

        if (invulnerableTime < maxInvulnerableTime)
            invulnerableTime += deltaTimeSeconds;

        if (speedUpTime > 0) {
            speedUpTime -= deltaTimeSeconds;

            if (speedUpTime <= 0) {
                speedUpTime = 0;
                maxPlayerSpeed = maxPlayerSpeed / 2;
            }
        }

        // We spawn a yeti after 2000 meters
        if (totalDistance > 2000) {
            if (!yetiDead)
                yetiOnField = true;
            else 
                yetiOnField = false;
        }

        if (totalDistance > 3000) {
            if (!enemySkiDead)
                enemySkiOnField = true;
            else
                enemySkiOnField = false;
        }

        if (yetiOnField){
            if (distanceYetiToPlayer > 0) distanceYetiToPlayer -= yetiSpeed * deltaTimeSeconds;
            else timeBetweenAnimation += deltaTimeSeconds; 
            // This is to make an animation when the player is eaten by the yeti
        }

        if (enemySkiOnField) {
            moveEnemy1(deltaTimeSeconds);
        }

        if (totalDistance - distanceToFirstEnemyDeath >= 800 && distanceToFirstEnemyDeath != 0) {
            if (!enemyJetDead && !enemyJetOnField) {
                enemyJetOnField = true;
                distanceEnemyToPlayer = -5;
                enemyUp = false;
                timeBetweenShots = 0;
            }
            else if (enemyJetDead) {
                enemyJetOnField = false;
            }
        }
    
        if (enemyJetOnField) {
            moveEnemy2(deltaTimeSeconds);
        }

        if (enemyJetDead && totalDistance - distancefromLastDeath >= 100) {
            if (!noMove) {
                snowPlanePosition = glm::vec3(playerPosition.x, 0, playerPosition.z + 3);
            }

            noMove = true;
            playerAngle = -M_PI_2;
            speedUpTime = 0;

            if (playerSpeed == 0) {
                gameWon = true;
                gameIsOn = false;
            }
        }
    }

    RenderScene();

    if (playerLives == 0) {
        gameIsOn = false;
        gameOver = true;
    }
}


void Tema3::FrameEnd()
{
    //DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, bool moving, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
    }

    GLint location = glGetUniformLocation(shader->program, "moving");
    int move = (moving) ? 1 : 0;
    glUniform1i(location, move);

    if (moving) {
        location = glGetUniformLocation(shader->program, "offset");
        glUniform2fv(location, 1, glm::value_ptr(glm::vec2(playerPosition.x, playerPosition.z)));

        location = glGetUniformLocation(shader->program, "scale");
        glUniform1f(location, SLOPE_SCALE);
    }

    // Set shader uniforms for directional light properties
    int dir_light_dir = glGetUniformLocation(shader->program, "directional_light_direction");
    glUniform3fv(dir_light_dir, 1, glm::value_ptr(directionalLightDirection));

    // Set shader uniforms for point light properties
    int number_of_point = glGetUniformLocation(shader->program, "number_of_point_lights");
    glUniform1i(number_of_point, objects.size());

    int light_position = glGetUniformLocation(shader->program, "point_light_position");
    glUniform3fv(light_position, objects.size(), glm::value_ptr(pointLightPositions[0]));

    int light_color = glGetUniformLocation(shader->program, "light_color");
    glUniform3fv(light_color, objects.size(), glm::value_ptr(pointLightColors[0]));

    // Set shader uniforms for the spot lights
    int spot_light_position = glGetUniformLocation(shader->program, "spot_light_position");
    glUniform3fv(spot_light_position, numberOfLightPoles * 2, glm::value_ptr(spotLight[0]));

    int number_of_spot_lights = glGetUniformLocation(shader->program, "number_of_spot_lights");
    glUniform1i(number_of_spot_lights, numberOfLightPoles * 2);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction, 1, glm::value_ptr(lightDirection));

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE && gunPartsCollected == 3) {
        playerBullet = ObjectOnSlope(playerPosition, BULLET_TYPE);
        gunPartsCollected = 0;

        if (enemySkiOnField) playerBulletDirection = glm::normalize(enemySkiPosition - playerBullet.getPosition());
        else if (enemyJetOnField) playerBulletDirection = glm::normalize(enemyJetPosition - playerBullet.getPosition());
        else playerBulletDirection = glm::vec3(0, 0, -1);
    }
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

// The mouse coordinates have the y axis inverted, so we invert it
int Tema3::MouseToWorld(int mouseY) {
    return window->GetResolution(true).y - mouseY;
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseY = MouseToWorld(mouseY);
    int resX = window->GetResolution(true).x;
    int resY = window->GetResolution(true).y;
    int centerX = resX / 2;
    int centerY = resY / 2;

    float tangent = (mouseY - centerY) / (float)(mouseX - centerX);

    if (mouseY >= centerY && mouseX >= centerX) playerAngle = 0;
    else if (mouseY >= centerY && mouseX < centerX) playerAngle = M_PI;
    else {
        playerAngle = atan(tangent);

        if (tangent > 0) playerAngle += M_PI;
    }

    // We limit the movement to a 60 degrees window
    if (playerAngle > -M_PI_2 / 3 && playerAngle < 0) playerAngle = -M_PI_2 / 3;

    if (playerAngle > (float)M_PI && playerAngle < (float)(M_PI * 7 / 6)) playerAngle = M_PI * 7 / 6;

    if (noMove) playerAngle = -M_PI_2;
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (startMenu) {
        if (mouseX >= 0.323 * window->GetResolution().x && mouseX <= 0.677 * window->GetResolution().x &&
            mouseY >= 0.464 * window->GetResolution().y && mouseY <= 0.544 * window->GetResolution().y) {
            gameIsOn = true;
            startMenu = false;
            initializeGame();
        }
        else if (mouseX >= 0.423 * window->GetResolution().x && mouseX <= 0.563 * window->GetResolution().x &&
            mouseY >= 0.597 * window->GetResolution().y && mouseY <= 0.678 * window->GetResolution().y) {
            window->Close();
        }
    }
    else if (gameOver) {
        if (mouseX >= 0.414 * window->GetResolution().x && mouseX <= 0.574 * window->GetResolution().x &&
            mouseY >= 0.799 * window->GetResolution().y && mouseY <= 0.838 * window->GetResolution().y) {
            initializeGame();
            gameIsOn = true;
            gameOver = false;
        }
        else if (mouseX >= 0.46 * window->GetResolution().x && mouseX <= 0.53 * window->GetResolution().x &&
            mouseY >= 0.865 * window->GetResolution().y && mouseY <= 0.907 * window->GetResolution().y) {
            startMenu = true;
            gameOver = false;
        }
        else if (mouseX >= 0.46 * window->GetResolution().x && mouseX <= 0.53 * window->GetResolution().x &&
            mouseY >= 0.931 * window->GetResolution().y && mouseY <= 0.972 * window->GetResolution().y) {
            window->Close();
        }
    }
    else if (gameWon) {
        if (mouseX >= 0.414 * window->GetResolution().x && mouseX <= 0.574 * window->GetResolution().x &&
            mouseY >= 0.799 * window->GetResolution().y && mouseY <= 0.838 * window->GetResolution().y) {
            initializeGame();
            gameIsOn = true;
            gameWon = false;
        }
        else if (mouseX >= 0.46 * window->GetResolution().x && mouseX <= 0.53 * window->GetResolution().x &&
            mouseY >= 0.865 * window->GetResolution().y && mouseY <= 0.907 * window->GetResolution().y) {
            startMenu = true;
            gameWon = false;
        }
        else if (mouseX >= 0.46 * window->GetResolution().x && mouseX <= 0.53 * window->GetResolution().x &&
            mouseY >= 0.931 * window->GetResolution().y && mouseY <= 0.972 * window->GetResolution().y) {
            window->Close();
        }
    }
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
