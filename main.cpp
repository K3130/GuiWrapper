#include "guiwrapper/guiwrapper.h"

int main(int argc, char** argv) {

    GuiWrapper w;
    w.Init(800, 600, "Test");
    w.Render();
    w.Destroy();
    return 0;
}
