#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema3/ObjectOnSlope.h"
#include "components/text_renderer.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:
        Tema3();
        ~Tema3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void generateInitialLayout();
        void initializePlayer();
        void initializeGame();
        void addProceduralObjects();
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, bool moving,Texture2D *texture1 = NULL);
        void RenderSnow();
        void RenderSkier(glm::vec3 position, bool isPlayer);
        void RenderEnemy1();
        void RenderEnemy2();
        void RenderObjects();
        void RenderObject(glm::vec3 position, m1::ObjectOnSlope object);
        void RenderPresent(glm::vec3 position, int type);
        void RenderLight(glm::vec3 position);
        void RenderRock(glm::vec3 position);
        void RenderTree(glm::vec3 position);
        void RenderCabin();
        void RenderYeti();
        void RenderChopper();
        void RenderLives();
        void RenderTitle();
        void RenderHeads();
        void RenderSpeedBar();
        void RenderGunParts();
        void RenderBullets();
        void RenderHUD();
        void RenderScene();
        void verifyObjectsInScene();
        void verifyCollision();
        void verifyBulletCollision();
        void updatePointLights();
        void updateSpotLights();
        void updateLights();
        void SetCamera();
        void SetCameraHUD();

        int MouseToWorld(int mouseY);
        void movePlayer(float deltaTimeSeconds);
        void moveYeti(float deltaTimeSeconds);
        void movePlayerBullet(float deltaTimeSeconds);
        void moveBullets(float deltaTimeSeconds);
        void moveEnemy1(float deltaTimeSeconds);
        void moveEnemy2(float deltaTimeSeconds);
        void verifyCollisionBulletYeti();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D *> mapTextures;

        // The game will start with the player in the origin, with a little elevation, to ensure
        // that the player is above the snow.
        glm::vec3 playerPosition = glm::vec3(0.0f, 0.12f, 0.0f);
        float playerAngle = 0;
        float maxPlayerSpeed = 1.5;
        float playerSpeed = 1.5;
        glm::vec3 playerBoundingBox = glm::vec3(0.05, 0, 0.05); // We use AABB-AABB collision
        // We only care for the collision on the slope's plane

        // After a collision the player is invulnerable for a period of time
        float invulnerableTime;
        float maxInvulnerableTime = 3;
        float maxSpeedUpTime = 7;
        float speedUpTime;
        int playerLives = 3;
        int maxPlayerLives = 3;
        bool playerHasShield;
        int gunPartsCollected;

        float distanceBetweenObjects = 0.7;
        float playerBulletSpeed = 15;
        glm::vec3 playerBulletDirection;
        float bulletSpeed = 2.5;
        std::vector<m1::ObjectOnSlope> objects;
        std::vector<m1::ObjectOnSlope> bullets;
        m1::ObjectOnSlope playerBullet = ObjectOnSlope(glm::vec3(0), -1);
        glm::vec3 pointLightPositions[100];
        glm::vec3 pointLightColors[100];
        glm::vec3 spotLight[200];
        int numberOfLightPoles;
        glm::vec3 lightDirection = glm::vec3(0, -1, 0.3);
        glm::vec3 directionalLightDirection = glm::vec3(0, -1, 0);

        int materialShininess = 25;
        float materialKd = 0.5, materialKs = 0.25;

        float distance;
        float totalDistance;
        gfxc::Camera* camera;

        bool gameIsOn = false;
        bool startMenu = true;
        bool gameOver = false;
        bool gameWon = false;
        int score;
        gfxc::TextRenderer* text;
        float yetiAngle;
        bool yetiRight;
        bool yetiOnField;
        bool yetiDead;
        float distanceYetiToPlayer;
        float yetiSpeed = 3;
        float timeBetweenAnimation;
        float maxTimeBetweenAnimation = 0.2;
        bool enemySkiOnField;
        bool enemySkiDead;
        glm::vec3 enemySkiPosition;
        glm::vec3 enemyJetPosition;
        float distanceEnemyToPlayer;
        float maxEnemyDistance = 1.5;
        bool enemyUp;
        float timeBetweenShots;
        float maxTimeBetweenShots = 0.9;
        float maxTimeBetweenConsecShots = 0.3;
        bool enemyJetOnField;
        bool enemyJetDead;
        bool consecShots;
        int distanceToFirstEnemyDeath;
        bool noMove;
        glm::vec3 snowPlanePosition;
        float distancefromLastDeath;
    };
}   // namespace m1
