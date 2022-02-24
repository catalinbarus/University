#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/transform2D.h"
#include "lab_m1/Tema2/object2D.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

 // Basic punction for power of a number
float powfunc(float x) {
    return x * x;
}

float cameraSpeed = 4.0f;

float timeLeft;
float timeFrame;

float health;
float healthFrame;

float stamina;
float staminaFrame;
float okToDepleteStamina = 0;

float mazeCleared = 0;

float obstaclesX[1000000];
float obstaclesZ[1000000];
int numberOfObstacles;
int okToMove = 0;
int done = 0;

float goalX;
float goalY;
float goalZ;

float playerX;
float playerY;
float playerZ;

float leftArmX;
float leftArmY;
float leftArmZ;

float leftHandX;
float leftHandY;
float leftHandZ;

float rightArmX;
float rightArmY;
float rightArmZ;

float rightHandX;
float rightHandY;
float rightHandZ;

float leftLegX;
float leftLegY;
float leftLegZ;

float rightLegX;
float rightLegY;
float rightLegZ;

float projectileX;
float projectileY;
float projectileZ;

float cameraX;
float cameraY;
float cameraZ;

float wall1X;
float wall1Y;
float wall1Z;

float wall2X;
float wall2Y;
float wall2Z;

float wall3X;
float wall3Y;
float wall3Z;

float playerXBackup0;
float playerZBackup0;

float playerXBackup1;
float playerZBackup1;

float playerXBackup2;
float playerZBackup2;

float playerXBackup3;
float playerZBackup3;

int okToShoot;

float enemy1X;
float enemy1Y;
float enemy1Z;

int switchEnemy1 = 0;

float enemy1LeftArmX;
float enemy1LeftArmY;
float enemy1LeftArmZ;

float enemy1LeftHandX;
float enemy1LeftHandY;
float enemy1LeftHandZ;

float enemy1RightArmX;
float enemy1RightArmY;
float enemy1RightArmZ;

float enemy1RightHandX;
float enemy1RightHandY;
float enemy1RightHandZ;

float enemy1LeftLegX;
float enemy1LeftLegY;
float enemy1LeftLegZ;

float enemy1RightLegX;
float enemy1RightLegY;
float enemy1RightLegZ;

float enemy2X;
float enemy2Y;
float enemy2Z;

int switchEnemy2 = 0;

float enemy2LeftArmX;
float enemy2LeftArmY;
float enemy2LeftArmZ;

float enemy2LeftHandX;
float enemy2LeftHandY;
float enemy2LeftHandZ;

float enemy2RightArmX;
float enemy2RightArmY;
float enemy2RightArmZ;

float enemy2RightHandX;
float enemy2RightHandY;
float enemy2RightHandZ;

float enemy2LeftLegX;
float enemy2LeftLegY;
float enemy2LeftLegZ;

float enemy2RightLegX;
float enemy2RightLegY;
float enemy2RightLegZ;

float enemy3X;
float enemy3Y;
float enemy3Z;

int switchEnemy3 = 0;

float enemy3LeftArmX;
float enemy3LeftArmY;
float enemy3LeftArmZ;

float enemy3LeftHandX;
float enemy3LeftHandY;
float enemy3LeftHandZ;

float enemy3RightArmX;
float enemy3RightArmY;
float enemy3RightArmZ;

float enemy3RightHandX;
float enemy3RightHandY;
float enemy3RightHandZ;

float enemy3LeftLegX;
float enemy3LeftLegY;
float enemy3LeftLegZ;

float enemy3RightLegX;
float enemy3RightLegY;
float enemy3RightLegZ;

float enemy4X;
float enemy4Y;
float enemy4Z;

int switchEnemy4 = 0;

float enemy4LeftArmX;
float enemy4LeftArmY;
float enemy4LeftArmZ;

float enemy4LeftHandX;
float enemy4LeftHandY;
float enemy4LeftHandZ;

float enemy4RightArmX;
float enemy4RightArmY;
float enemy4RightArmZ;

float enemy4RightHandX;
float enemy4RightHandY;
float enemy4RightHandZ;

float enemy4LeftLegX;
float enemy4LeftLegY;
float enemy4LeftLegZ;

float enemy4RightLegX;
float enemy4RightLegY;
float enemy4RightLegZ;

int mazeGen;

float angularStepOX, angularStepOY, angularStepOZ;

// Initial value for camera orientation (it is alwyas behind the player)

/*
     0 = camera is on the plus side of Z axis (forward)
     1 = camera is on the plus side of X axis (left)
     2 = camera is on the negative side of Z axis (back)
     3 = camera is on the negative side of X axis (right)
*/
float whichDirection = 0;


