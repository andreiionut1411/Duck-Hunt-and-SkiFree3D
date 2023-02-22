#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema1/Duck.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;
        void RenderDuck(Duck::Duck duck);
        void RenderHUD();
        void createNewDuck();
        bool mouseInBox(int mouseX, int mouseY);
        void renderBackground();
        void renderBoss();
        void bossKilled();
        void renderDog(float deltaTime, bool duckEscaped);
        void renderLevelText();

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        bool gameOver = false;
        int playerScore;
        const int duckScore = 500;
        const int bossScore = 10000;
        int numberOfBossesKilled = 0;
        int level = 0;
        int comboMultiplier;
        int consecutiveDucksKilled;
        const int maxScore = 500000;
        float angleForCombo = 0; // The square for the killing spree should rotate with this angle.
        int xMouse = 0, yMouse = 0;
        float gunAngle;
        gfxc::TextRenderer* text; // We use this for rendering text.

        Duck::Duck duck; // The duck that is on screen at one point in time
        int resx, resy; // The window dimensions
        int bullets;
        int numberOfBullets = 3; // The player can increase their number of bullets, but no more than 5.
        int numberOfLives = 3;
        const int maximumNumberOfLives = 5; // The player can increase their number of lives, but no more than 5.
        float timeDuckOnScreen;
        float timeDuckOffScreen;
        float timeSlowAbility;
        float timeScoreAbility;
        bool writeLevelText;
        int firstBar = 0; // This helps us if we have 2 abilities stacked.
        bool slowAbility;
        bool scoreAbility;
        bool duckOnScreen;
        const int initialDuckSpeed = 300;
        int duckSpeed;
        int currentSpeed;
        int totalNumberOfDucks;
        bool duckIsBoss;
        bool bossIsDead;
        int duckLives; // A normal duck has one life, while the boss has 3.
        int typeOfDuck; // It tells us if we have a normal duck, or a special ability one.
        int dogX, dogY;
        bool dogGoesUp;
        float timeDogIsUp;
        bool duckEscaped;

        // The distance from the center to the bottom of the duck
        const float bottomOfDuck = duck.bodySize * (sqrt(6) + sqrt(2)) / 12;

        // The distance from the center to the bottom of the wing
        const float tipOfWing = duck.lowerWingY - duck.wingSize * (sqrt(6) + sqrt(2)) / 6;

        // We will use this to identify the hitbox for the duck
        float bottomLeftX, bottomLeftY;

        // For the width we add the following: the distance from the bottom to the center,
       // then from the center to the center of the beak, then the distance from the
       // center of the beak to the tip.
        const float width = bottomOfDuck + duck.beakX + duck.beakSize * (sqrt(6) + sqrt(2)) / 6;

        // For the height, we have the difference from the top of the upper wing to the lower wing.
        // We add a minus because tipOfWing is neagative.
        int height = 2 * (-tipOfWing);

        // We use these in order to make the hitbox for the boss.
        const int leftOfBoss = -50;
        const int feetOfBoss = -70;
        const int heightOfBoss = 135;
        const int widthOfBoss = 100;
    };
}   // namespace m1
