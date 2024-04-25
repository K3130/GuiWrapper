#include "guiwrapper/guiwrapper.h"

void testFunc() {
    ImGui::Begin("111");
}

int main(int argc, char** argv) {

    GuiWrapper w;
    w.Init(800, 800, "Главное окно.");

    bool f_open = true;
    Frame f(w.GetWindowPoint(), 0, 0, 800, 800, u8"Фрейм", &f_open,
                  ImGuiWindowFlags_None
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_MenuBar);
    f.SetButton(500, 500, 100, 40, u8"кнопка", testFunc);
    f.SetText(100, 100, u8"Обычный текст.");



    std::vector<GuiWrapperModules::MenuItem> FileMenu { {"New", NULL, false},
                                                  {"Open", NULL, false},
                                                  {"Close", NULL, false}};
    f.SetMenuInMenuBar("File", FileMenu);

    std::vector<GuiWrapperModules::MenuItem> HelpMenu { {"How To", NULL, false},
                                                      {"Как помочь?", NULL, false},
                                                      {"О проекте.", NULL, false}};
    f.SetMenuInMenuBar("Help", HelpMenu);

    w.SetFrame(f);


    //Если закрыть фрейм,выполняется выход из программы
    w.Render([&](){if (!f_open) {w.Destroy();} } );



    w.Destroy();
    return 0;
}
