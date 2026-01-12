#include <nlohmann/json.hpp>
#include <cpp_tk/cpp_tk.hpp>

#include "base_form.hpp"
#include "widget_model.hpp"
#include "form_model.hpp"
#include "serialize.hpp"
#include "preview_builder.hpp"
#include "designer.hpp"

int main(int argc, char** argv) 
{ 
    auto app        = new tk::Tk(); 
    auto designer   = new Designer(app); 
    designer->protocol("WM_DELETE_WINDOW", [&](){
        app->quit();
    });
    app->withdraw(); 
    app->mainloop(); 
    return 0;
}