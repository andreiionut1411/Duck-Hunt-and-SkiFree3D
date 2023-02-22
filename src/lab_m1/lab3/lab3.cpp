#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    float squareSide2 = 300;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;
    cx2 = corner.x + squareSide2 / 2;
    cy2 = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* body = object2D::CreateSquare("body", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(body);

    Mesh* tireL = object2D::CreateSquare("tireL", corner, squareSide, glm::vec3(0.4, 0.6, 0.3), true);
    AddMeshToList(tireL);

    Mesh* tireR = object2D::CreateSquare("tireR", corner, squareSide, glm::vec3(0.4, 0.6, 0.3), true);
    AddMeshToList(tireR);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300 + translateX, 100);
    modelMatrix *= transform2D::Scale(3, 1);
    modelMatrix *= transform2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200 + translateX, 50);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["tireL"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400 + translateX, 50);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["tireR"], shaders["VertexColor"], modelMatrix);

    //if (forwardScale) {
    //        scaleX += deltaTimeSeconds * 3;
    //        scaleY += deltaTimeSeconds * 3;

    //        if (scaleX > 3) forwardScale = false;
    //}
    //else {
    //    scaleX -= deltaTimeSeconds * 3;
    //    scaleY -= deltaTimeSeconds * 3;

    //    if (scaleX < 0.5) forwardScale = true;
    //}


    //modelMatrix *= transform2D::Translate(200 + cx, 200 + cy);
    //modelMatrix *= transform2D::Scale(scaleX, scaleY);
    //modelMatrix *= transform2D::Translate(-cx, -cy);
    //// TODO(student): Create animations by multiplying the current
    //// transform matrix with the matrices you just implemented
    //// Remember, the last matrix in the chain will take effect first!

    //RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    //modelMatrix = glm::mat3(1);

    //angularStep += deltaTimeSeconds * 2;

    //modelMatrix *= transform2D::Translate(650 + cx, 200 + cy);
    //modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Translate(-cx, -cy);
    //// TODO(student): Create animations by multiplying the current
    //// transform matrix with the matrices you just implemented
    //// Remember, the last matrix in the chain will take effect first!

    //RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_D)) {
        angularStep -= deltaTime * 2;
        translateX += deltaTime * 150;

    }

    if (window->KeyHold(GLFW_KEY_A)) {
        angularStep += deltaTime * 2;
        translateX -= deltaTime * 150;

    }
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
