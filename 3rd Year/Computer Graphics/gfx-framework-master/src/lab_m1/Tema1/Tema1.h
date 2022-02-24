#pragma once

#include "components/simple_scene.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "lab_m1/Tema1/transform2D.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);
        void spawnEnemies(float start, float end);
        void spawnEnemiesPow(float start, float end);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

        float cx, cy;
        glm::mat3 modelMatrix, visMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        float upperBound;
        float lowerBound;
        float leftBound;
        float rightBound;
        int score;
        float nextWave;
        float health;
        float maxHealth;
        float numberOfEnemies;
        float numberOfEnemiesPow;
        float front_x, front_y;
        double radians;
        double currentAim;
        float circle_x;
        float circle_y;
        float eye1_x;
        float eye1_y;
        float eye2_x;
        float eye2_y;
        int okToShoot;
        float projectile_x;
        float projectile_y;
        float projectile_r;
        float projectile_g;
        float projectile_b;
        float healthbar_x;
        float healthbar_y;
        float enemy_x;
        float enemy_y;
        float leftArm_x;
        float leftArm_y;
        float rightArm_x;
        float rightArm_y;

        float enemies_x[100];
        float enemies_y[100];
        float leftArms_x[100];
        float leftArms_y[100];
        float rightArms_x[100];
        float rightArms_y[100];
        double radiansEnemy[100];
        float speedEnemies[100];

        float enemiesPow_x[100];
        float enemiesPow_y[100];
        float leftArmsPow_x[100];
        float leftArmsPow_y[100];
        float rightArmsPow_x[100];
        float rightArmsPow_y[100];
        double radiansEnemyPow[100];
        float speedEnemiesPow[100];
        int chanceToEvade[100];
        ViewportSpace viewSpace;
        LogicSpace logicSpace;



        // TODO(student): If you need any other class variables, define them here.
        void DrawPlayer(glm::mat3 modelMatrix, float circle_x, float circle_y, float eye1_x, float eye1_y, float eye2_x, float eye2_y) {
            // Black border left eye
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(eye1_x, eye1_y);
            modelMatrix *= transform2D::Scale(14, 14);
            RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

            // Black border left eye
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(eye2_x, eye2_y);
            modelMatrix *= transform2D::Scale(14, 14);
            RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

            // Left eye
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(eye1_x, eye1_y);
            modelMatrix *= transform2D::Scale(20, 20);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

            // Right eye
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(eye2_x, eye2_y);
            modelMatrix *= transform2D::Scale(20, 20);
            RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix);

            // Main body
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(circle_x, circle_y);
            modelMatrix *= transform2D::Scale(60, 60);
            RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

            // Black border main body
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(circle_x, circle_y);
            modelMatrix *= transform2D::Scale(65, 65);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);
        }

        void DrawProjectile(glm::mat3 modelMatrix, float projectile_x, float projectile_y, float currentAim) {
            // Projectile (rendered behind player)
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(projectile_x, projectile_y);
            modelMatrix *= transform2D::Rotate(currentAim);
            modelMatrix *= transform2D::Scale(0.45f, 0.45f);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }

        void DrawEnemy(glm::mat3 modelMatrix, const std::string& name, float enemy_x, float enemy_y, float leftArm_x,
            float leftArm_y, float rightArm_x, float rightArm_y) {

            // Left arm
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(leftArm_x, leftArm_y);
            modelMatrix *= transform2D::Scale(25, 25);
            RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(leftArm_x, leftArm_y);
            modelMatrix *= transform2D::Scale(30, 30);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

            // Right arm
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(rightArm_x, rightArm_y);
            modelMatrix *= transform2D::Scale(25, 25);
            RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(rightArm_x, rightArm_y);
            modelMatrix *= transform2D::Scale(30, 30);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

            // Main body
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy_x, enemy_y);
            modelMatrix *= transform2D::Scale(65, 65);
            RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy_x, enemy_y);
            modelMatrix *= transform2D::Scale(70, 70);
            RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

        }


    };
}   // namespace m1
