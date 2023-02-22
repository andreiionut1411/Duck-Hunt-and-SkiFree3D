#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <random>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/Geometry.h"
#include "components/text_renderer.h"

#define BLACK glm::vec3(0, 0, 0)
#define WHITE glm::vec3(1, 1, 1)
#define RED glm::vec3(1, 0, 0)
#define BLUE glm::vec3(0, 0, 1)
#define PALE_ORANGE glm::vec3(0.992, 0.811, 0.447)
#define ORANGE glm::vec3(1, 0.5, 0)
#define DARK_RED glm::vec3(0.4, 0, 0)
#define GREEN glm::vec3(0.012, 0.675, 0.075)
#define BONEWHITE glm::vec3(0.953, 0.961, 0.910)
#define NEWBLACK glm::vec3(0.184, 0.184, 0.157)
#define NORMALDUCK 0
#define LIFEDUCK 1
#define SCOREDUCK 2
#define SLOWDUCK 3
#define BOSSDUCK 4

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::createNewDuck() {
    duck.centerOfDuckX = Duck::generateRandomDuckStartingPosition(resx / 8, resx * 7 / 8);
    duck.centerOfDuckY = Duck::generateRandomDuckStartingPosition(0, resy / 12);
    duck.duckAngle = Duck::generateRandomDuckAngle();
    timeDuckOnScreen = 0; // We start the timer for the duck.
    bullets = numberOfBullets; // We restart the number of bullets.
    writeLevelText = false;

    // We generate a random number between 1 and 10. If it is 1, then we have a duck
    // that gives the player a bonus life. If it is 2, then we have a duck that multiplies the score
    // by 10 for a period of time. If it is 3, then we have a duck that will slow the next
    // ducks for a period of time. For the rest of the numbers we have a normal duck.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 10);
    int x = distr(gen);

    if (x == LIFEDUCK) typeOfDuck = LIFEDUCK;
    else if (x == SCOREDUCK) typeOfDuck = SCOREDUCK;
    else if (x == SLOWDUCK) typeOfDuck = SLOWDUCK;
    else typeOfDuck = NORMALDUCK;
    
    // We reset the movement of the duck.
    duck.duckDirectionX = 0;
    duck.duckDirectionY = 0;

    // We reset the state of the duck.
    duck.escape = false;
    duck.dead = false;
    bossIsDead = false;

    // Once every 5 ducks, we speed them up and go to the next level.
    if (totalNumberOfDucks % 5 == 0 && totalNumberOfDucks > 0 && !duckIsBoss) {
        duckSpeed += duckSpeed / 3;
    }

    if (totalNumberOfDucks % 5 == 0) {
        level++;
    }

    currentSpeed = duckSpeed;

    if (duckIsBoss == true) duckIsBoss = false;
    else if (totalNumberOfDucks % 10 == 0 && totalNumberOfDucks > 0 && duckIsBoss == false) {
        duckIsBoss = true;
        totalNumberOfDucks--; // The boss is not one of the 5 normal ducks per level.
        typeOfDuck = BOSSDUCK;
        level--;
    }

    if (duckIsBoss) duckLives = 3;
    else duckLives = 1;
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    resx = resolution.x;
    resy = resolution.y;

    // Initialize the screen with a duck not in scene.
    duckOnScreen = false;
    timeDuckOffScreen = 0;
    timeDuckOnScreen = 0;
    duckIsBoss = false;

    // Initialize some basic game parameters.
    duckSpeed = initialDuckSpeed;
    totalNumberOfDucks = 0;
    consecutiveDucksKilled = 0;
    playerScore = 0;
    level = 0;
    comboMultiplier = 1;
    dogX = resolution.x / 2;
    dogY = 0;

    // Initializing for the text.
    text = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    text->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", 128);
    writeLevelText = true;

    // Initializing the meshes that we will use.
    Mesh* upperWing = geometry::CreateTriangle("upperWing", glm::vec3(0, 0, 0), duck.wingSize, duck.brown, true);
    AddMeshToList(upperWing);

    Mesh* lowerWing = geometry::CreateTriangle("lowerWing", glm::vec3(0, 0, 0), duck.wingSize, duck.brown, true);
    AddMeshToList(lowerWing);

    Mesh* redWing = geometry::CreateTriangle("redWing", glm::vec3(0, 0, 0), duck.wingSize, RED, true);
    AddMeshToList(redWing);

    Mesh* whiteWing = geometry::CreateTriangle("whiteWing", glm::vec3(0, 0, 0), duck.wingSize, BONEWHITE, true);
    AddMeshToList(whiteWing);

    Mesh* orangeWing = geometry::CreateTriangle("orangeWing", glm::vec3(0, 0, 0), duck.wingSize, PALE_ORANGE, true);
    AddMeshToList(orangeWing);

    Mesh* body = geometry::CreateTriangle("body", glm::vec3(0, 0, 0), duck.bodySize, duck.brown, true);
    AddMeshToList(body);

    Mesh* redBody = geometry::CreateTriangle("redBody", glm::vec3(0, 0, 0), duck.bodySize, RED, true);
    AddMeshToList(redBody);

    Mesh* blackBody = geometry::CreateTriangle("blackBody", glm::vec3(0, 0, 0), duck.bodySize, NEWBLACK, true);
    AddMeshToList(blackBody);

    Mesh* head = geometry::CreateCircle("head", 0, 0, duck.headRadius, duck.darkGreen, true);
    AddMeshToList(head);

    Mesh* orangeHead = geometry::CreateCircle("orangeHead", 0, 0, duck.headRadius, PALE_ORANGE, true);
    AddMeshToList(orangeHead);

    Mesh* whiteHead = geometry::CreateCircle("whiteHead", 0, 0, duck.headRadius, BONEWHITE, true);
    AddMeshToList(whiteHead);

    Mesh* beak = geometry::CreateTriangle("beak", glm::vec3(0, 0, 0), duck.beakSize, duck.yellow, true);
    AddMeshToList(beak);

    Mesh* bullet = geometry::CreateRectangle("bullet", glm::vec3(0, 0, 0), 22, 7, WHITE, false);
    AddMeshToList(bullet);

    Mesh* life = geometry::CreateCircle("life", 0, 0, 12, RED, true);
    AddMeshToList(life);

    Mesh* scoreWireframe = geometry::CreateRectangle("wireframe", glm::vec3(0, 0, 0), 30, 240, WHITE, false);
    AddMeshToList(scoreWireframe);

    Mesh* scoreBar = geometry::CreateRectangle("scorebar", glm::vec3(0, 0, 0), 30, 240, BLUE, true);
    AddMeshToList(scoreBar);

    Mesh* slowBar = geometry::CreateRectangle("slowbar", glm::vec3(0, 0, 0), 30, 240, PALE_ORANGE, true);
    AddMeshToList(slowBar);

    Mesh* multiplyBar = geometry::CreateRectangle("multiplybar", glm::vec3(0, 0, 0), 30, 240, NEWBLACK, true);
    AddMeshToList(multiplyBar);

    Mesh* combo_x2 = geometry::CreateRectangle("x2", glm::vec3(0, 0, 0), 40, 40, PALE_ORANGE, true);
    AddMeshToList(combo_x2);

    Mesh* combo_x3 = geometry::CreateRectangle("x3", glm::vec3(0, 0, 0), 40, 40, ORANGE, true);
    AddMeshToList(combo_x3);

    Mesh* combo_x4 = geometry::CreateRectangle("x4", glm::vec3(0, 0, 0), 40, 40, RED, true);
    AddMeshToList(combo_x4);

    Mesh* combo_x5 = geometry::CreateRectangle("x5", glm::vec3(0, 0, 0), 40, 40, DARK_RED, true);
    AddMeshToList(combo_x5);

    Mesh* grass = new Mesh("grass");
    grass->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "grass.fbx");
    meshes[grass->GetMeshID()] = grass;

    Mesh* gun = new Mesh("gun");
    gun->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "gun.fbx");
    meshes[gun->GetMeshID()] = gun;

    Mesh* scope = new Mesh("scope");
    scope->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "scope.fbx");
    meshes[scope->GetMeshID()] = scope;

    Mesh* tree = new Mesh("tree");
    tree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "tree.fbx");
    meshes[tree->GetMeshID()] = tree;

    Mesh* cloud = new Mesh("cloud");
    cloud->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "cloud.fbx");
    meshes[cloud->GetMeshID()] = cloud;

    Mesh* amogus = new Mesh("amogus");
    amogus->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "amogus.fbx");
    meshes[amogus->GetMeshID()] = amogus;

    Mesh* dead_amogus = new Mesh("dead_amogus");
    dead_amogus->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "dead_amogus.fbx");
    meshes[dead_amogus->GetMeshID()] = dead_amogus;

    Mesh* go = new Mesh("game_over");
    go->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "game_over.fbx");
    meshes[go->GetMeshID()] = go;

    Mesh* dog_laugh = new Mesh("dog_laugh");
    dog_laugh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "dog_laugh.fbx");
    meshes[dog_laugh->GetMeshID()] = dog_laugh;

    Mesh* dog_duck = new Mesh("dog_duck");
    dog_duck->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "Tema1"), "dog_duck.fbx");
    meshes[dog_duck->GetMeshID()] = dog_duck;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.224, 0.569, 0.741, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

