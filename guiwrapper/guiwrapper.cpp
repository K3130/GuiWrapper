#include "guiwrapper.h"

void error_callback( int error, const char *msg ) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

void testFunc() {
    ImGui::Begin("111");
}

GuiWrapper::GuiWrapper() : m_window(nullptr)
{

}

bool GuiWrapper::Init(int aWindowWidth, int aWindowHeight, const char *aWindowTitle)
{
    glfwSetErrorCallback(error_callback );
    // Initialize GLFW
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);

    if (!m_window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(m_window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return 0;
}

void GuiWrapper::Render()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //...Base code
        Frame f(0, 0, 700, 700, "First", nullptr, ImGuiWindowFlags_None | ImGuiWindowFlags_NoMove);
        //f.SetText("this text");
        //f.SetButton(500, 500, 30, 100, "button", testFunc);

        //Frame f2(1000, 500, 200, 200, "Second", nullptr, ImGuiWindowFlags_None);
        //f2.SetText("это текст");


        //---
        //ImGui::End();
        //...

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }
}

void GuiWrapper::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}
