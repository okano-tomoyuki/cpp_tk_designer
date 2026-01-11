#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <functional>
#include <vector>
#include <string>

#include <cpp_tk/cpp_tk.hpp>
#include "fwd.hpp"

class Palette : public ttk::Frame
{
public:
    // ウィジェットタイプが選択されたときに呼ばれるコールバック
    std::function<void(const std::string&)> on_select;

    Palette(tk::Widget* master)
        : ttk::Frame(master)
    {
        this->config({{"padding", "4"}});

        add_button("Label");
        add_button("Entry");
        add_button("Button");
        add_button("Checkbutton");
        add_button("Radiobutton");
        add_button("Frame");
        add_button("GroupBox");
        add_button("Notebook");
        add_button("Tab");
        add_button("Treeview");
    }

private:
    void add_button(const std::string& type)
    {
        auto btn = new ttk::Button(this);
        btn->config({{"text", type}});
        btn->pack({{"side", "top"}, {"fill", "x"}, {"padx", 2}, {"pady", 2}});

        btn->command([this, type]() {
            if (on_select) {
                on_select(type);
            }
        });
    }
};

#endif