// The function renders the duck based on its position and orientation.
void Tema1::RenderDuck(Duck::Duck duck) {
    // Rendering the head
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.duckDirectionX, duck.duckDirectionY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX, duck.centerOfDuckY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Translate(-duck.centerOfDuckX, -duck.centerOfDuckY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.headX, duck.centerOfDuckY + duck.headY);

    if (typeOfDuck == NORMALDUCK || typeOfDuck == LIFEDUCK) {
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    }
    else if (typeOfDuck == SCOREDUCK) RenderMesh2D(meshes["whiteHead"], shaders["VertexColor"], modelMatrix);
    else if (typeOfDuck == SLOWDUCK) RenderMesh2D(meshes["orangeHead"], shaders["VertexColor"], modelMatrix);

    // Rendering the beak
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.duckDirectionX, duck.duckDirectionY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX, duck.centerOfDuckY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Translate(-duck.centerOfDuckX, -duck.centerOfDuckY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.beakX, duck.centerOfDuckY + duck.beakY);
    modelMatrix *= transform2D::Rotate(3 * M_PI / 2);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

    // Rendering the body
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.duckDirectionX, duck.duckDirectionY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX, duck.centerOfDuckY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Rotate(3 * M_PI / 2);

    if (typeOfDuck == NORMALDUCK || typeOfDuck == SLOWDUCK) {
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    }
    else if (typeOfDuck == LIFEDUCK) RenderMesh2D(meshes["redBody"], shaders["VertexColor"], modelMatrix);
    else RenderMesh2D(meshes["blackBody"], shaders["VertexColor"], modelMatrix);

    // Rendering the upper wing
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.duckDirectionX, duck.duckDirectionY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX, duck.centerOfDuckY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Translate(-duck.centerOfDuckX, -duck.centerOfDuckY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.upperWingX, duck.centerOfDuckY + duck.upperWingY);
    modelMatrix *= transform2D::Rotate(duck.currentAngleWings);

    if (typeOfDuck == NORMALDUCK) RenderMesh2D(meshes["upperWing"], shaders["VertexColor"], modelMatrix);
    else if (typeOfDuck == LIFEDUCK) RenderMesh2D(meshes["redWing"], shaders["VertexColor"], modelMatrix);
    else if (typeOfDuck == SLOWDUCK) RenderMesh2D(meshes["orangeWing"], shaders["VertexColor"], modelMatrix);
    else RenderMesh2D(meshes["whiteWing"], shaders["VertexColor"], modelMatrix);

    // Rendering the lower wing
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.duckDirectionX, duck.duckDirectionY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX, duck.centerOfDuckY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Translate(-duck.centerOfDuckX, -duck.centerOfDuckY);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.lowerWingX, duck.centerOfDuckY + duck.lowerWingY);
    modelMatrix *= transform2D::Rotate(-duck.currentAngleWings);
    modelMatrix *= transform2D::Rotate(M_PI);

    if (typeOfDuck == NORMALDUCK) RenderMesh2D(meshes["lowerWing"], shaders["VertexColor"], modelMatrix);
    else if (typeOfDuck == LIFEDUCK) RenderMesh2D(meshes["redWing"], shaders["VertexColor"], modelMatrix);
    else if (typeOfDuck == SLOWDUCK) RenderMesh2D(meshes["orangeWing"], shaders["VertexColor"], modelMatrix);
    else RenderMesh2D(meshes["whiteWing"], shaders["VertexColor"], modelMatrix);
}

