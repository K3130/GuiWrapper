#include "guiwrapper.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void error_callback( int error, const char *msg ) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
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

    m_window = glfwCreateWindow(aWindowWidth, aWindowHeight, aWindowTitle, NULL, NULL);

    GLFWimage icon[1];
    icon[0].pixels = stbi_load("resources/icon.png", &icon[0].width, &icon[0].height, 0, 4);
    glfwSetWindowIcon(m_window, 1, icon);
    stbi_image_free(icon[0].pixels);

    if (!m_window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);

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
    bool f_open = true;
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //...Base code
        for (size_t i = 0; i < m_frames.size(); i++)
        {
            m_frames[i].Show();
            m_frames[i].End();
        }   
        //...




        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.22f, 0.26f, 0.37f, 1.00f);
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
