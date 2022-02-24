#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Utils.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

void Tema1::spawnEnemies(float start, float end) {

    glm::ivec2 resolution = window->GetResolution();

    for (int i = start; i < end; i++) {

        enemies_x[i] = checkPlayerNearby(enemies_x[i], resolution.x, circle_x, i);
        enemies_y[i] = checkPlayerNearby(enemies_y[i], resolution.y, circle_y, i);
        leftArms_x[i] = enemies_x[i] - 50;
        leftArms_y[i] = enemies_y[i] + 60;
        rightArms_x[i] = enemies_x[i] + 50;
        rightArms_y[i] = enemies_y[i] + 60;
        speedEnemies[i] = (rand() % 400) + 250;
    }
}

void Tema1::spawnEnemiesPow(float start, float end) {

    glm::ivec2 resolution = window->GetResolution();

    for (int i = start; i < end; i++) {

        enemiesPow_x[i] = checkPlayerNearbyPow(enemiesPow_x[i], resolution.x, circle_x, i);
        enemiesPow_y[i] = checkPlayerNearbyPow(enemiesPow_y[i], resolution.y, circle_y, i);
        leftArmsPow_x[i] = enemiesPow_x[i] - 50;
        leftArmsPow_y[i] = enemiesPow_y[i] + 60;
        rightArmsPow_x[i] = enemiesPow_x[i] + 50;
        rightArmsPow_y[i] = enemiesPow_y[i] + 60;
        chanceToEvade[i] = rand() % 2;
        speedEnemiesPow[i] = (rand() % 400) + 250;
    }
}