void Tema1::renderBoss() {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.duckDirectionX, duck.centerOfDuckY + duck.duckDirectionY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Scale(174, 180);

    if (!bossIsDead) {
        RenderMesh2D(meshes["amogus"], shaders["Simple"], modelMatrix);
    }
    else {
        RenderMesh2D(meshes["dead_amogus"], shaders["Simple"], modelMatrix);
    }
}

void Tema1::RenderHUD() {
    // Render level text.
    renderLevelText();

    // Rendering the gun.
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resx / 2, 40);
    modelMatrix *= transform2D::Scale(200, 200);
    modelMatrix *= transform2D::Rotate(gunAngle);
    RenderMesh2D(meshes["gun"], shaders["Simple"], modelMatrix);

    // Rendering the scope of the gun.
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xMouse, yMouse);
    modelMatrix *= transform2D::Scale(75, 75);
    RenderMesh2D(meshes["scope"], shaders["Simple"], modelMatrix);

    // Rendering the tree.
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 300);
    modelMatrix *= transform2D::Scale(400, 500);
    RenderMesh2D(meshes["tree"], shaders["Simple"], modelMatrix);

    // Rendering the player's number of bullets.
    for (int i = 0; i < bullets; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resx - (i + 1) * 20, resy - 50);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    // Rendering the player's number of lives.
    for (int i = 0; i < numberOfLives; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resx - (i + 1) * 30 - 100, resy - 40);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }

    // Rendering the score bar.
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resx - 260, resy - 100);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

    // For the score, if the player has 0 points, we don't need to render anything.
    if (playerScore > 0 && playerScore < maxScore) {
        modelMatrix *= transform2D::Scale((float)(playerScore) / maxScore, 1);
        RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);
    }
    else if (playerScore > 0) {
        // When the bar is full, we don't continue adding the score to the bar.
        RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);
    }

    // Rendering the ability timer if we have the slow ability.
    if (timeSlowAbility > 0) {
        modelMatrix = glm::mat3(1);

        // If we have both abilities that have a timer, then we chain them, one under the other.
        if (firstBar == SLOWDUCK) modelMatrix *= transform2D::Translate(resx - 260, resy - 140);
        else modelMatrix *= transform2D::Translate(resx - 260, resy - 180);
        RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

        // The total time of the ability is 10 seconds.
        modelMatrix *= transform2D::Scale((float)(timeSlowAbility) / 10, 1);
        RenderMesh2D(meshes["slowbar"], shaders["VertexColor"], modelMatrix);
    }

    // Rendering the ability timer if we have the score ability.
    if (timeScoreAbility > 0) {
        modelMatrix = glm::mat3(1);

        // If we have both abilities that have a timer, then we chain them, one under the other.
        if (firstBar == SCOREDUCK) modelMatrix *= transform2D::Translate(resx - 260, resy - 140);
        else modelMatrix *= transform2D::Translate(resx - 260, resy - 180);
        RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

        // The total time of the ability is 10 seconds.
        modelMatrix *= transform2D::Scale((float)(timeScoreAbility) / 10, 1);
        RenderMesh2D(meshes["multiplybar"], shaders["VertexColor"], modelMatrix);
    }

    // If we have a combo, then we render the square with the color based on the killing spree.
    if (comboMultiplier != 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resx - 80, 50);
        modelMatrix *= transform2D::Translate(20, 20);
        modelMatrix *= transform2D::Rotate(angleForCombo);
        modelMatrix *= transform2D::Translate(-20, -20);

        if (comboMultiplier == 2) {
            RenderMesh2D(meshes["x2"], shaders["VertexColor"], modelMatrix);
        }
        else if (comboMultiplier == 3) {
            RenderMesh2D(meshes["x3"], shaders["VertexColor"], modelMatrix);
        }
        else if (comboMultiplier == 4) {
            RenderMesh2D(meshes["x4"], shaders["VertexColor"], modelMatrix);
        }
        else if (comboMultiplier == 5) {
            RenderMesh2D(meshes["x5"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Rendering the grass.
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 90);
    modelMatrix *= transform2D::Scale(400, 200);
    RenderMesh2D(meshes["grass"], shaders["Simple"], modelMatrix);
}

void Tema1::renderBackground() {
    // Render the clouds in the background
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 350);
    modelMatrix *= transform2D::Scale(300, 200);
    RenderMesh2D(meshes["cloud"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 500);
    modelMatrix *= transform2D::Scale(300, 200);
    RenderMesh2D(meshes["cloud"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 430);
    modelMatrix *= transform2D::Scale(300, 200);
    RenderMesh2D(meshes["cloud"], shaders["Simple"], modelMatrix);
}

void Tema1::renderDog(float deltaTime, bool duckEscaped) {
    if (dogGoesUp) {
        dogY += 300 * deltaTime;
        timeDogIsUp = 0;
    }
    if (!dogGoesUp && timeDogIsUp >= 1) {
        dogY -= 300 * deltaTime;
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(dogX, dogY);
    modelMatrix *= transform2D::Scale(100, 100);

    if (duckEscaped)
        RenderMesh2D(meshes["dog_laugh"], shaders["Simple"], modelMatrix);
    else
        RenderMesh2D(meshes["dog_duck"], shaders["Simple"], modelMatrix);

    if (dogY >= 100) {
        timeDogIsUp += deltaTime;
        dogGoesUp = false;
    }
}

void Tema1::renderLevelText() {
    if (writeLevelText) {
        if (totalNumberOfDucks % 10 == 0 && totalNumberOfDucks > 0 && !duckIsBoss)
            text->RenderText("Boss level", resx * 3 / 8, resy / 2, 0.5);
        else
            text->RenderText("Level " + to_string(level + 1), resx * 3 / 8, resy / 2, 0.5);
    }

    text->RenderText("Score " + to_string(playerScore), resx / 25, resy / 30, 0.22);
}

void Tema1::Update(float deltaTimeSeconds)
{
    RenderHUD();

    if (deltaTimeSeconds < 1) {
        if (!gameOver) {
            if (!duckOnScreen && totalNumberOfDucks > 0) {
                renderDog(deltaTimeSeconds, duckEscaped);
            }

            if (!duckIsBoss) {
                RenderDuck(duck);
            }
            else {
                renderBoss();
            }

            if (slowAbility) currentSpeed = duckSpeed / 2;

            timeDuckOnScreen += deltaTimeSeconds;
            timeDuckOffScreen += deltaTimeSeconds;
            timeSlowAbility -= deltaTimeSeconds;
            timeScoreAbility -= deltaTimeSeconds;
            timeDogIsUp += deltaTimeSeconds;
            angleForCombo += 3 * deltaTimeSeconds;

            if (timeSlowAbility <= 0) {
                slowAbility = false;
                currentSpeed = duckSpeed;
                if (firstBar == SLOWDUCK && timeScoreAbility > 0) firstBar = SCOREDUCK;
            }

            if (timeScoreAbility <= 0) {
                scoreAbility = false;

                if (firstBar == SCOREDUCK && timeSlowAbility > 0) firstBar = SLOWDUCK;
            }

            if (timeSlowAbility <= 0 && timeScoreAbility <= 0) firstBar = 0;

            // We calculate the corner of the hitbox.
            if (!duckIsBoss) {
                bottomLeftX = duck.centerOfDuckX - bottomOfDuck;
                bottomLeftY = duck.centerOfDuckY + tipOfWing;
            }
            else {
                bottomLeftX = duck.centerOfDuckX + leftOfBoss;
                bottomLeftY = duck.centerOfDuckY + feetOfBoss;
            }

            // If we don't shoot the duck for 5 seconds, it escapes.
            if (timeDuckOnScreen > 5 || bullets == 0) {
                duck.escape = true;
            }

            // If the duck left the screen after it escaped, the player loses a life.
            if (duckOnScreen == true && duck.centerOfDuckY + duck.duckDirectionY - bottomOfDuck > resy) {
                duckOnScreen = false;
                duckEscaped = true;
                timeDuckOffScreen = 0;
                timeDuckOnScreen = 0;
                numberOfLives--;
                totalNumberOfDucks++;

                // When the player has no more lives, the game ends.
                if (numberOfLives == 0) gameOver = true;

                // When a duck escapes, we lose the combo.
                consecutiveDucksKilled = 0;
                comboMultiplier = 1;

                // We use this for the animation of the dog.
                dogX = duck.centerOfDuckX + duck.duckDirectionX;
                dogGoesUp = true;

                // If we change the level, we print the text.
                if (totalNumberOfDucks % 5 == 0) writeLevelText = true;
            }

            // If the duck leaves the field through the ground, then it means we hit it, so we get the score.
            if (duckOnScreen == true && duck.centerOfDuckY + duck.duckDirectionY + bottomOfDuck < 0) {
                duckOnScreen = false;
                duckEscaped = false;
                timeDuckOffScreen = 0;

                // We use this for the animation of the dog.
                dogX = duck.centerOfDuckX + duck.duckDirectionX;
                dogGoesUp = true;

                // We have a different scheme of scoring the bosses.
                if (!duckIsBoss) {
                    if (!scoreAbility) playerScore += duckScore * level * comboMultiplier;
                    else playerScore += duckScore * level * 10;
                }
                else {
                    if (!scoreAbility) playerScore += bossScore * numberOfBossesKilled * comboMultiplier;
                    else playerScore += bossScore * numberOfBossesKilled * 10;
                }

                totalNumberOfDucks++;
                consecutiveDucksKilled++;

                if (consecutiveDucksKilled % 3 == 0 && comboMultiplier < 5) {
                    comboMultiplier++;
                }

                // We apply the different effects of different ducks.
                if (typeOfDuck == LIFEDUCK) {
                    if (numberOfLives < maximumNumberOfLives) {
                        numberOfLives++;
                    }
                }
                else if (typeOfDuck == SCOREDUCK) {
                    timeScoreAbility = 10;
                    scoreAbility = true;

                    if (firstBar == 0) firstBar = SCOREDUCK;
                }
                else if (typeOfDuck == SLOWDUCK) {
                    timeSlowAbility = 10;
                    slowAbility = true;

                    if (firstBar == 0) firstBar = SLOWDUCK;
                }

                // If we change the level, we print the text.
                if (totalNumberOfDucks % 5 == 0) writeLevelText = true;
            }

            // If we don't have a duck on the screen for 1.5 second, then we add one.
            if (duckOnScreen == false && timeDuckOffScreen > 1.5) {
                duckOnScreen = true;
                createNewDuck();
            }

            // We make the wings flap.
            if (duck.forwardFlap) {
                duck.currentAngleWings += 2.5 * deltaTimeSeconds;

                if (duck.currentAngleWings > M_PI_4) duck.forwardFlap = false;
            }
            else {
                duck.currentAngleWings -= 2.5 * deltaTimeSeconds;

                if (duck.currentAngleWings < -M_PI_4) duck.forwardFlap = true;
            }

            // Movement in the direction the duck is facing.
            if (duckOnScreen) {
                // We do this, so that the duck doesn't fall faster
                if (duck.dead) {
                    currentSpeed = initialDuckSpeed;
                }

                duck.duckDirectionX += deltaTimeSeconds * currentSpeed * cos(duck.duckAngle);
                duck.duckDirectionY += deltaTimeSeconds * currentSpeed * sin(duck.duckAngle);
            }

            if (!duck.dead && !duck.escape) {
                // ceiling
                if (duck.centerOfDuckY + duck.headY + duck.duckDirectionY >= resy) {
                    if (duck.duckAngle > 0 && duck.duckAngle < M_PI_2) {
                        duck.duckAngle = 2 * M_PI - duck.duckAngle;
                    }
                    else if (duck.duckAngle > M_PI_2 && duck.duckAngle < M_PI) {
                        duck.duckAngle = 2 * M_PI - duck.duckAngle;
                    }
                }

                // right wall
                if (duck.centerOfDuckX + duck.headX + duck.duckDirectionX >= resx) {
                    if (duck.duckAngle > 0 && duck.duckAngle < M_PI_2) {
                        duck.duckAngle = M_PI - duck.duckAngle;
                    }
                    else if (duck.duckAngle > 3 * M_PI_2) {
                        duck.duckAngle = 3 * M_PI - duck.duckAngle;
                    }
                }

                // floor
                if (duck.centerOfDuckY - duck.headY + duck.duckDirectionY <= 0) {
                    if (duck.duckAngle > 3 * M_PI_2) {
                        duck.duckAngle = 2 * M_PI - duck.duckAngle;
                    }
                    else if (duck.duckAngle > M_PI && duck.duckAngle < 3 * M_PI_2) {
                        duck.duckAngle = 2 * M_PI - duck.duckAngle;
                    }
                }

                // The duck's head is fixed as a positive number, as if it faces right.
                // But if we hit the left wall, it means it faces left, so we need to subtract
                // the head's direction. The duck's angle can be in one of two quadrants.
                if (duck.centerOfDuckX - duck.headX + duck.duckDirectionX <= 0) {
                    if (duck.duckAngle <= M_PI && duck.duckAngle >= M_PI_2) {
                        duck.duckAngle = M_PI - duck.duckAngle;
                    }
                    else if (duck.duckAngle > M_PI && duck.duckAngle < 3 * M_PI_2) {
                        duck.duckAngle = 3 * M_PI - duck.duckAngle;
                    }
                }
            }
            else if (duck.dead) {
                duck.duckAngle = 3 * M_PI_2;
            }
            else if (duck.escape) {
                duck.duckAngle = M_PI_2;
            }
        }
        else {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(resx / 2 - 20, resy / 2);
            modelMatrix *= transform2D::Scale(450, 450);
            RenderMesh2D(meshes["game_over"], shaders["Simple"], modelMatrix);
        }
    }

    renderBackground();
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

bool Tema1::mouseInBox(int mouseX, int mouseY) {
    // We move the points so the bottom left corner of the hitbox is in the origin.
    // Then, we rotate with negative the angle, so we get the hitbox in origin and "facing"
    // on the direction of Ox. This way, if our mouse point is in this box, it means we hit the duck.
    int duckWidth, duckHeight;

    glm::vec3 bottomLeft = glm::vec3(bottomLeftX, bottomLeftY, 1);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duck.centerOfDuckX + duck.duckDirectionX, duck.centerOfDuckY + duck.duckDirectionY);
    modelMatrix *= transform2D::Rotate(duck.duckAngle);
    modelMatrix *= transform2D::Translate(-duck.centerOfDuckX, -duck.centerOfDuckY);
    bottomLeft = modelMatrix * bottomLeft;

    glm::vec3 mouseVector = glm::vec3(mouseX, mouseY, 1);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Rotate(-duck.duckAngle);
    modelMatrix *= transform2D::Translate(-bottomLeft.x, -bottomLeft.y);

    mouseVector = modelMatrix * mouseVector;

    if (!duckIsBoss) {
        duckWidth = width;
        duckHeight = height;
    }
    else {
        duckWidth = widthOfBoss;
        duckHeight = heightOfBoss;
    }

    if (mouseVector.x >= 0 && mouseVector.x <= duckWidth && mouseVector.y >= 0 && mouseVector.y <= duckHeight) {
        return true;
    }

    return false;
}

// When the player kills a boss, it will receive rewards, based on the number of bosses it killed.
void Tema1::bossKilled() {
    if (numberOfBossesKilled == 1 || numberOfBossesKilled == 3) {
        numberOfBullets++;
    }
    else {
        duckSpeed = 2 * duckSpeed / 3;
    }

    bossIsDead = true;
}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    // We go from the scrren's coordinates to the window's coordinates
    xMouse = mouseX;
    yMouse = resy - mouseY;
    float tangent = (float)yMouse / (xMouse - resx / 2);
    gunAngle = atan(tangent);

    if (tangent < 0) {
        gunAngle += M_PI;
    }

    // The gun mesh has already an 135 degrees angle, so we account for that.
    gunAngle -= 3 * M_PI_4;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2) {

        // We transform the coordinates from the window's space to the scene's space.
        int duckCoordinatesX = mouseX;
        int duckCoordinatesY = resy - mouseY;

        bullets--;
        
        // If we click the duck and we still have bullets, it dies.
        if (bullets >= 0 && mouseInBox (duckCoordinatesX, duckCoordinatesY)) {
            duckLives--;

            // When we hit the boss, it changes the angle.
            if (duckIsBoss) duck.duckAngle = Duck::generateRandomDuckAngle();

            if (duckLives == 0) {
                duck.dead = true;

                if (duckIsBoss) {
                    numberOfBossesKilled++;
                    bossKilled();
                }
            }
        }
   }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
