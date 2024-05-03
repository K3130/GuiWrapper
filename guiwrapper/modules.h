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
        float m_x;
        float m_y;
        float m_w;
        float m_h;
        const char* m_lable;
        std::string *m_bufer;
    };

    struct InputLine
    {
        float m_x;
        float m_y;
        float m_w;
        const char* m_lable;
        std::string *m_bufer;
    };

    struct ComboBox
    {
        float m_x;
        float m_y;
        float m_w;
        const char* m_lable;
        const char** m_items;
        size_t m_size;
        int m_item_current = 0;
    };



}


#endif // MODULES_H
