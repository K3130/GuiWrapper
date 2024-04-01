#ifndef GUIWRAPPER_H
#define GUIWRAPPER_H

//---Includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw3.h"
#include <iostream>


//---

struct Frame
{
    Frame(float aX, float aY, float aWidth, float aHeight,
          const char* aTitle, bool* aOpen, ImGuiWindowFlags aFlags)
        : m_title(aTitle), m_isOpen(aOpen), m_flags(aFlags) {

        ImGui::SetNextWindowPos(ImVec2(aX, aY), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(aWidth, aHeight));
        ImGui::Begin(m_title, m_isOpen, m_flags);
    }

    void SetText(const std::string& aText) { ImGui::Text(aText.c_str()); }

    void SetButton(float aX, float aY, float aWidth, float aHeight, const std::string& aText, void(aFunc)())
    {
        ImGui::SetCursorPos(ImVec2(aX, aY));
        if (ImGui::Button(aText.c_str(), ImVec2(aWidth, aHeight))){

            aFunc();
        }
    }

private:
    const char* m_title;
    bool* m_isOpen;
    ImGuiWindowFlags m_flags;
};

class GuiWrapper
{
public:
    GuiWrapper();
    bool Init(int aWindowWidth, int aWindowHeight, const char* aWindowTitle);
    void Render();
    void Destroy();
private:
    GLFWwindow* m_window;
};

#endif // GUIWRAPPER_H
