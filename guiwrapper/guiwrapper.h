#ifndef GUIWRAPPER_H
#define GUIWRAPPER_H

//---Includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw3.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <chrono>
#include <thread>
#include "modules.h"
//---

// --- Для передвижения окна ---
static int cp_x;
static int cp_y;
static int offset_cpx;
static int offset_cpy;
static int w_posx;
static int w_posy;
static int buttonEvent;

static void cursor_position_callback(GLFWwindow* window, double x, double y){
    if (buttonEvent == 1) {
        offset_cpx = x - cp_x;
        offset_cpy = y - cp_y;
    }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        buttonEvent = 1;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        cp_x = std::floor(x);
        cp_y = std::floor(y);
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        buttonEvent = 0;
        cp_x = 0;
        cp_y = 0;
    }
}
// ---


struct Frame
{
    Frame(GLFWwindow* aWindow, float aX, float aY, float aWidth, float aHeight,
          const char* aTitle, bool* aOpen, ImGuiWindowFlags aFlags)
        : m_window(aWindow), m_x(aX), m_y(aY), m_width(aWidth), m_height(aHeight), m_title(aTitle), m_isOpen(aOpen), m_flags(aFlags) {
    }

    void SetText(float aX, float aY, const char* aText) {
        m_texts.push_back(GuiWrapperModules::Text {aX, aY, aText}); }

    void SetButton(float aX, float aY, float aWidth, float aHeight, const char* aText, const std::function<void()>aFunc) {
        m_buttons.push_back(GuiWrapperModules::Button {aX, aY, aWidth, aHeight, aText, aFunc});
    }


    void End() { ImGui::End(); }

    void Show()
    {
        ImGui::SetNextWindowPos(ImVec2(m_x, m_y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(m_width, m_height), ImGuiCond_FirstUseEver);

        UpdateWindowDrugging();


        if (m_isOpen && *m_isOpen == true)
        {

            //---Main window
            ImGui::Begin(m_title, m_isOpen, m_flags);

            //---Drag window by title only
            if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                buttonEvent = 1;
            } else
                buttonEvent = 0;
            //---

            //---Show buttons
            for (size_t i = 0; i < m_buttons.size(); i++) {
                ImGui::SetCursorPos(ImVec2(m_buttons[i].m_x, m_buttons[i].m_y));
                if (ImGui::Button(m_buttons[i].m_t, ImVec2(m_buttons[i].m_w, m_buttons[i].m_h)))
                    m_buttons[i].m_f();
            }
            //---

            //---Show texts
            for (size_t i = 0; i < m_texts.size(); i++) {
                ImGui::SetCursorPos(ImVec2(m_texts[i].m_x, m_texts[i].m_y));
                ImGui::Text("%s", m_texts[i].m_t);
            }
            //---



        }

    }
private:
    void UpdateWindowDrugging() {
        glfwGetWindowPos(m_window, &w_posx, &w_posy);
        glfwSetWindowPos(m_window, w_posx + offset_cpx, w_posy + offset_cpy);
        offset_cpx = 0;
        offset_cpy = 0;
        cp_x += offset_cpx;
        cp_y += offset_cpy;


    }

private:
    GLFWwindow* m_window;
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
    void Render(const std::function<void()>aFunc);
    void Destroy();
    void SetFrame(const Frame &aFrame) { m_frames.push_back(aFrame); }
    GLFWwindow* GetWindowPoint() { return m_window; }
private:
    void UpdateWindowDrugging();
private:
    GLFWwindow* m_window;
    ImFont* m_font;
    ImGuiIO* m_io;
    std::vector<Frame> m_frames;
};

#endif // GUIWRAPPER_H
