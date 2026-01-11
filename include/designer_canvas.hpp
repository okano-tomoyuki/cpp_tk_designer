#ifndef DESIGNER_CANVAS_HPP
#define DESIGNER_CANVAS_HPP

#include <functional>
#include <cpp_tk/cpp_tk.hpp>

#include "fwd.hpp"

class DesignerCanvas : public ttk::Frame
{
public:
    // Canvas 上でクリックされたときに呼ばれるコールバック
    // (x, y) はキャンバス内座標
    std::function<void(int, int)> on_click;

    DesignerCanvas(tk::Widget *master)
        : ttk::Frame(master)
    {
        this->config({{"borderwidth", "1"},
                      {"relief", "solid"},
                      {"background", "#f0f0f0"}});

        // マウスクリックイベント
        this->bind("<Button-1>", [this](const tk::Event& e){
            if (on_click) {
                on_click(e.x, e.y);
            } 
        });
    }
};

#endif // DESIGNER_CANVAS_HPP