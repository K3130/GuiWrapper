#include "guiwrapper/guiwrapper.h"

void testFunc() {
    ImGui::Begin("111");
}

int main(int argc, char** argv) {

    GuiWrapper w;
    w.Init(800, 600, u8"Главное окно.");

    bool f_open = true;
    Frame f(0, 0, 700, 700, "First", &f_open, ImGuiWindowFlags_None);
    f.SetButton(500, 500, 100, 20, "button", testFunc);
    w.SetFrame(f);

    w.Render();



    w.Destroy();
    return 0;
}
