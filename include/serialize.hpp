#include <fstream>
#include <nlohmann/json.hpp>
#include "widget_model.hpp"
#include "form_model.hpp"

inline void to_json(nlohmann::json& j, const WidgetModel& w)
{
    j = nlohmann::json{
        {"id", w.id},
        {"type", w.type},
        {"parent_id", w.parent_id},
        {"x", w.x},
        {"y", w.y},
        {"width", w.width},
        {"height", w.height},
        {"props", w.props},
        {"events", w.events},
        {"children", w.children}
    };
}

inline void from_json(const nlohmann::json& j, WidgetModel& w)
{
    j.at("id").get_to(w.id);
    j.at("type").get_to(w.type);
    j.at("parent_id").get_to(w.parent_id);
    j.at("x").get_to(w.x);
    j.at("y").get_to(w.y);
    j.at("width").get_to(w.width);
    j.at("height").get_to(w.height);

    if (j.contains("props"))  j.at("props").get_to(w.props);
    if (j.contains("events")) j.at("events").get_to(w.events);
    if (j.contains("children")) j.at("children").get_to(w.children);
}

inline void to_json(nlohmann::json& j, const FormModel& f)
{
    j = nlohmann::json{
        {"name", f.name},
        {"caption", f.caption},
        {"width", f.width},
        {"height", f.height},
        {"root_widgets", f.root_widgets},
        {"widgets", f.widgets},
        {"id_counter", f.id_counter}
    };
}

inline void from_json(const nlohmann::json& j, FormModel& f)
{
    j.at("name").get_to(f.name);
    j.at("caption").get_to(f.caption);
    j.at("width").get_to(f.width);
    j.at("height").get_to(f.height);

    if (j.contains("root_widgets"))
        j.at("root_widgets").get_to(f.root_widgets);

    if (j.contains("widgets"))
        j.at("widgets").get_to(f.widgets);

    if (j.contains("id_counter"))
        j.at("id_counter").get_to(f.id_counter);
}

inline void save_form_model(const FormModel& model, const std::string& path)
{
    nlohmann::json j = model;
    std::ofstream ofs(path);
    ofs << j.dump(4);  // インデント 4
}

inline FormModel load_form_model(const std::string& path)
{
    std::ifstream ifs(path);
    nlohmann::json j;
    ifs >> j;
    return j.get<FormModel>();
}
