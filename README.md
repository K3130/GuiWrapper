# GuiWrapper
Часто приходится делать не большие проекты. Что бы не думать что использоавть для кросплатформы и выбирать между qt, wxwidgets и других.    
Нашел для себя вариант.    
Главное: Бысто подключил в виде сабмодуля проект, и у тебя есть гуй, без дополнительных телодвижений, не нужно скачивать и устанавливать фреймворки.    
Возможность сборки на практически голой системе.    
Поддержка windows, linux из коробки.    
Проект чисто для своего удобства и использования.    

Пример cmake:    
```cmake
cmake_minimum_required(VERSION 3.5)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -mwindows")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GuiWrapper)


add_executable(untitled main.cpp)


target_link_libraries(${PROJECT_NAME} PUBLIC GuiWrapper)

install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
```
Простой пример:    
```C++
#include "GuiWrapper/guiwrapper/guiwrapper.h"

void testButton() {
    std::cout << "Button presed" << std::endl;
    printf("%s\n", glGetString(GL_VERSION));
}

void testMenuItem() {
    std::cout << "Menu item pressed" << std::endl;
}

int main(int argc, char** argv)
{
    GuiWrapper w;
    w.Init(800, 800, "Главное окно.");
        bool f_open = true;
        Frame f(w.GetWindowPoint(), 0, 0, 800, 800, u8"Фрейм", &f_open,
                      ImGuiWindowFlags_None
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_MenuBar
                    | ImGuiWindowFlags_HorizontalScrollbar);
        f.SetButton(500, 500, 100, 40, u8"кнопка", testButton);
        f.SetText(100, 100, u8"Обычный текст.");
    w.SetFrame(f);
    w.Render([&](){if (!f_open) {w.Destroy();} } );
    return 0;
}
```
