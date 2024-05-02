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

    struct MenuItem
    {
        const char* m_lable;
        const std::function<void()> m_f;
    };

    struct Menu
    {
        const char* m_t;
        std::vector<MenuItem> m_menuitem;
    };

    struct InputText
    {

    };



}


#endif // MODULES_H
