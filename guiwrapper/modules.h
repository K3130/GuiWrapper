#ifndef MODULES_H
#define MODULES_H

namespace GuiWrapperModules
{
    struct Button
    {
        float m_x;
        float m_y;
        float m_w;
        float m_h;
        const char* m_t;
        const std::function<void()> m_f;
    };

    struct Text
    {
        float m_x;
        float m_y;
        const char* m_t;
    };
}


#endif // MODULES_H
