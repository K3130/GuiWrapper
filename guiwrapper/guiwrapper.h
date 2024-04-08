#ifndef GUIWRAPPER_H
#define GUIWRAPPER_H

//---Includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw3.h"
#include <iostream>
#include <vector>
#include "modules.h"

//---

struct Frame
{
    Frame(float aX, float aY, float aWidth, float aHeight,
          const char* aTitle, bool* aOpen, ImGuiWindowFlags aFlags)
        : m_x(aX), m_y(aY), m_width(aWidth), m_height(aHeight), m_title(aTitle), m_isOpen(aOpen), m_flags(aFlags) {


    }

    void SetText(float aX, float aY, const char* aText) {
        m_texts.push_back(GuiWrapperModules::Text {aX, aY, aText}); }

    void SetButton(float aX, float aY, float aWidth, float aHeight, const char* aText, void(aFunc)()) {
        m_buttons.push_back(GuiWrapperModules::Button {aX, aY, aWidth, aHeight, aText, aFunc});
    }

    void End() { ImGui::End(); }

    void Show()
    {
        ImGui::SetNextWindowPos(ImVec2(m_x, m_y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(m_width, m_height), ImGuiCond_FirstUseEver);

        if (m_isOpen && *m_isOpen == true)
        {
            ImGui::Begin(m_title, m_isOpen, m_flags);

            //Show buttons
            for (size_t i = 0; i < m_buttons.size(); i++) {
                ImGui::SetCursorPos(ImVec2(m_buttons[i].m_x, m_buttons[i].m_y));
                if (ImGui::Button(m_buttons[i].m_t, ImVec2(m_buttons[i].m_w, m_buttons[i].m_h)))
                    m_buttons[i].m_f();
            }
            //Show texts
            for (size_t i = 0; i < m_texts.size(); i++) {
                ImGui::SetCursorPos(ImVec2(m_texts[i].m_x, m_texts[i].m_y));
                ImGui::Text("%s", m_texts[i].m_t);
            }
        }

    }

private:
    float m_x; float m_y; float m_width; float m_height;
    const char* m_title;
    bool* m_isOpen;
    ImGuiWindowFlags m_flags;
    std::vector<GuiWrapperModules::Button> m_buttons;
    std::vector<GuiWrapperModules::Text> m_texts;
};

class GuiWrapper
{
public:
    GuiWrapper();
    bool Init(int aWindowWidth, int aWindowHeight, const char* aWindowTitle);
    void Render();
    void Destroy();
    void SetFrame(const Frame &aFrame) { m_frames.push_back(aFrame); }
private:
    GLFWwindow* m_window;
    ImFont* m_font;
    std::vector<Frame> m_frames;
};

#endif // GUIWRAPPER_H
