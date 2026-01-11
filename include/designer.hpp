#ifndef DESIGNER_HPP
#define DESIGNER_HPP

#include <cpp_tk/cpp_tk.hpp>
#include "fwd.hpp"
#include "palette.hpp"
#include "designer_canvas.hpp"
#include "form_model.hpp"
#include "preview_builder.hpp"

class Designer : public BaseForm
{
public:
    Designer(tk::Widget* master = nullptr)
        : BaseForm(master)
    {
        this->title("cpp_tk Designer (Minimal Demo)");

        // Palette（左側）
        palette_ = new Palette(this);
        palette_->place({{"x", 0}, {"y", 0}, {"width", 150}, {"height", 600}});

        // Canvas（右側）
        canvas_ = new DesignerCanvas(this);
        canvas_->place({{"x", 150}, {"y", 0}, {"width", 800}, {"height", 600}});

        // Palette で選択されたウィジェットタイプを保持
        palette_->on_select = [this](const std::string& type) {
            selected_widget_type_ = type;
        };

        // Canvas クリックでウィジェット追加
        canvas_->on_click = [this](int x, int y) {
            if (!selected_widget_type_.empty()) {

                // Canvas のオフセットを補正
                int canvas_x = canvas_->winfo_x();
                int canvas_y = canvas_->winfo_y();

                add_widget_to_model(selected_widget_type_, x + canvas_x, y + canvas_y);

                selected_widget_type_.clear();
            }
        };

        // 初期 FormModel
        model_.name = "Form1";
        model_.caption = "Designer Preview";
    }

private:
    Palette* palette_;
    DesignerCanvas* canvas_;
    FormModel model_;
    std::string selected_widget_type_;

    // Widget* → id の逆引き
    std::unordered_map<tk::Widget*, std::string> widget_to_id_;

    // ドラッグ用
    bool dragging_ = false;
    int drag_offset_x_ = 0;
    int drag_offset_y_ = 0;
    std::string selected_widget_id_;

    // ------------------------------------------------------------
    // Model にウィジェットを追加
    // ------------------------------------------------------------
    void add_widget_to_model(const std::string& type, int x, int y)
    {
        WidgetModel w;
        w.id = model_.generate_id(type);
        w.type = type;
        w.parent_id = model_.name;
        w.x = x;
        w.y = y;

        if (type == "Label") w.props["text"] = "Label";
        if (type == "Button") w.props["text"] = "Button";
        if (type == "Checkbutton") w.props["text"] = "Check";

        model_.add_widget(w);

        rebuild_preview();
    }

    // ------------------------------------------------------------
    // プレビュー再構築
    // ------------------------------------------------------------
    void rebuild_preview()
    {
        widget_to_id_.clear();

        PreviewBuilder::build_preview(
            this,
            model_,
            [this](tk::Widget* w, const std::string& id) {
                widget_to_id_[w] = id;

                // クリック
                w->bind("<Button-1>", [this, w](const tk::Event& e) {
                    on_widget_click(w, e);
                });

                // ドラッグ開始
                w->bind("<ButtonPress-1>", [this, w](const tk::Event& e) {
                    on_drag_start(w, e);
                });

                // ドラッグ中
                w->bind("<B1-Motion>", [this, w](const tk::Event& e) {
                    on_drag_move(w, e);
                });

                // ドラッグ終了
                w->bind("<ButtonRelease-1>", [this, w](const tk::Event& e) {
                    on_drag_end(w, e);
                });
            }
        );
    }

    // ------------------------------------------------------------
    // イベント処理
    // ------------------------------------------------------------
    void on_widget_click(tk::Widget* w, const tk::Event& e)
    {
        selected_widget_id_ = widget_to_id_[w];
        dragging_ = false;
    }

    void on_drag_start(tk::Widget* w, const tk::Event& e)
    {
        selected_widget_id_ = widget_to_id_[w];
        dragging_ = true;

        drag_offset_x_ = e.x;
        drag_offset_y_ = e.y;
    }

    void on_drag_move(tk::Widget* w, const tk::Event& e)
    {
        if (!dragging_) return;

        auto& wm = model_.widgets[selected_widget_id_];

        wm.x += (e.x - drag_offset_x_);
        wm.y += (e.y - drag_offset_y_);

        rebuild_preview();
    }

    void on_drag_end(tk::Widget* w, const tk::Event& e)
    {
        dragging_ = false;
    }
};

#endif