Tema1::Tema1()
{
    okToShoot = 0;
    projectile_r = 1;
    projectile_g = 0;
    projectile_b = 0;
    score = 0;
    health = 3;
    maxHealth = 3;
    numberOfEnemies = 6;
    numberOfEnemiesPow = 3;
    nextWave = 0;
    upperBound = 6.56;
    lowerBound = -1.60;
    leftBound = -4.77;
    rightBound = 5.77;
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();

    // Initial spawning position for player meshes
    circle_x = resolution.x / 2;
    circle_y = resolution.y / 2;
    eye1_x = circle_x - 50.f;
    eye1_y = circle_y + 50.f;
    eye2_x = circle_x + 50.f;
    eye2_y = circle_y + 50.f;

    // Initial spawning position for projectile mesh
    projectile_x = circle_x;
    projectile_y = circle_y;

    // Initial spawning position for healthbar mesh
    healthbar_x = circle_x + 200;
    healthbar_y = circle_y - 300;

    spawnEnemies(0, numberOfEnemies);
    spawnEnemiesPow(0, numberOfEnemiesPow);

    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // Main body mesh
    Mesh* circle = object2D::CreateCircle("circle1", glm::vec3(1, 1, 0));
    AddMeshToList(circle);

    // Left eye mesh
    Mesh* circle2 = object2D::CreateCircle("circle2", glm::vec3(0, 0, 0));
    AddMeshToList(circle2);

    // Right eye mesh
    Mesh* circle3 = object2D::CreateCircle("circle3", glm::vec3(0, 0, 0));
    AddMeshToList(circle3);

    // Projectile mesh
    Mesh* projectile = object2D::CreateSquare("projectile", corner, squareSide, glm::vec3(projectile_r, projectile_g, projectile_b), true);
    AddMeshToList(projectile);

    // Obstacle mesh
    Mesh* obstacle = object2D::CreateSquare("obstacle", glm::vec3(0, 0, 0), squareSide, glm::vec3(0.00, 0.30, 0.10), true);
    AddMeshToList(obstacle);

    // Border mesh
    Mesh* border = object2D::CreateSquare("border", glm::vec3(0, 0, 0), squareSide, glm::vec3(0, 0, 0), false);
    AddMeshToList(border);

    // Line mesh
    Mesh* line = object2D::CreateSquare("line", glm::vec3(0, 0, 0), squareSide, glm::vec3(0, 0, 0), true);
    AddMeshToList(line);

    // Enemy mesh
    Mesh* enemy = object2D::CreateSquare("enemy", glm::vec3(0, 0, 0), squareSide, glm::vec3(1.67f, 0.15f, 0.31f), true);
    AddMeshToList(enemy);

    // Enemy arms mesh
    Mesh* enemyArms = object2D::CreateCircle("enemyArms", glm::vec3(0.67f, 0.15f, 0.31f));
    AddMeshToList(enemyArms);

    // HP resotre mesh
    Mesh* lifeline = object2D::CreateCircle("lifeline", glm::vec3(0.20, 0.60, 0));
    AddMeshToList(lifeline);

    // Line mesh (used for HP cross)
    Mesh* line2 = object2D::CreateSquare("line2", glm::vec3(0, 0, 0), squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(line2);

    // Soil mesh
    Mesh* soil = object2D::CreateSquare("soil", glm::vec3(0, 0, 0), squareSide, glm::vec3(0.20, 0.10, 0.00), true);
    AddMeshToList(soil);

    // Trees mesh
    Mesh* trees = object2D::CreateCircle("trees", glm::vec3(0.00, 0.30, 0.05));
    AddMeshToList(trees);

    // Powerful enemy mesh
    Mesh* enemyPow = object2D::CreateCircle("enemyPow", glm::vec3(0.27, 0.00, 0.40));
    AddMeshToList(enemyPow);
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5f, 0.5f, 0.5f), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    // Render all the meshes for the player
    DrawPlayer(modelMatrix, circle_x, circle_y, eye1_x, eye1_y, eye2_x, eye2_y);

    // Border
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(healthbar_x, healthbar_y);
    modelMatrix *= transform2D::Scale(3, 0.5f);
    RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix);

    // Healthbar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(healthbar_x, healthbar_y);
    modelMatrix *= transform2D::Scale(health, 0.5f);
    RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);

    nextWave += deltaTimeSeconds;

    // Spawn the next wave of enemies
    if (nextWave >= 10) {

        float start = numberOfEnemies;
        numberOfEnemies += 5;
        spawnEnemies(start, numberOfEnemies);

        float startPow = numberOfEnemiesPow;
        numberOfEnemiesPow += 3;
        spawnEnemiesPow(startPow, numberOfEnemiesPow);
        nextWave = 0;
       
    }

    // If health of player reaches zero
    if (health < 0.01f) {
        health = 0;
        cout << "Game Over!" << endl;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(555, 200);
        modelMatrix *= transform2D::Scale(1.7f, 0.25f);
        RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(630, 80);
        modelMatrix *= transform2D::Scale(0.25f, 2);
        RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);
    }

    // Enemies
    for (int i = 0; i < numberOfEnemies; i++) {
     
        DrawEnemy(modelMatrix, "enemyArms", enemies_x[i], enemies_y[i], leftArms_x[i], leftArms_y[i], rightArms_x[i], rightArms_y[i]);
    }

    for (int i = 0; i < numberOfEnemiesPow; i++) {

        DrawEnemy(modelMatrix, "enemyPow", enemiesPow_x[i], enemiesPow_y[i], leftArmsPow_x[i], leftArmsPow_y[i], rightArmsPow_x[i], rightArmsPow_y[i]);
    }

    for (int i = 0; i < numberOfEnemies; i++) {

        // Compute path from enemy to player
        radiansEnemy[i] = atan2((enemies_y[i] - circle_y), enemies_x[i] - circle_x);

        // Make enemies follow player
        if (sqrt(pow(enemies_x[i] - circle_x) + pow(enemies_y[i] - circle_y)) > 130.f) {
            enemies_y[i] += -sin(radiansEnemy[i]) * deltaTimeSeconds * speedEnemies[i];
            enemies_x[i] += -cos(radiansEnemy[i]) * deltaTimeSeconds * speedEnemies[i];
        }

        // Check for collision between player and enemy
        if (health >= 0.01f && sqrt(pow(enemies_x[i] - circle_x) + pow(enemies_y[i] - circle_y)) <= 130.f) {
            
            // Deal damage to player
            if (health >= 0.01f) {
                health -= deltaTimeSeconds * 20;
            }

            // Erase that enemy from existance (literally)
            float backup = numberOfEnemies;
            deleteElement(enemies_x, backup, i);
            deleteElement(enemies_y, backup, i);
            deleteElement(leftArms_x, backup, i);
            deleteElement(leftArms_y, backup, i);
            deleteElement(rightArms_x, backup, i);
            deleteElement(rightArms_y, backup, i);
            deleteRadians(radiansEnemy, backup, i);
            numberOfEnemies--;
        }

        // Render enemies' arms so that they always face the player
        leftArms_x[i] = -cos(radiansEnemy[i] + (37.5 * M_PI) / 180) * 65 + enemies_x[i];
        leftArms_y[i] = -sin(radiansEnemy[i] + (37.5 * M_PI) / 180) * 65 + enemies_y[i];

        rightArms_x[i] = -cos(radiansEnemy[i] - (37.5 * M_PI) / 180) * 65 + enemies_x[i];
        rightArms_y[i] = -sin(radiansEnemy[i] - (37.5 * M_PI) / 180) * 65 + enemies_y[i];
    }

    // Enemies pow
    for (int i = 0; i < numberOfEnemiesPow; i++) {

        // Compute path from enemy to player
        radiansEnemyPow[i] = atan2((enemiesPow_y[i] - circle_y), enemiesPow_x[i] - circle_x);

        // Make enemies follow player
        if (sqrt(pow(enemiesPow_x[i] - circle_x) + pow(enemiesPow_y[i] - circle_y)) > 130.f) {
            enemiesPow_y[i] += -sin(radiansEnemyPow[i]) * deltaTimeSeconds * speedEnemiesPow[i];
            enemiesPow_x[i] += -cos(radiansEnemyPow[i]) * deltaTimeSeconds * speedEnemiesPow[i];
        }

        // Check for collision between player and enemy
        if (health >= 0.01f && sqrt(pow(enemiesPow_x[i] - circle_x) + pow(enemiesPow_y[i] - circle_y)) <= 130.f) {

            // Deal damage to player
            if (health >= 0.01f) {
                health -= deltaTimeSeconds * 20;
            }

            // Erase that enemy from existance (literally)
            float backup = numberOfEnemiesPow;
            deleteElement(enemiesPow_x, backup, i);
            deleteElement(enemiesPow_y, backup, i);
            deleteElement(leftArmsPow_x, backup, i);
            deleteElement(leftArmsPow_y, backup, i);
            deleteElement(rightArmsPow_x, backup, i);
            deleteElement(rightArmsPow_y, backup, i);
            deleteRadians(radiansEnemyPow, backup, i);
            deleteChance(chanceToEvade, backup, i);
            numberOfEnemiesPow--;
        }

        // Render enemies' arms so that they always face the player
        leftArmsPow_x[i] = -cos(radiansEnemyPow[i] + (37.5 * M_PI) / 180) * 65 + enemiesPow_x[i];
        leftArmsPow_y[i] = -sin(radiansEnemyPow[i] + (37.5 * M_PI) / 180) * 65 + enemiesPow_y[i];

        rightArmsPow_x[i] = -cos(radiansEnemyPow[i] - (37.5 * M_PI) / 180) * 65 + enemiesPow_x[i];
        rightArmsPow_y[i] = -sin(radiansEnemyPow[i] - (37.5 * M_PI) / 180) * 65 + enemiesPow_y[i];
    }

    // Check if health restore point is available
    if (health < maxHealth && (logicSpace.x >= -1 && logicSpace.x <= 1) && (logicSpace.y >= -0.5f && logicSpace.y <= 1)) {
        health += deltaTimeSeconds * 2.5f;
    }

    // Minimap
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 9.5);
    modelMatrix *= transform2D::Scale(3.21, 1.81);
    RenderMesh2D(meshes["border"], shaders["VertexColor"], modelMatrix);

    // Render all the meshes for the projectile
    DrawProjectile(modelMatrix, projectile_x, projectile_y, currentAim);

    // Draw big screen viewport
    DrawScene(visMatrix);

    // Set screen size for minimap
    viewSpace = ViewportSpace(10, 10, resolution.x / 4, resolution.y / 4);
    SetViewportArea(viewSpace, glm::vec3(0.5f, 0.5f, 0.5f), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    // Draw minimap viewport
    DrawScene(visMatrix);

    // Shooting mechanic
    if (health >= 0.01f) {

            if (okToShoot == 1 && sqrt(pow(front_x - projectile_x) + pow(front_y - projectile_y)) <= 300.f) {
                projectile_y += -sin(currentAim) * deltaTimeSeconds * 1200;
                projectile_x += -cos(currentAim) * deltaTimeSeconds * 1200;
            }
            else
            {
                projectile_x = circle_x;
                projectile_y = circle_y;
                okToShoot = 0;
            }

            for (int i = 0; i < numberOfEnemies; i++) {
                if (okToShoot == 1 && sqrt(pow(enemies_x[i] - projectile_x) + pow(enemies_y[i] - projectile_y)) <= 70.f) {

                    // Erase that enemy from existance (literally)
                    float backup = numberOfEnemies;
                    deleteElement(enemies_x, backup, i);
                    deleteElement(enemies_y, backup, i);
                    deleteElement(leftArms_x, backup, i);
                    deleteElement(leftArms_y, backup, i);
                    deleteElement(rightArms_x, backup, i);
                    deleteElement(rightArms_y, backup, i);
                    deleteRadians(radiansEnemy, backup, i);
                    numberOfEnemies--;

                    score++;
                    cout << "Score: " << score << endl;
                    projectile_x = circle_x;
                    projectile_y = circle_y;
                    okToShoot = 0;
                }
            }

            for (int i = 0; i < numberOfEnemiesPow; i++) {

                // Some of the special enemies will attepmt to dodge bullets
                if (okToShoot == 1 && sqrt(pow(enemiesPow_x[i] - projectile_x) + pow(enemiesPow_y[i] - projectile_y)) <= 160.f) {

                    if (chanceToEvade[i] == 1) {
                        enemiesPow_y[i] += -sin(radiansEnemyPow[i] + (140 * M_PI) / 180) * deltaTimeSeconds * speedEnemiesPow[i] * 3;
                        enemiesPow_x[i] += -cos(radiansEnemyPow[i] + (140 * M_PI) / 180) * deltaTimeSeconds * speedEnemiesPow[i] * 3;
                    }
                }

                // If close enough all of them will perish
                if (okToShoot == 1 && sqrt(pow(enemiesPow_x[i] - projectile_x) + pow(enemiesPow_y[i] - projectile_y)) <= 70.f) {

                    float backup = numberOfEnemiesPow;
                    deleteElement(enemiesPow_x, backup, i);
                    deleteElement(enemiesPow_y, backup, i);
                    deleteElement(leftArmsPow_x, backup, i);
                    deleteElement(leftArmsPow_y, backup, i);
                    deleteElement(rightArmsPow_x, backup, i);
                    deleteElement(rightArmsPow_y, backup, i);
                    deleteRadians(radiansEnemyPow, backup, i);
                    deleteChance(chanceToEvade, backup, i);
                    numberOfEnemiesPow--;

                    score++;
                    cout << "Score: " << score << endl;
                    projectile_x = circle_x;
                    projectile_y = circle_y;
                    okToShoot = 0;  
                }
            }
    }
}


