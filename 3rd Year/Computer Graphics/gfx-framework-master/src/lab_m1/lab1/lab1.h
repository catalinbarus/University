#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
     public:
        Lab1();
        ~Lab1();

        void Init() override;

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

        // TODO(student): Class variables go here

        // Colour componenents
        float red_colour;
        float green_colour;
        float blue_colour;
        float alpha_value;

        // Base coordinates for the teapot
        float tea_x, tea_y, tea_z;

        // Base coordinates for the archer
        float archer_x, archer_y, archer_z;

        // Used for returning archer after jumping
        float y_backup;

        // Used for cycling through models
        int switchModel;
    };
}   // namespace m1
