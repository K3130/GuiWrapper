#include "guiwrapper/guiwrapper.h"

void testFunc() {
    ImGui::Begin("111");
}

int main(int argc, char** argv) {

    GuiWrapper w;
    w.Init(800, 600, "Главное окно.");

    bool f_open = true;
    Frame f(0, 0, 600, 500, u8"Фрейм", &f_open, ImGuiWindowFlags_None);
    f.SetButton(500, 500, 100, 40, u8"кнопка", testFunc);
    f.SetText(100, 100, u8"Обычный текст.");
    w.SetFrame(f);

    w.Render();



    w.Destroy();
    return 0;
}
