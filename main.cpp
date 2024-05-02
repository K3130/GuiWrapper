#include "guiwrapper/guiwrapper.h"

void testButton() {
    std::cout << "Button presed" << std::endl;
}

void testMenuItem() {
    std::cout << "Menu item pressed" << std::endl;
}



int main(int argc, char** argv) {

    GuiWrapper w;
    w.Init(800, 800, "Главное окно.");

    bool f_open = true;
    Frame f(w.GetWindowPoint(), 0, 0, 800, 800, u8"Фрейм", &f_open,
                  ImGuiWindowFlags_None
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_MenuBar);
    f.SetButton(500, 500, 100, 40, u8"кнопка", testButton);
    f.SetText(100, 100, u8"Обычный текст.");



    std::vector<GuiWrapperModules::MenuItem> FileMenu { {"New", testMenuItem},
                                                  {"Open", nullptr},
                                                  {"Close", nullptr}};
    f.SetMenuInMenuBar("File", FileMenu);


    std::vector<GuiWrapperModules::MenuItem> HelpMenu { {"How To", nullptr},
                                                      {"Как помочь?", nullptr},
                                                      {"О проекте.", nullptr}};
    f.SetMenuInMenuBar("Help", HelpMenu);

    w.SetFrame(f);


    //Если закрыть фрейм,выполняется выход из программы
    w.Render([&](){if (!f_open) {w.Destroy();} } );



    w.Destroy();
    return 0;
}
