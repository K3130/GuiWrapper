#include "guiwrapper/guiwrapper.h"

//Пример использования


//void testButton() {
//    std::cout << "Button presed" << std::endl;
//    printf("%s\n", glGetString(GL_VERSION));
//}

//void testMenuItem() {
//    std::cout << "Menu item pressed" << std::endl;
//}


//int main(int argc, char** argv) {

//    GuiWrapper w;
//    w.Init(800, 800, "Главное окно.");

//    bool f_open = true;
//    Frame f(w.GetWindowPoint(), 0, 0, 800, 800, u8"Фрейм", &f_open,
//                  ImGuiWindowFlags_None
//                | ImGuiWindowFlags_NoMove
//                | ImGuiWindowFlags_MenuBar
//                | ImGuiWindowFlags_HorizontalScrollbar);
//    f.SetButton(500, 500, 100, 40, u8"кнопка", testButton);
//    f.SetText(100, 100, u8"Обычный текст.");



//    std::vector<GuiWrapperModules::MenuItem> FileMenu { {"New", testMenuItem},
//                                                  {"Open", nullptr},
//                                                  {"Close", nullptr}};
//    f.SetMenuInMenuBar("File", FileMenu);


//    std::vector<GuiWrapperModules::MenuItem> HelpMenu { {"How To", nullptr},
//                                                      {"Как помочь?", nullptr},
//                                                      {"О проекте.", nullptr}};
//    f.SetMenuInMenuBar("Help", HelpMenu);

//    std::string input_bufer;
//    f.SetInputText({200, 200, 300, 300, "##Input text", &input_bufer});

//    std::string input_line_buff;
//    f.SetInputLine({10, 600, 300, "##Input line", &input_line_buff});

//    const char* items[] = { "AAAA", "BBBB", "CCCC",
//                           "DDDD", "EEEE", "FFFF",
//                           "GGGG", "HHHH", "IIIIIII",
//                           "JJJJ", "KKKKKKK" };
//    f.SetComboBox({300, 50, 200, "Combobox", items, 11});

//    w.SetFrame(f);



//    //Если закрыть фрейм,выполняется выход из программы
//    w.Render([&](){if (!f_open) {w.Destroy();} } );



//    w.Destroy();
//    return 0;
//}
