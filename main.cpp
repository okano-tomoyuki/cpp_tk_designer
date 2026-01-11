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
    tk::Tk app; app.withdraw(); // ルートは非表示 
    Designer* designer = new Designer(&app); 
    app.mainloop(); 
    return 0;
}