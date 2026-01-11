#ifndef FORM_MODEL_HPP
#define FORM_MODEL_HPP

#include <string>
#include <vector>
#include "widget_model.hpp"

struct FormModel
{
    // フォーム名（Form1, Form2 など）
    std::string name;

    // 表示タイトル
    std::string caption;

    // フォームサイズ
    int width = 800;
    int height = 600;

    // フォーム直下のウィジェット ID（アウトラインビュー用）
    std::vector<std::string> root_widgets;

    // 全ウィジェットの辞書（id → WidgetModel）
    std::map<std::string, WidgetModel> widgets;

    // 新しいウィジェット ID を生成するためのカウンタ
    int id_counter = 1;

    // ------------------------------------------------------------
    // ユーティリティ
    // ------------------------------------------------------------

    // 新規ウィジェット ID を生成（Label1, Label2...）
    std::string generate_id(const std::string &base)
    {
        return base + std::to_string(id_counter++);
    }

    // ウィジェットを追加
    void add_widget(const WidgetModel &w)
    {
        widgets[w.id] = w;
        if (w.parent_id == name)
        {
            root_widgets.push_back(w.id);
        }
        else
        {
            widgets[w.parent_id].children.push_back(w.id);
        }
    }
};

#endif
