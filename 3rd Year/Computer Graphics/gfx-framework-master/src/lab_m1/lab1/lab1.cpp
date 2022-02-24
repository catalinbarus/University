#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!

    // Colour componenents
    red_colour = 0;
    green_colour = 0;
    blue_colour = 0;
    alpha_value = 1;

    // Base coordinates for the teapot
    tea_x = -3, tea_y = 0.5f, tea_z = 1;

    // Base coordinates for the archer
    archer_x = 3, archer_y = 0.2f, archer_z = 1;

    // Used for returning archer after jumping
    y_backup = 0.2f;

    // Used for cycling through models
    switchModel = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

    {
        Mesh* mesh2 = new Mesh("teapot");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh2->GetMeshID()] = mesh2;

        Mesh* mesh3 = new Mesh("Archer");
        mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/archer"), "Archer.fbx");
        meshes[mesh3->GetMeshID()] = mesh3;

        Mesh* mesh4 = new Mesh("loopmesh");
        mesh4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh4->GetMeshID()] = mesh4;  
    }

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(red_colour, green_colour, blue_colour, alpha_value);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    // Tepot object
    RenderMesh(meshes["teapot"], glm::vec3(tea_x, tea_y,tea_z));

    // Archer object
    RenderMesh(meshes["Archer"], glm::vec3(archer_x, archer_y, archer_z), glm::vec3(0.01f));

    // The object which we will cycle through
    RenderMesh(meshes["loopmesh"], glm::vec3(5, 0.8f, 1), glm::vec3(0.8f));

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

    float maxJump = archer_y + 5 * deltaTime;

    // Only move archer if the right click of the mouse is not pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) == 0) {
        if (window->KeyHold(GLFW_KEY_W)) { archer_x -= deltaTime; }
        if (window->KeyHold(GLFW_KEY_A)) { archer_z -= deltaTime; }
        if (window->KeyHold(GLFW_KEY_S)) { archer_x += deltaTime; }
        if (window->KeyHold(GLFW_KEY_D)) { archer_z += deltaTime; }
        if (window->KeyHold(GLFW_KEY_E)) { archer_y += deltaTime; }
        if (window->KeyHold(GLFW_KEY_Q)) { archer_y -= deltaTime; }

       
      
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        
        red_colour = (rand() % 255) / 255.f;
        green_colour = (rand() % 255) / 255.f;
        blue_colour = (rand() % 255) / 255.f;
        alpha_value = (rand() % 255) / 255.f;

    }

    // For BONUS
    if (key == GLFW_KEY_SPACE) {

        archer_y *= 3.0f;
        archer_z *= 1.5f;
    }

   
    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    if (key == GLFW_KEY_C) {


        // Use the C key for cycling through a tepot, box and sphere
        if (switchModel == 0) {
            Mesh* next_loop = new Mesh("loopmesh");
            switchModel++;

            next_loop->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
            meshes["loopmesh"]->ClearData();
            free(meshes["loopmesh"]);
            meshes["loopmesh"] = next_loop;
        }

        else if (switchModel == 1) {
            Mesh* next_loop = new Mesh("loopmesh");
            switchModel++;

            next_loop->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
            meshes["loopmesh"]->ClearData();
            free(meshes["loopmesh"]);
            meshes["loopmesh"] = next_loop;
        }

        else {

            Mesh* next_loop = new Mesh("loopmesh");
            switchModel = 0;

            next_loop->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
            meshes["loopmesh"]->ClearData();
            free(meshes["loopmesh"]);
            meshes["loopmesh"] = next_loop;
        }
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event

    // For BONUS
    // If we release space, it means the archer had jumped
    // so we return him to initial position
    if (key == GLFW_KEY_SPACE) {

        archer_y = y_backup;
    }
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
