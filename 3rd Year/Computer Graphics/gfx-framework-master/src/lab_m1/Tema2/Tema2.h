#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/lab_camera.h"

#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/object2D.h"



namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void CreateCube(const char* name, float length);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

   
        implemented::TemaCamera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.

        float fieldOfView;
        float left, right, bottom, top;
        float const ZNear = 15.f;
        float const ZFar = 1.f;
        bool orthoProjMode;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        void DrawPlayer(float whichDirection, float playerX, float playerY, float playerZ, float leftArmX, float leftArmY, float leftArmZ,
            float leftHandX, float leftHandY, float leftHandZ, float rightArmX, float rightArmY, float rightArmZ, 
            float rightHandX, float rightHandY, float rightHandZ, float leftLegX, float leftLegY, float leftLegZ, 
            float rightLegX, float rightLegY, float rightLegZ, float angularStepOY) {
            // Main body of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                modelMatrix *= transform3D::Translate(playerX, playerY + 0.6f, playerZ);
                modelMatrix *= transform3D::RotateOY(angularStepOY);
                modelMatrix *= transform3D::Scale(0.4f, 0.5f, 0.2f);

                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.53, 0.80));
            }

            // Head of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(playerX, playerY + 1.45f, playerZ);
                modelMatrix *= transform3D::Scale(0.3f, 0.3f, 0.3f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 0.83, 0.80));
            }

            // Left arm of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {
                    leftArmX = playerX - 0.6f;
                    leftArmY = playerY + 0.8f;
                    leftArmZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {
                    leftArmX = playerX;
                    leftArmY = playerY + 0.8f;
                    leftArmZ = playerZ + 0.6;
                }

                modelMatrix *= transform3D::Translate(leftArmX, leftArmY, leftArmZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.3f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.53, 0.80));
            }

            // Left hand of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {

                    leftHandX = playerX - 0.6f;
                    leftHandY = playerY + 0.3f;
                    leftHandZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {

                    leftHandX = playerX;
                    leftHandY = playerY + 0.3f;
                    leftHandZ = playerZ + 0.6f;
                }

                modelMatrix *= transform3D::Translate(leftHandX, leftHandY, leftHandZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.15f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 0.83, 0.80));
            }

            // Right arm of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {
                    rightArmX = playerX + 0.6f;
                    rightArmY = playerY + 0.8f;
                    rightArmZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {

                    rightArmX = playerX;
                    rightArmY = playerY + 0.8f;
                    rightArmZ = playerZ - 0.6f;
                }

                modelMatrix *= transform3D::Translate(rightArmX, rightArmY, rightArmZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.3f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.53, 0.80));
            }

            // Right hand of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {
                    rightHandX = playerX + 0.6f;
                    rightHandY = playerY + 0.3f;
                    rightHandZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {
                    rightHandX = playerX;
                    rightHandY = playerY + 0.3f;
                    rightHandZ = playerZ - 0.6f;
                }
                modelMatrix *= transform3D::Translate(rightHandX, rightHandY, rightHandZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.15f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(1.00, 0.83, 0.80));
            }

            // Left leg of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {

                    leftLegX = playerX - 0.25f;
                    leftLegY = playerY - 0.4f;
                    leftLegZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {

                    leftLegX = playerX;
                    leftLegY = playerY - 0.4f;
                    leftLegZ = playerZ + 0.25f;
                }

                modelMatrix *= transform3D::Translate(leftLegX, leftLegY, leftLegZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.4f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.00, 0.40));
            }

            // Right leg of the player
            {
                glm::mat4 modelMatrix = glm::mat4(1);

                if (whichDirection == 0 || whichDirection == 2) {

                    rightLegX = playerX + 0.25f;
                    rightLegY = playerY - 0.4f;
                    rightLegZ = playerZ;
                }

                if (whichDirection == 1 || whichDirection == 3) {

                    rightLegX = playerX;
                    rightLegY = playerY - 0.4f;
                    rightLegZ = playerZ - 0.25f;
                }
                modelMatrix *= transform3D::Translate(rightLegX, rightLegY, rightLegZ);
                modelMatrix *= transform3D::Scale(0.15f, 0.4f, 0.15f);
                RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.00, 0.40));
            }
        }

        void DrawEnemy(float whichDirection, float enemyX, float enemyY, float enemyZ, float enemyLeftArmX, float enemyLeftArmY, float enemyLeftArmZ,
            float enemyLeftHandX, float enemyLeftHandY, float enemyLeftHandZ, float enemyRightArmX, float enemyRightArmY, float enemyRightArmZ,
            float enemyRightHandX, float enemyRightHandY, float enemyRightHandZ, float enemyLeftLegX, float enemyLeftLegY, float enemyLeftLegZ,
            float enemyRightLegX, float enemyRightLegY, float enemyRightLegZ, float angularStepOY) {

                // Main body of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    modelMatrix *= transform3D::Translate(enemyX, enemyY + 0.6f, enemyZ);
                    modelMatrix *= transform3D::RotateOY(angularStepOY);
                    modelMatrix *= transform3D::Scale(0.4f, 0.5f, 0.2f);

                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.35, 0.00, 0.70));
                }

                // Head of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(enemyX, enemyY + 1.45f, enemyZ);
                    modelMatrix *= transform3D::Scale(0.3f, 0.3f, 0.3f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.07, 0.40, 0.00));
                }

                // Left arm of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {
                        enemyLeftArmX = enemyX - 0.6f;
                        enemyLeftArmY = enemyY + 0.8f;
                        enemyLeftArmZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {
                        enemyLeftArmX = enemyX;
                        enemyLeftArmY = enemyY + 0.8f;
                        enemyLeftArmZ = enemyZ + 0.6;
                    }

                    modelMatrix *= transform3D::Translate(enemyLeftArmX, enemyLeftArmY, enemyLeftArmZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.3f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.35, 0.00, 0.70));
                }

                // Left hand of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {

                        enemyLeftHandX = enemyX - 0.6f;
                        enemyLeftHandY = enemyY + 0.3f;
                        enemyLeftHandZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {

                        enemyLeftHandX = enemyX;
                        enemyLeftHandY = enemyY + 0.3f;
                        enemyLeftHandZ = enemyZ + 0.6f;
                    }

                    modelMatrix *= transform3D::Translate(enemyLeftHandX, enemyLeftHandY, enemyLeftHandZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.15f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.07, 0.40, 0.00));
                }

                // Right arm of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {
                        enemyRightArmX = enemyX + 0.6f;
                        enemyRightArmY = enemyY + 0.8f;
                        enemyRightArmZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {

                        enemyRightArmX = enemyX;
                        enemyRightArmY = enemyY + 0.8f;
                        enemyRightArmZ = enemyZ - 0.6f;
                    }

                    modelMatrix *= transform3D::Translate(enemyRightArmX, enemyRightArmY, enemyRightArmZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.3f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.35, 0.00, 0.70));
                }

                // Right hand of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {
                        enemyRightHandX = enemyX + 0.6f;
                        enemyRightHandY = enemyY + 0.3f;
                        enemyRightHandZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {
                        enemyRightHandX = enemyX;
                        enemyRightHandY = enemyY + 0.3f;
                        enemyRightHandZ = enemyZ - 0.6f;
                    }
                    modelMatrix *= transform3D::Translate(enemyRightHandX, enemyRightHandY, enemyRightHandZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.15f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.07, 0.40, 0.00));
                }

                // Left leg of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {

                        enemyLeftLegX = enemyX - 0.25f;
                        enemyLeftLegY = enemyY - 0.4f;
                        enemyLeftLegZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {

                        enemyLeftLegX = enemyX;
                        enemyLeftLegY = enemyY - 0.4f;
                        enemyLeftLegZ = enemyZ + 0.25f;
                    }

                    modelMatrix *= transform3D::Translate(enemyLeftLegX, enemyLeftLegY, enemyLeftLegZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.4f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.00, 0.40));
                }

                // Right leg of the enemy
                {
                    glm::mat4 modelMatrix = glm::mat4(1);

                    if (whichDirection == 0 || whichDirection == 2) {

                        enemyRightLegX = enemyX + 0.25f;
                        enemyRightLegY = enemyY - 0.4f;
                        enemyRightLegZ = enemyZ;
                    }

                    if (whichDirection == 1 || whichDirection == 3) {

                        enemyRightLegX = enemyX;
                        enemyRightLegY = enemyY - 0.4f;
                        enemyRightLegZ = enemyZ - 0.25f;
                    }
                    modelMatrix *= transform3D::Translate(enemyRightLegX, enemyRightLegY, enemyRightLegZ);
                    modelMatrix *= transform3D::Scale(0.15f, 0.4f, 0.15f);
                    RenderMesh(meshes["cube"], shaders["TemaShader"], modelMatrix, glm::vec3(0.00, 0.00, 0.40));
                }
        }

        

    };
}   // namespace m1
