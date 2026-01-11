#ifndef PREVIEW_BUILDER_HPP
#define PREVIEW_BUILDER_HPP

#include <unordered_map>
#include <cpp_tk/cpp_tk.hpp>

#include "fwd.hpp"
#include "widget_model.hpp"
#include "form_model.hpp"
#include "base_form.hpp"

class PreviewBuilder
{

public:
    // model を読み取り、BaseForm 上にウィジェットを構築する
    static void build_preview(
        BaseForm *form, 
        const FormModel &model,
        std::function<void(tk::Widget*, const std::string&)> register_widget
    )
    {
        // 1. 既存のウィジェットを破棄
        form->clear_widgets();

        // 2. ID → 実際の Widget* のマップ
        std::unordered_map<std::string, tk::Widget *> created;

        // 3. まず Form の直下のウィジェットから構築
        for (auto &id : model.root_widgets)
        {
            build_widget_recursive(form, model, id, created, register_widget);
        }
    }

private:
    // 再帰的にウィジェットを構築
    static tk::Widget *build_widget_recursive(
        BaseForm *form,
        const FormModel &model,
        const std::string &id,
        std::unordered_map<std::string, tk::Widget *> &created,
        std::function<void(tk::Widget*, const std::string&)> register_widget
    )
    {
        const WidgetModel &w = model.widgets.at(id);

        // 親 Widget*
        tk::Widget *parent = nullptr;
        if (w.parent_id == model.name)
        {
            parent = form; // Form 直下
        }
        else
        {
            parent = created[w.parent_id];
        }

        tk::Widget *widget = nullptr;

        // ------------------------------------------------------------
        // ウィジェット種別に応じて生成
        // ------------------------------------------------------------
        if (w.type == "Label")
        {
            widget = form->create_label(parent, w.x, w.y, w.props.at("text"));
        }
        else if (w.type == "Entry")
        {
            widget = form->create_entry(parent, w.x, w.y);
        }
        else if (w.type == "Button")
        {
            widget = form->create_button(parent, w.x, w.y, w.props.at("text"));
        }
        else if (w.type == "Combobox")
        {
            widget = form->create_combobox(parent, w.x, w.y);
        }
        else if (w.type == "Checkbutton")
        {
            widget = form->create_checkbutton(parent, w.x, w.y, w.props.at("text"), false);
        }
        else if (w.type == "Radiobutton")
        {
            widget = form->create_radiobutton(parent, w.x, w.y, w.props.at("text"),
                                              "group1", w.id);
        }
        else if (w.type == "Frame")
        {
            widget = form->create_frame(parent, w.x, w.y, w.width, w.height);
        }
        else if (w.type == "GroupBox")
        {
            widget = form->create_frame(parent, w.x, w.y, w.width, w.height);
            widget->config({{"text", w.props.at("text")}});
        }
        else if (w.type == "Notebook")
        {
            widget = form->create_notebook(parent, w.x, w.y, w.width, w.height);
        }
        // else if (w.type == "Tab")
        // {
        //     auto nb = dynamic_cast<ttk::Notebook *>(parent);
        //     widget = form->create_tab(nb, w.props.at("text"));
        // }
        else if (w.type == "Treeview")
        {
            widget = form->create_treeview(parent, w.x, w.y, w.width, w.height, {});
        }
        else
        {
            // 未対応ウィジェット
            return nullptr;
        }

        created[id] = widget;
        register_widget(widget, id);

        // ------------------------------------------------------------
        // 子ウィジェットを再帰的に構築
        // ------------------------------------------------------------
        for (auto &child_id : w.children)
        {
            build_widget_recursive(form, model, child_id, created, register_widget);
        }

        return widget;
    }
};

#endif
