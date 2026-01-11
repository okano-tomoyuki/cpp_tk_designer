#ifndef WIDGET_MODEL_HPP
#define WIDGET_MODEL_HPP

#include <string>
#include <map>
#include <vector>

struct WidgetModel
{
    // 固有 ID（Label1, Edit3, Panel2 など）
    std::string id;

    // ウィジェット種別（Label, Entry, Button, Frame, Notebook, Tab など）
    std::string type;

    // 親ウィジェットの ID（Form の場合は FormModel.name）
    std::string parent_id;

    // 位置とサイズ（place ベース）
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    // プロパティ（text, orient, variable, onvalue, offvalue, values など）
    std::map<std::string, std::string> props;

    // イベント（OnClick → handler 名など）
    std::map<std::string, std::string> events;

    // 子ウィジェット（Notebook → Tab、Frame → Label など）
    std::vector<std::string> children;
};

#endif
