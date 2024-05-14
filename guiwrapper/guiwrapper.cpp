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

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Hide decoration window
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Transparent
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

    m_window = glfwCreateWindow(aWindowWidth, aWindowHeight, aWindowTitle, NULL, NULL);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);

    // Set window center
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int screenWidth = mode->width;
    int screenHeight = mode->height;
    glfwSetWindowPos(m_window, (screenWidth - aWindowWidth) / 2, (screenHeight - aWindowHeight) / 2);
    //---

    // Set icon
    GLFWimage icon[1];
    icon[0].pixels = stbi_load("resources/icon.png", &icon[0].width, &icon[0].height, 0, 4);
    glfwSetWindowIcon(m_window, 1, icon);
    stbi_image_free(icon[0].pixels);
    //--

    if (!m_window) {
        glfwTerminate();
        return 1;
    }


    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = &ImGui::GetIO(); (void)m_io;
    m_io->ConfigWindowsMoveFromTitleBarOnly = true;
    m_io->ConfigWindowsResizeFromEdges = false;
    m_font = m_io->Fonts->AddFontFromFileTTF("resources/roboto.ttf",
                                          20.0f, nullptr,
                                             m_io->Fonts->GetGlyphRangesCyrillic());
    //Set min window size
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(640, 480));



    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    return 0;
}

void GuiWrapper::Render(const std::function<void()>aFunc)
{
    bool f_open = true;
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Rounding
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);




        //...Base code
        for (size_t i = 0; i < m_frames.size(); i++)
        {
            m_frames[i].Show();
            m_frames[i].End();
        }   
        //...


        //... Arbitrary function
        if(aFunc != nullptr)
            aFunc();
        //


        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        //---

        ImGui::ShowDemoWindow();




        ImGui::Render();
        int display_w, display_h;

        glfwGetFramebufferSize(m_window, &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);

        //glClearColor(0.22f, 0.26f, 0.37f, 1.00f);
        glClearColor(0, 0, 0, 0);

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void GuiWrapper::Destroy()
{
    ImGui::DestroyContext();
    glfwSetWindowShouldClose(m_window, true);
    exit(0);
}


