#ifndef GUIWRAPPER_H
#define GUIWRAPPER_H

//---Includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
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

    void SetMenuInMenuBar(const char* aText, const std::vector<GuiWrapperModules::MenuItem> aItem) {
        m_menubar.push_back({ aText, aItem });
    }

    void SetInputText(const GuiWrapperModules::InputText aInText) {
        m_inputText.push_back(aInText);
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
            ImGui::SetNextWindowBgAlpha(1); //off transparent
            ImGui::Begin(m_title, m_isOpen, m_flags);
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowMenuButtonPosition = ImGuiDir_Right;

            //--Collapsed
            if(ImGui::IsWindowCollapsed())
            {
                glfwIconifyWindow(m_window);
                ImGui::SetWindowCollapsed(false);
            }
            //---

            //---Drag window by title only
            if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                if(ImGui::IsItemHovered())
                {
                    buttonEvent = 1;
                }
            } else
                buttonEvent = 0;
            //---

            //---Resize window
            if (WindowResized() && !ImGui::IsWindowCollapsed())
            {
                ImVec2 size = ImGui::GetWindowSize();
                glfwSetWindowSize(m_window, size.x, size.y);
                ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);

            }
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

            //---Show menu bar
            for (size_t i = 0; i < m_menubar.size(); i++)
            {
                if(ImGui::BeginMenuBar())
                {
                    if(ImGui::BeginMenu(m_menubar[i].m_t))
                    {
                        for (size_t j = 0; j < m_menubar[i].m_menuitem.size(); j++) {
                            bool isPressed = false;
                            ImGui::MenuItem(m_menubar[i].m_menuitem[j].m_lable,
                                            NULL,
                                            &isPressed);
                            if (isPressed)
                                m_menubar[i].m_menuitem[j].m_f();
                            ImGui::Separator();
                        }

                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }
            }
            //---

            //---Show input texts
            for (size_t i = 0; i < m_inputText.size(); i++)
            {
                ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                ImGui::SetCursorPos(ImVec2(m_inputText[i].m_x, m_inputText[i].m_y));
                ImGui::BeginChildFrame(ImGui::GetID("##Edit_Window_Container"),
                                       ImVec2(m_inputText[i].m_x, m_inputText[i].m_y),
                                       ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
                ImGui::InputTextMultiline(m_inputText[i].m_lable,
                                          m_inputText[i].m_bufer,
                                          ImVec2(m_inputText[i].m_w, m_inputText[i].m_h),
                                          ImGuiInputTextFlags_None);

                ImGui::EndChildFrame();
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

    bool WindowResized() {
        ImVec2 size = ImGui::GetWindowSize();
        if ((int)size.x != m_width || (int)size.y != m_height)
        {
            return true;
        }
        return false;
    }

private:
    GLFWwindow* m_window;
    float m_x; float m_y; float m_width; float m_height;
    const char* m_title;
    bool* m_isOpen;
    ImGuiWindowFlags m_flags;
    std::vector<GuiWrapperModules::Button> m_buttons;
    std::vector<GuiWrapperModules::Text> m_texts;
    std::vector<GuiWrapperModules::Menu> m_menubar;
    std::vector<GuiWrapperModules::InputText> m_inputText;
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
