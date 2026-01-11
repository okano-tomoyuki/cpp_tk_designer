#ifndef BASE_FORM_HPP
#define BASE_FORM_HPP

#include <vector>
#include <cpp_tk/cpp_tk.hpp>

#include "fwd.hpp"

class BaseForm : public tk::Toplevel
{
public:
    BaseForm(tk::Widget *master = nullptr)
        : tk::Toplevel(master)
    {
    }

    virtual ~BaseForm()
    {
        for (auto *w : widget_list_)
        {
            if (w)
            {
                w->destroy();
                delete w;
            }
        }
    }

    void clear_widgets()
    {
        for (auto* w : widget_list_) 
        {
            if (w) 
            {
                w->destroy();
                delete w;
            }
        }
        widget_list_.clear();
    }

    // ------------------------------------------------------------
    // Factory methods
    // ------------------------------------------------------------
    ttk::Label *create_label(tk::Widget *m, int x, int y, const std::string &t)
    {
        auto w = new ttk::Label(m);
        w->config({{"text", t}});
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Entry *create_entry(tk::Widget *m, int x, int y)
    {
        auto w = new ttk::Entry(m);
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Button *create_button(tk::Widget *m, int x, int y, const std::string &t)
    {
        auto w = new ttk::Button(m);
        w->config({{"text", t}});
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Combobox *create_combobox(tk::Widget *m, int x, int y)
    {
        auto w = new ttk::Combobox(m);
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Checkbutton *create_checkbutton(tk::Widget *m, int x, int y, const std::string &t, bool v)
    {
        auto w = new ttk::Checkbutton(m);
        w->config({{"text", t}});
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Radiobutton *create_radiobutton(tk::Widget *m, int x, int y, const std::string &t,
                                         const std::string &var, const std::string &val)
    {
        auto w = new ttk::Radiobutton(m);
        w->config({{"text", t}, {"variable", var}, {"value", val}});
        w->place({{"x", x}, {"y", y}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Treeview *create_treeview(tk::Widget *m, int x, int y, int w_, int h_, const std::vector<std::string> &cols)
    {
        auto w = new ttk::Treeview(m);
        w->place({{"x", x}, {"y", y}, {"width", w_}, {"height", h_}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Frame *create_frame(tk::Widget *m, int x, int y, int w_, int h_)
    {
        auto w = new ttk::Frame(m);
        w->place({{"x", x}, {"y", y}, {"width", w_}, {"height", h_}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Notebook *create_notebook(tk::Widget *m, int x, int y, int w_, int h_)
    {
        auto w = new ttk::Notebook(m);
        w->place({{"x", x}, {"y", y}, {"width", w_}, {"height", h_}});
        widget_list_.push_back(w);
        return w;
    }

    ttk::Frame *create_tab(ttk::Notebook *nb, const std::string &label)
    {
        auto tab = new ttk::Frame(nb);
        nb->add_tab(tab, label);
        widget_list_.push_back(tab);
        return tab;
    }

    tk::Text* create_text(tk::Widget* m, const int& x, const int& y, const int& width, const int& height)
    {
        auto w = new tk::Text(m);
        w->config({{"width", std::to_string(width / 10)}, {"height", std::to_string(height / 10)}});
        w->place({{"x", std::to_string(x)}, {"y", std::to_string(y)}});
        widget_list_.push_back(w);
        return w;   
    }

protected:
    std::vector<tk::Widget *> widget_list_;

};

#endif // BASE_FORM_HPP