void Tema1::FrameEnd()
{
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
    glm::ivec2 resolution = window->GetResolution();

    // Lower border
    modelMatrix = visMatrix * transform2D::Translate(-10, -5);
    modelMatrix *= transform2D::Scale(0.5f, 0.05f);
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

    // Left border
    modelMatrix = visMatrix * transform2D::Translate(-8, -5);
    modelMatrix *= transform2D::Scale(0.05f, 0.5f);
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

    // Right border
    modelMatrix = visMatrix * transform2D::Translate(8, -5);
    modelMatrix *= transform2D::Scale(0.05f, 0.5f);
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

    //  Upper border
    modelMatrix = visMatrix * transform2D::Translate(-10, 9);
    modelMatrix *= transform2D::Scale(0.5f, 0.05f);
    RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);

    // Helthkit white cross
    modelMatrix = visMatrix * transform2D::Translate(2, 1.8f);
    modelMatrix *= transform2D::Scale(0.0005f, 0.005f);
    RenderMesh2D(meshes["line2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(1.82, 2);
    modelMatrix *= transform2D::Scale(0.004f, 0.0007f);
    RenderMesh2D(meshes["line2"], shaders["VertexColor"], modelMatrix);

    // Lifeline restore point
    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(2, 2);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["lifeline"], shaders["VertexColor"], modelMatrix);

    // Trees
    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(-0.7f, 2);
    modelMatrix *= transform2D::Scale(0.4f, 1.f);
    RenderMesh2D(meshes["trees"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transform2D::Translate(-0.7f, 4.5);
    modelMatrix *= transform2D::Scale(0.4f, 1.f);
    RenderMesh2D(meshes["trees"], shaders["VertexColor"], modelMatrix);

    // Obstacles
    modelMatrix = visMatrix * transform2D::Translate(-1, 1);
    modelMatrix *= transform2D::Scale(0.006f, 0.060f);
    RenderMesh2D(meshes["soil"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(3, 3);
    modelMatrix *= transform2D::Scale(0.5f, 0.02f);
    RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

    for (float i = 0; i < 10; i++) {
        modelMatrix = visMatrix * transform2D::Translate(i, 5);
        modelMatrix *= transform2D::Scale(0.005f, 0.005f);
        RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
    } 
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) { 
        if (health >= 0.01f) {

            if (logicSpace.y < upperBound) {
                logicSpace.y += deltaTime * 3;
            }

            for (int i = 0; i < numberOfEnemies; i++) {
                enemies_y[i] -= deltaTime * 300;
            }

            for (int i = 0; i < numberOfEnemiesPow; i++) {
                enemiesPow_y[i] -= deltaTime * 300;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_A)) { 
    
        if (health >= 0.01f) {

            if (logicSpace.x > leftBound) {
                logicSpace.x -= deltaTime * 2;
            }

            for (int i = 0; i < numberOfEnemies; i++) {
                enemies_x[i] += deltaTime * 300;
            }

            for (int i = 0; i < numberOfEnemiesPow; i++) {
                enemiesPow_x[i] += deltaTime * 300;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) { 
        
        if (health >= 0.01f) {

            if (logicSpace.y > lowerBound) {
                logicSpace.y -= deltaTime * 3;
            }

            for (int i = 0; i < numberOfEnemies; i++) {
                enemies_y[i] += deltaTime * 300;
            }

            for (int i = 0; i < numberOfEnemiesPow; i++) {
                enemiesPow_y[i] += deltaTime * 300;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_D)) { 
      
        if (health >= 0.01f) {

            if (logicSpace.x < rightBound) {
                logicSpace.x += deltaTime * 2;
            }
            for (int i = 0; i < numberOfEnemies; i++) {
                enemies_x[i] -= deltaTime * 300;
            }

            for (int i = 0; i < numberOfEnemiesPow; i++) {
                enemiesPow_x[i] -= deltaTime * 300;
            }
        }
    }

    if (window->KeyHold(GLFW_KEY_K)) {

        if (health >= 0.01f) {
            health -= deltaTime * 2.5f;
        }

    }

    if (window->KeyHold(GLFW_KEY_Z))
    {
        GLfloat zoomAmount = deltaTime * 4.f;

        logicSpace.width += zoomAmount;
        logicSpace.height += zoomAmount;
    }
    if (window->KeyHold(GLFW_KEY_X))
    {
        GLfloat zoomAmount = deltaTime * 4.f;

        logicSpace.width -= zoomAmount;
        logicSpace.height -= zoomAmount;
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE && okToShoot == 0) {
        okToShoot = 1;
        currentAim = radians;
    }
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
   
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (health >= 0.01f) {
        radians = atan2(-(circle_y - mouseY), circle_x - mouseX);

        front_x = -cos(radians) * 200 + circle_x;
        front_y = -sin(radians) * 200 + circle_y;

        eye1_x = -cos(radians + (37.5 * M_PI) / 180) * 65 + circle_x;
        eye1_y = -sin(radians + (37.5 * M_PI) / 180) * 65 + circle_y;

        eye2_x = -cos(radians - (37.5 * M_PI) / 180) * 65 + circle_x;
        eye2_y = -sin(radians - (37.5 * M_PI) / 180) * 65 + circle_y;
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
   
    if (button == 1 && okToShoot == 0) {
        okToShoot = 1;
        currentAim = radians;
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
    glm::ivec2 resolution = window->GetResolution();

    circle_x = resolution.x / 2;
    circle_y = resolution.y / 2;
    eye1_x = circle_x - 50.f;
    eye1_y = circle_y + 50.f;
    eye2_x = circle_x + 50.f;
    eye2_y = circle_y + 50.f;
    projectile_x = circle_x - 25;
    projectile_y = circle_y;
    healthbar_x = circle_x + 200;
    healthbar_y = circle_y - 300;
}