void Tema2::CreateCube(const char* name, float length) {

    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-length / 2, -length / 2,  length / 2), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(length / 2, -length / 2,  length / 2), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-length / 2,  length / 2,  length / 2), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(length / 2,  length / 2,  length / 2), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-length / 2, -length / 2, -length / 2), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(length / 2, -length / 2, -length / 2), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-length / 2,  length / 2, -length / 2), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(length / 2,  length / 2, -length / 2), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0)),

    };

    vector<unsigned int> indices =
    {
        0, 1, 2,        1, 3, 2,
        2, 3, 7,        2, 7, 6,
        1, 7, 3,        1, 5, 7,
        6, 7, 4,        7, 5, 4,
        0, 4, 1,        1, 4, 5,
        2, 6, 4,        0, 2, 4,

    };

    CreateMesh(name, vertices, indices);

}

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
    srand(time(NULL));
    renderCameraTarget = false;
    mazeGen = rand() % 3;

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 1;

    timeLeft = 60;
    timeFrame = 1.2f;

    right = 5.f;
    left = 0.05f;
    bottom = 0.05f;
    top = 5.f;
    fieldOfView = 50.f;

    health = 100;
    healthFrame = 1.2f;

    stamina = 100;
    staminaFrame = 1.2f;

    if (mazeGen == 0) {
        playerX = 0;
        playerY = 1.9f;
        playerZ = 0;

        goalX = -10;
        goalY = 0;
        goalZ = -15;
    }

    if (mazeGen == 1) {
        playerX = -20;
        playerY = 1.9f;
        playerZ = 20;

        goalX = 18;
        goalY = 0;
        goalZ = -21;
    }

    if (mazeGen == 2) {
        playerX = 20;
        playerY = 1.9f;
        playerZ = 20;

        goalX = -22;
        goalY = 0;
        goalZ = -13;
    }

    numberOfObstacles = 0;

    projectileX = playerX;
    projectileY = playerY + 0.5f;
    projectileZ = playerZ;

    okToShoot = 0;

    leftArmX = playerX - 0.6f;
    leftArmY = playerY + 0.8f;
    leftArmZ = playerZ;

    leftHandX = playerX - 0.6f;
    leftHandY = playerY + 0.3f;
    leftHandZ = playerZ;

    rightArmX = playerX + 0.6f;
    rightArmY = playerY + 0.8f;
    rightArmZ = playerZ;

    rightHandX = playerX + 0.6f;
    rightHandY = playerY + 0.3f;
    rightHandZ = playerZ;

    leftLegX = playerX - 0.25f;
    leftLegY = playerY - 0.4f;
    leftLegZ = playerZ;

    rightLegX = playerX + 0.25f;
    rightLegY = playerY - 0.4f;
    rightLegZ = playerZ;


    if (mazeGen == 0) {
        enemy1X = -14;
        enemy1Y = 1.5f;
        enemy1Z = 4;

        enemy2X = 10;
        enemy2Y = 1.5f;
        enemy2Z = 0;

        enemy3X = -7;
        enemy3Y = 1.5f;
        enemy3Z = 0;

        enemy4X = 0;
        enemy4Y = 1.5f;
        enemy4Z = -15;
    }

    if (mazeGen == 1) {
        enemy1X = 0;
        enemy1Y = 1.5f;
        enemy1Z = 0;

        enemy2X = 13;
        enemy2Y = 1.5f;
        enemy2Z = 0;

        enemy3X = -13;
        enemy3Y = 1.5f;
        enemy3Z = 0;

        enemy4X = -19;
        enemy4Y = 1.5f;
        enemy4Z = 0;
    }

    if (mazeGen == 2) {
        enemy1X = -11;
        enemy1Y = 1.5f;
        enemy1Z = 0;

        enemy2X = 15;
        enemy2Y = 1.5f;
        enemy2Z = 0;

        enemy3X = 15;
        enemy3Y = 1.5f;
        enemy3Z = -13;

        enemy4X = -17;
        enemy4Y = 1.5f;
        enemy4Z = 0;
    }

    enemy1LeftArmX = enemy1X - 0.6f;
    enemy1LeftArmY = enemy1Y + 0.8f;
    enemy1LeftArmZ = enemy1Z;

    enemy1LeftHandX = enemy1X - 0.6f;
    enemy1LeftHandY = enemy1Y + 0.3f;
    enemy1LeftHandZ = enemy1Z;

    enemy1RightArmX = enemy1X + 0.6f;
    enemy1RightArmY = enemy1Y + 0.8f;
    enemy1RightArmZ = enemy1Z;

    enemy1RightHandX = enemy1X + 0.6f;
    enemy1RightHandY = enemy1Y + 0.3f;
    enemy1RightHandZ = enemy1Z;

    enemy1LeftLegX = enemy1X - 0.25f;
    enemy1LeftLegY = enemy1Y - 0.4f;
    enemy1LeftLegZ = enemy1Z;

    enemy1RightLegX = enemy1X + 0.25f;
    enemy1RightLegY = enemy1Y - 0.4f;
    enemy1RightLegZ = enemy1Z;

    enemy2LeftArmX = enemy2X - 0.6f;
    enemy2LeftArmY = enemy2Y + 0.8f;
    enemy2LeftArmZ = enemy2Z;

    enemy2LeftHandX = enemy2X - 0.6f;
    enemy2LeftHandY = enemy2Y + 0.3f;
    enemy2LeftHandZ = enemy2Z;

    enemy2RightArmX = enemy2X + 0.6f;
    enemy2RightArmY = enemy2Y + 0.8f;
    enemy2RightArmZ = enemy2Z;

    enemy2RightHandX = enemy2X + 0.6f;
    enemy2RightHandY = enemy2Y + 0.3f;
    enemy2RightHandZ = enemy2Z;

    enemy2LeftLegX = enemy2X - 0.25f;
    enemy2LeftLegY = enemy2Y - 0.4f;
    enemy2LeftLegZ = enemy2Z;

    enemy2RightLegX = enemy2X + 0.25f;
    enemy2RightLegY = enemy2Y - 0.4f;
    enemy2RightLegZ = enemy2Z;

    enemy3LeftArmX = enemy3X - 0.6f;
    enemy3LeftArmY = enemy3Y + 0.8f;
    enemy3LeftArmZ = enemy3Z;

    enemy3LeftHandX = enemy3X - 0.6f;
    enemy3LeftHandY = enemy3Y + 0.3f;
    enemy3LeftHandZ = enemy3Z;

    enemy3RightArmX = enemy3X + 0.6f;
    enemy3RightArmY = enemy3Y + 0.8f;
    enemy3RightArmZ = enemy3Z;

    enemy3RightHandX = enemy3X + 0.6f;
    enemy3RightHandY = enemy3Y + 0.3f;
    enemy3RightHandZ = enemy3Z;

    enemy3LeftLegX = enemy3X - 0.25f;
    enemy3LeftLegY = enemy3Y - 0.4f;
    enemy3LeftLegZ = enemy3Z;

    enemy3RightLegX = enemy3X + 0.25f;
    enemy3RightLegY = enemy3Y - 0.4f;
    enemy3RightLegZ = enemy3Z;

    enemy4LeftArmX = enemy4X - 0.6f;
    enemy4LeftArmY = enemy4Y + 0.8f;
    enemy4LeftArmZ = enemy4Z;

    enemy4LeftHandX = enemy4X - 0.6f;
    enemy4LeftHandY = enemy4Y + 0.3f;
    enemy4LeftHandZ = enemy4Z;

    enemy4RightArmX = enemy4X + 0.6f;
    enemy4RightArmY = enemy4Y + 0.8f;
    enemy4RightArmZ = enemy4Z;

    enemy4RightHandX = enemy4X + 0.6f;
    enemy4RightHandY = enemy4Y + 0.3f;
    enemy4RightHandZ = enemy4Z;

    enemy4LeftLegX = enemy4X - 0.25f;
    enemy4LeftLegY = enemy4Y - 0.4f;
    enemy4LeftLegZ = enemy4Z;

    enemy4RightLegX = enemy4X + 0.25f;
    enemy4RightLegY = enemy4Y - 0.4f;
    enemy4RightLegZ = enemy4Z;

    cameraX = 0;
    cameraY = 6.5f;
    cameraZ = 3.5f;

    wall1X = playerX - 2;
    wall1Y = 0;
    wall1Z = playerZ;

    wall2X = playerX + 2;
    wall2Y = 0;
    wall2Z = playerZ;

    wall3X = playerX;
    wall3Y = 0;
    wall3Z = playerZ + 2;

    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    camera = new implemented::TemaCamera();
    camera->Set(glm::vec3(playerX, cameraY, playerZ + 3.5f), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));

    {
        // Border mesh
        Mesh* border = object2D::CreateSquare("border", glm::vec3(0, 0, 0), squareSide, glm::vec3(0, 0, 0), false);
        AddMeshToList(border);
    }

    {
        Mesh* redLine = object2D::CreateSquare("red_line", corner, squareSide, glm::vec3(1.00, 0.00, 0.17), true);
        AddMeshToList(redLine);
    }

    {
        Mesh* blueLine = object2D::CreateSquare("blue_line", corner, squareSide, glm::vec3(0.40, 0.50, 1.00), true);
        AddMeshToList(blueLine);
    }

    {
        Mesh* greenLine = object2D::CreateSquare("green_line", corner, squareSide, glm::vec3(0.47, 0.70, 0.00), true);
        AddMeshToList(greenLine);
    }

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
        Shader* shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a simple cube
    {
        CreateCube("cube", 2);
    }

    // Light & material properties
    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
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
   
    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    // Check if maze was completed
    if (sqrt(powfunc(goalX - playerX) + powfunc(goalZ - playerZ)) <= 0.8f) {

        if (mazeCleared == 0) {
            cout << "Maze cleared. You won!" << endl;
            cout << "Press ENTER to exit game." << endl;
        }

        mazeCleared = 1;
    }

    // Check if the allotted time was passed
    if (timeLeft <= 0) {
        cout << "GAME OVER!" << endl;
        exit(0);
    }

    // Only decrement time if player hasnt't finished the maze
    if (mazeCleared == 0) {
        timeLeft -= deltaTimeSeconds;
    }

    
    // Compute remaining stamina for a potential sprint
    if (mazeCleared == 0) {
        if (okToDepleteStamina == 1) {

            if (stamina > 0) {
                stamina -= deltaTimeSeconds * 9;
                staminaFrame -= (9 * 1.2f * deltaTimeSeconds) / 100;
            }
        }

        if (okToDepleteStamina == 0) {

            if (stamina < 100) {
                stamina += deltaTimeSeconds * 6;
                staminaFrame += (6 * 1.2f * deltaTimeSeconds) / 100;
            }
        }
    }

    // Border for time bar
    {
        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(-2.2f, 2);
        modelMatrix2D *= transform2D::Scale(1.202f, 0.2f);
        RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix2D);
    }

    // Timebar
    {

        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(-2.2f, 2);
        modelMatrix2D *= transform2D::Scale(timeFrame, 0.2f);
        RenderMesh2D(meshes["blue_line"], shaders["VertexColor"], modelMatrix2D);
    }

    if (mazeCleared == 0) {
        timeFrame -= (1.2f * deltaTimeSeconds) / 60;
    }

    // Border for healthbar
    {
        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(1, 2);
        modelMatrix2D *= transform2D::Scale(1.202f, 0.2f);
        RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix2D);
    }

    // Healthbar
    {
        
        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(1, 2);
        modelMatrix2D *= transform2D::Scale(healthFrame, 0.2f);
        RenderMesh2D(meshes["red_line"], shaders["VertexColor"], modelMatrix2D);
    }

    // Border for stamina bar
    {
        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(-0.6f, -0.5f);
        modelMatrix2D *= transform2D::Scale(1.202f, 0.2f);
        RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix2D);
    }

    // Stamina bar
    {

        glm::mat3 modelMatrix2D = glm::mat3(1);
        modelMatrix2D *= transform2D::Translate(-0.6f, -0.5f);
        modelMatrix2D *= transform2D::Scale(staminaFrame, 0.2f);
        RenderMesh2D(meshes["green_line"], shaders["VertexColor"], modelMatrix2D);
    }

    // Projectile
    {
        glm::mat4 modelMatrix = glm::mat4(1);

        if (okToShoot == 0) {
            projectileX = playerX;
            projectileY = playerY + 0.5f;
            projectileZ = playerZ;
        }

        modelMatrix *= transform3D::Translate(projectileX, projectileY, projectileZ);
        modelMatrix *= transform3D::RotateOY(angularStepOY);
        modelMatrix *= transform3D::Scale(0.4f, 0.4f, 0.4f);

        RenderMesh(meshes["sphere"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 0.50, 0.00));
    }

    // Generate player
    DrawPlayer(whichDirection, playerX, playerY, playerZ, leftArmX, leftArmY, leftArmZ, leftHandX, leftHandY, leftHandZ, rightArmX, 
        rightArmY, rightArmZ, rightHandX, rightHandY, rightHandZ, leftLegX, leftLegY, leftLegZ, rightLegX, rightLegY, rightLegZ, angularStepOY);

    // Generate Enemy 1
    DrawEnemy(whichDirection, enemy1X, enemy1Y, enemy1Z, enemy1LeftArmX, enemy1LeftArmY, enemy1LeftArmZ, enemy1LeftHandX, enemy1LeftHandY, enemy1LeftHandZ, 
        enemy1RightArmX, enemy1RightArmY, enemy1RightArmZ, enemy1RightHandX, enemy1RightHandY, enemy1RightHandZ, enemy1LeftLegX, enemy1LeftLegY, 
        enemy1LeftLegZ, enemy1RightLegX, enemy1RightLegY, enemy1RightLegZ, angularStepOY);

    // Generate Enemy 2
    DrawEnemy(whichDirection, enemy2X, enemy2Y, enemy2Z, enemy2LeftArmX, enemy2LeftArmY, enemy2LeftArmZ, enemy2LeftHandX, enemy2LeftHandY, enemy2LeftHandZ,
        enemy2RightArmX, enemy2RightArmY, enemy2RightArmZ, enemy2RightHandX, enemy2RightHandY, enemy2RightHandZ, enemy2LeftLegX, enemy2LeftLegY,
        enemy2LeftLegZ, enemy2RightLegX, enemy2RightLegY, enemy2RightLegZ, angularStepOY);

    // Generate Enemy 3
    DrawEnemy(whichDirection, enemy3X, enemy3Y, enemy3Z, enemy3LeftArmX, enemy3LeftArmY, enemy3LeftArmZ, enemy3LeftHandX, enemy3LeftHandY, enemy3LeftHandZ,
        enemy3RightArmX, enemy3RightArmY, enemy3RightArmZ, enemy3RightHandX, enemy3RightHandY, enemy3RightHandZ, enemy3LeftLegX, enemy3LeftLegY,
        enemy3LeftLegZ, enemy3RightLegX, enemy3RightLegY, enemy3RightLegZ, angularStepOY);

    // Generate Enemy 4
    DrawEnemy(whichDirection, enemy4X, enemy4Y, enemy4Z, enemy4LeftArmX, enemy4LeftArmY, enemy4LeftArmZ, enemy4LeftHandX, enemy4LeftHandY, enemy4LeftHandZ,
        enemy4RightArmX, enemy4RightArmY, enemy4RightArmZ, enemy4RightHandX, enemy4RightHandY, enemy4RightHandZ, enemy4LeftLegX, enemy4LeftLegY,
        enemy4LeftLegZ, enemy4RightLegX, enemy4RightLegY, enemy4RightLegZ, angularStepOY);

    //Generate behaviours for each enemy
    if (mazeGen == 0) {

        // Generate enemy 1 behaviour
        if (enemy1X >= -16 && switchEnemy1 == 0) {
            enemy1X -= deltaTimeSeconds * 2;
        }

        if (enemy1X < -16) {

            switchEnemy1 = 1;
        }

        if (enemy1X <= -12 && switchEnemy1 == 1) {

            enemy1X += deltaTimeSeconds * 2;
        }

        if (enemy1X > -12) {
            switchEnemy1 = 0;
        }

        // Generate enemy 2 behaviour
        if (enemy2X >= 8 && switchEnemy2 == 0) {
            enemy2X -= deltaTimeSeconds * 2;
        }

        if (enemy2X < 8) {

            switchEnemy2 = 1;
        }

        if (enemy2X <= 14 && switchEnemy2 == 1) {

            enemy2X += deltaTimeSeconds * 2;
        }

        if (enemy2X > 14) {
            switchEnemy2 = 0;
        }

        // Generate enemy 3 behaviour
        if (enemy3Z <= 12 && switchEnemy3 == 0) {
            enemy3Z += deltaTimeSeconds * 4;
        }

        if (enemy3Z > 12) {

            switchEnemy3 = 1;
        }

        if (enemy3Z >= 0 && switchEnemy3 == 1) {

            enemy3Z -= deltaTimeSeconds * 4;
        }

        if (enemy3Z < 0) {
            switchEnemy3 = 0;
        }

        // Generate enemy 4 behaviour
        if (enemy4X <= 8 && switchEnemy4 == 0) {
            enemy4X += deltaTimeSeconds * 2;
        }

        if (enemy4X > 8) {

            switchEnemy4 = 1;
        }

        if (enemy4X >= 0 && switchEnemy4 == 1) {

            enemy4X -= deltaTimeSeconds * 2;
        }

        if (enemy4X < 0) {
            switchEnemy4 = 0;
        }

    }

    if (mazeGen == 1) {

        // Generate enemy 1 behaviour
        if (enemy1X >= -4 && switchEnemy1 == 0) {
            enemy1X -= deltaTimeSeconds * 2;
        }

        if (enemy1X < -4) {

            switchEnemy1 = 1;
        }

        if (enemy1X <= 8 && switchEnemy1 == 1) {

            enemy1X += deltaTimeSeconds * 2;
        }

        if (enemy1X > 8) {
            switchEnemy1 = 0;
        }

        // Generate enemy 2 behaviour
        if (enemy2Z >= -10 && switchEnemy2 == 0) {
            enemy2Z -= deltaTimeSeconds * 4;
        }

        if (enemy2Z < -10) {

            switchEnemy2 = 1;
        }

        if (enemy2Z <= 12 && switchEnemy2 == 1) {

            enemy2Z += deltaTimeSeconds * 4;
        }

        if (enemy2Z > 12) {
            switchEnemy2 = 0;
        }

        // Generate enemy 3 behaviour
        if (enemy3Z >= -12 && switchEnemy3 == 0) {
            enemy3Z -= deltaTimeSeconds * 4;
        }

        if (enemy3Z < -12) {

            switchEnemy3 = 1;
        }

        if (enemy3Z <= 12 && switchEnemy3 == 1) {

            enemy3Z += deltaTimeSeconds * 4;
        }

        if (enemy3Z > 12) {
            switchEnemy3 = 0;
        }

        // Generate enemy 4 behaviour
        if (enemy4Z >= -12 && switchEnemy4 == 0) {
            enemy4Z -= deltaTimeSeconds * 4;
        }

        if (enemy4Z < -12) {

            switchEnemy4 = 1;
        }

        if (enemy4Z <= 10 && switchEnemy4 == 1) {

            enemy4Z += deltaTimeSeconds * 4;
        }

        if (enemy4Z > 10) {
            switchEnemy4 = 0;
        }
    }

    if (mazeGen == 2) {

        // Generate enemy 1 behaviour
        if (enemy1X <= 0 && switchEnemy1 == 0) {

            enemy1X += deltaTimeSeconds * 2;
        }

        if (enemy1X > 0) {
            switchEnemy1 = 1;
        }

        if (enemy1X >= -11 && switchEnemy1 == 1) {
            enemy1X -= deltaTimeSeconds * 2;
        }

        if (enemy1X < -11) {

            switchEnemy1 = 0;
        }

        // Generate enemy 2 behaviour
        if (enemy2X >= 2 && switchEnemy2 == 0) {
            enemy2X -= deltaTimeSeconds * 2;
        }

        if (enemy2X < 2) {

            switchEnemy2 = 1;
        }

        if (enemy2X <= 15 && switchEnemy2 == 1) {

            enemy2X += deltaTimeSeconds * 2;
        }

        if (enemy2X > 15) {
            switchEnemy2 = 0;
        }

        // Generate enemy 3 behaviour
        if (enemy3X >= 2 && switchEnemy3 == 0) {
            enemy3X -= deltaTimeSeconds * 2;
        }

        if (enemy3X < 2) {

            switchEnemy3 = 1;
        }

        if (enemy3X <= 15 && switchEnemy3 == 1) {

            enemy3X += deltaTimeSeconds * 2;
        }

        if (enemy3X > 15) {
            switchEnemy3 = 0;
        }

        // Generate enemy 4 behaviour
        if (enemy4Z <= 16 && switchEnemy4 == 0) {
            enemy4Z += deltaTimeSeconds * 4;
        }

        if (enemy4Z > 16) {

            switchEnemy4 = 1;
        }

        if (enemy4Z >= 0 && switchEnemy4 == 1) {

            enemy4Z -= deltaTimeSeconds * 4;
        }

        if (enemy4Z < 0) {
            switchEnemy4 = 0;
        }

        

    }

    // Generate chess-like tiles for the floor
    float nextTile = -24;

    for (int i = 0; i <= 24; i++) {

        if (i % 2 == 0) {

            // Spawn light tiles
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                for (float j = -24; j <= 24; j += 4) {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(j, -0.9f, nextTile);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 1.00, 0.70));
                }
            }

            // Spawn dark tiles
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                for (float j = -22; j <= 22; j += 4) {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(j, -0.9f, nextTile);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.13, 0.20));
                }
            }

            nextTile += 2;

        } 

        else {
            // Spawn light tiles
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                for (float j = -22; j <= 22; j += 4) {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(j, -0.9f, nextTile);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 1.00, 0.70));
                }
            }

            // Spawn dark tiles
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                for (float j = -24; j <= 24; j += 4) {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(j, -0.9f, nextTile);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.13, 0.20));
                }
            }

            nextTile += 2;

        }
    }


    if (mazeGen == 0) {

        // Spawn goal
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(goalX, goalY, goalZ);
            modelMatrix *= transform3D::Scale(1, 2.5f, 1);
            RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.60, 0.40));
        }

        // Spawn walls (left side of player)
        {
            float i = wall1Z;
            for (i = wall1Z; i >= -4; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(wall1X, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = wall1X;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            float j = wall1X;
            for (j = wall1X; j >= -8; j -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; i <= 12; i += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i -= 2;
            float deadEnd = -4;
            for (j = deadEnd; j <= 8; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (deadEnd = i; deadEnd >= -4; deadEnd -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(-4, wall1Y, deadEnd);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = -4;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i >= 6; i -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j >= 4; j -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j += 2;
            for (; i >= -12; i -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j <= 8; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }



        }

        // Spawn walls (right side of player)
        {

            float i = wall2Z;

            for (i = wall2Z; i >= -10; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(wall2X, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = wall2X;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            float j = wall2X;

            for (j = wall2X; j >= -22; j -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; i < 6; i += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; j <= -16; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i <= 18; i += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i -= 2;
            for (; j <= 14; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i >= 6; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j <= 18; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i >= -12; i -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j >= 14; j -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j += 2;
            for (; i >= -18; i -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }


            for (; i >= -8; i -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j >= -8; j -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }
        }

        // Spawn walls (the rest)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(wall3X, wall3Y, wall3Z);
            modelMatrix *= transform3D::Scale(1, 5, 1);
            RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

            if (done == 0) {
                obstaclesX[numberOfObstacles] = wall3X;
                obstaclesZ[numberOfObstacles] = wall3Z;
                numberOfObstacles++;
            }
        }
    }

    if (mazeGen == 1) {

        // Spawn goal
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(goalX, goalY, goalZ);
            modelMatrix *= transform3D::Scale(1, 2.5f, 1);
            RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.60, 0.40));
        }

        // Spawn walls (left side of player)
        {
            float i = wall1Z;
            float j = wall1X;
            
            for (i = wall1Z; i >= -24; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(wall1X, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = wall1X;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j <= -10; j += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i <= wall1Z - 6; i += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i -= 2;
            for (; j <= -6; j += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j += 4;
            float hallway1X = j - 6;
            float hallway1Z = i;

            float hallway2X = j;
            float hallway2Z = i;

            for (; j <= 10; j += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; hallway1Z >= -8; hallway1Z -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (; i >= -22; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; hallway1X <= 4; hallway1X += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            hallway1X -= 2;
            for (; hallway1Z >= -22; hallway1Z -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            for (; hallway1X <= 16; hallway1X += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }
        }

        // Spawn walls (right side of player)
        {
            float i = wall2Z;
            float j = wall2X;
            j += 2;

            for (i = wall2Z; i >= -18; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i = wall2Z;
            j = wall2X + 4;

            for (; j <= 16; j += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j -= 2;
            for (i = wall2Z; i >= -18; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }
        }

        // Spawn walls (the rest)
        {
            for (float i = wall3X; i <= wall3X + 2; i += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(i, wall3Y, wall3Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = i;
                    obstaclesZ[numberOfObstacles] = wall3Z;
                    numberOfObstacles++;
                }
            }

        }
    }

    if (mazeGen == 2) {

        // Spawn goal
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(goalX, goalY, goalZ);
            modelMatrix *= transform3D::Scale(1, 2.5f, 1);
            RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.60, 0.40));
        }

        // Spawn walls (left side of player)
        {
            float i = wall1Z;
            float j = wall1X;

            i -= 6;
            for (i = wall1Z; i >= 18; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(wall1X, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = wall1X;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            float hallway1X = wall1X;
            float hallway1Z = i + 2;

            i -= 4;

            float hallway2X = wall1X;
            float hallway2Z = i;

            for (; hallway1X >= -14; hallway1X -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            for (; hallway2X >= -8; hallway2X -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway2X, wall1Y, hallway2Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway2X;
                    obstaclesZ[numberOfObstacles] = hallway2Z;
                    numberOfObstacles++;
                }
            }

            hallway1X += 2;
            for (; hallway1Z >= -4; hallway1Z -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            hallway1Z -= 4;

            for (; hallway1X >= -20; hallway1X -= 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            hallway1X += 2;
            for (; hallway1Z <= 18; hallway1Z += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            hallway1Z -= 2;
            for (; hallway1X <= -16; hallway1X += 2) {

                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(hallway1X, wall1Y, hallway1Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = hallway1X;
                    obstaclesZ[numberOfObstacles] = hallway1Z;
                    numberOfObstacles++;
                }
            }

            for (; i >= -4; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(wall1X, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = wall1X;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            for (; i >= -10; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 8;
            j -= 6;

            for (; j >= -8; j -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            j += 2;
            for (; i >= -10; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j <= 16; j += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall1Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }
        }

        // Spawn walls (right side of player)
        {
            float i = wall2Z;
            float j = wall2X;
            j += 2;


            for (i = wall2Z; i >= -16; i -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }

            i += 2;
            for (; j >= -20; j -= 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(j, wall2Y, i);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = j;
                    obstaclesZ[numberOfObstacles] = i;
                    numberOfObstacles++;
                }
            }
        }

        // Spawn walls (the rest)
        {
            for (float i = wall3X; i <= wall3X + 2; i += 2) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(i, wall3Y, wall3Z);
                modelMatrix *= transform3D::Scale(1, 5, 1);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.60, 0.00, 0.00));

                if (done == 0) {
                    obstaclesX[numberOfObstacles] = i;
                    obstaclesZ[numberOfObstacles] = wall3Z;
                    numberOfObstacles++;
                }
            }
        }
    }

    // Only compute obstacle coordinates once
    done = 1;

    // Player - obstacles collision
    for (int i = 0; i < numberOfObstacles; i++) {

        if (sqrt(powfunc(obstaclesX[i] - playerX) + powfunc(obstaclesZ[i] - playerZ)) <= 1.95f) {

            okToMove = 1;
            break;
        } 
    }

    // Player - enemies collision

    // Player - Enemy 1 collision
    if (sqrt(powfunc(enemy1X - playerX) + powfunc(enemy1Z - playerZ)) <= 1.5f) {

        enemy1X = 999;
        enemy1Z = 999;
        okToShoot = 0;
        healthFrame -= 0.3f;
        health -= 25;

    }

    // Player - Enemy 2 collision
    if (sqrt(powfunc(enemy2X - playerX) + powfunc(enemy2Z - playerZ)) <= 1.5f) {

        enemy2X = 999;
        enemy2Z = 999;
        okToShoot = 0;
        healthFrame -= 0.3f;
        health -= 25;

    }

    // Player - Enemy 3 collision
    if (sqrt(powfunc(enemy3X - playerX) + powfunc(enemy3Z - playerZ)) <= 1.5f) {

        enemy3X = 999;
        enemy3Z = 999;
        okToShoot = 0;
        healthFrame -= 0.3f;
        health -= 25;

    }

    // Player - Enemy 4 collision
    if (sqrt(powfunc(enemy4X - playerX) + powfunc(enemy4Z - playerZ)) <= 1.5f) {

        enemy4X = 999;
        enemy4Z = 999;
        okToShoot = 0;
        healthFrame -= 0.3f;
        health -= 25;

    }

    // Shooting mechanic
    if (okToShoot == 1) {

        // Projectile - Enemy 1 collision
        if (sqrt(powfunc(enemy1X - projectileX) + powfunc(enemy1Z - projectileZ)) <= 1.5f) {

            enemy1X = 999;
            enemy1Z = 999;
            okToShoot = 0;

        }

        // Projectile - Enemy 2 collision
        if (sqrt(powfunc(enemy2X - projectileX) + powfunc(enemy2Z - projectileZ)) <= 1.5f) {

            enemy2X = 999;
            enemy2Z = 999;
            okToShoot = 0;

        }

        // Projectile - Enemy 3 collision
        if (sqrt(powfunc(enemy3X - projectileX) + powfunc(enemy3Z - projectileZ)) <= 1.5f) {

            enemy3X = 999;
            enemy3Z = 999;
            okToShoot = 0;

        }

        // Projectile - Enemy 4 collision
        if (sqrt(powfunc(enemy4X - projectileX) + powfunc(enemy4Z - projectileZ)) <= 1.5f) {

            enemy4X = 999;
            enemy4Z = 999;
            okToShoot = 0;

        }

        // Control trajectory of projectile
        if (whichDirection == 0) {

            playerXBackup0 = playerX;
            playerZBackup0 = playerZ;

            float maxRange = playerZBackup0 - 5;

            if (projectileZ >= maxRange) {
                projectileX = playerX;
                projectileZ -= deltaTimeSeconds * 7;
            }
            else {
                okToShoot = 0;
            } 
        }

        if (whichDirection == 1) {

            playerXBackup1 = playerX;
            playerZBackup1 = playerZ;

            float maxRange = playerXBackup1 - 5;

            if (projectileX >= maxRange) {
                projectileZ = playerZ;
                projectileX -= deltaTimeSeconds * 7;
            }
            else {
                okToShoot = 0;
            }
        }

        if (whichDirection == 2) {

            playerXBackup2 = playerX;
            playerZBackup2 = playerZ;

            float maxRange = playerZBackup2 + 5;

            if (projectileZ <= maxRange) {
                projectileX = playerX;
                projectileZ += deltaTimeSeconds * 7;
            }
            else {
                okToShoot = 0;
            }
        }

        if (whichDirection == 3) {

            playerXBackup3 = playerX;
            playerZBackup3 = playerZ;

            float maxRange = playerXBackup3 + 5;

            if (projectileX <= maxRange) {

                projectileZ = playerZ;
                projectileX += deltaTimeSeconds * 7;
            }
            else {
                okToShoot = 0;
            }
        }
    }

  
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
    GLint lightPos = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(lightPos, 1, glm::value_ptr(lightPosition));

    GLint shininessOfMaterial = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(shininessOfMaterial, materialShininess);

    GLint kdPos = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(kdPos, materialKd);

    GLint ksPos = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(ksPos, materialKs);

    GLint objectColor = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(objectColor, 1, glm::value_ptr(color));


    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    
    if (window->KeyHold(GLFW_KEY_W) && okToMove == 0 && mazeCleared == 0) {
        // TODO(student): Translate the camera forward
        camera->MoveForward(deltaTime * cameraSpeed);
        
        if (whichDirection == 0) {

            
            playerZ -= deltaTime * cameraSpeed;
            
        }

        if (whichDirection == 1) {
            playerX -= deltaTime * cameraSpeed;
        }

        if (whichDirection == 2) {
            playerZ += deltaTime * cameraSpeed;
        }

        if (whichDirection == 3) {
            playerX += deltaTime * cameraSpeed;
        }
    }

    if (window->KeyHold(GLFW_KEY_A) && okToMove == 0 && mazeCleared == 0) {
        // TODO(student): Translate the camera to the left
        camera->TranslateRight(-deltaTime * cameraSpeed);

        if (whichDirection == 0) {
            playerX -= deltaTime * cameraSpeed;
        }

        if (whichDirection == 1) {
            playerZ += deltaTime * cameraSpeed;
        }

        if (whichDirection == 2) {
            playerX += deltaTime * cameraSpeed;
        }

        if (whichDirection == 3) {
            playerZ -= deltaTime * cameraSpeed;
        }
    }

    if (window->KeyHold(GLFW_KEY_S) && okToMove == 0 && mazeCleared == 0) {
        // TODO(student): Translate the camera backward
        camera->MoveForward(-deltaTime * cameraSpeed);

        if (whichDirection == 0) {
            playerZ += deltaTime * cameraSpeed;
        }

        if (whichDirection == 1) {
            playerX += deltaTime * cameraSpeed;
        }

        if (whichDirection == 2) {
            playerZ -= deltaTime * cameraSpeed;
        }

        if (whichDirection == 3) {
            playerX -= deltaTime * cameraSpeed;
        }
    }

    if (window->KeyHold(GLFW_KEY_D) && okToMove == 0 && mazeCleared == 0) {
        // TODO(student): Translate the camera to the right
        camera->TranslateRight(deltaTime * cameraSpeed);

        if (whichDirection == 0) {
            playerX += deltaTime * cameraSpeed;
        }

        if (whichDirection == 1) {
            playerZ -= deltaTime * cameraSpeed;
        }

        if (whichDirection == 2) {
            playerX -= deltaTime * cameraSpeed;
        }

        if (whichDirection == 3) {
            playerZ += deltaTime * cameraSpeed;
        }
    } 

    if (window->KeyHold(GLFW_KEY_LEFT_SHIFT)) {

        if (stamina > 0) {
            cameraSpeed  = 8.0f;
        }

        else {
            cameraSpeed = 4.0f;
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event

    if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) {
        okToMove = 0;
    }

    if (key == GLFW_KEY_ENTER) {

        if (mazeCleared == 1) {
            exit(0);
        }
    }

    if (key == GLFW_KEY_LEFT_SHIFT) {

        okToDepleteStamina = 1;
    }

    if (key == GLFW_KEY_SPACE) {
        okToShoot = 1;
    }

    if (key == GLFW_KEY_Q) {
        angularStepOY += RADIANS(90);

        if (whichDirection < 3) {
            whichDirection++;
        }
        else {
            whichDirection = 0;
        }

        if (whichDirection == 0) {
            camera->Set(glm::vec3(playerX, cameraY, playerZ + 3.5f), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 1) {
            camera->Set(glm::vec3(playerX + 3.5f, cameraY, playerZ), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 2) {
            camera->Set(glm::vec3(playerX, cameraY, playerZ - 3.5f), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 3) {
            camera->Set(glm::vec3(playerX - 3.5f, cameraY, playerZ), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }   
    }

    if (key == GLFW_KEY_E) {
        angularStepOY -= RADIANS(90);

        if (whichDirection > 0) {
            whichDirection--;
        }

        else {
            whichDirection = 3;
        }

        if (whichDirection == 0) {
            camera->Set(glm::vec3(playerX, cameraY, playerZ + 3.5f), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 1) {
            camera->Set(glm::vec3(playerX + 3.5f, cameraY, playerZ), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 2) {
            camera->Set(glm::vec3(playerX, cameraY, playerZ - 3.5f), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        }

        if (whichDirection == 3) {
            camera->Set(glm::vec3(playerX - 3.5f, cameraY, playerZ), glm::vec3(playerX, 3, playerZ), glm::vec3(0, 1, 0));
        } 
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event 
    if (key == GLFW_KEY_LEFT_SHIFT) {
        cameraSpeed = 4.0f;
        okToDepleteStamina = 0;
    }

    
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    float sensivityOX = 0.005f;
    float sensivityOY = 0.005f;
  
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1 && okToShoot == 0) {
        okToShoot = 1;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
