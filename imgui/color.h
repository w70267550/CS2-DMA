#pragma once
#include "imgui.h"



namespace colors {

    inline ImVec4 general_color = ImColor(204, 0, 255, 255);
    inline ImVec4 main_color = ImColor(16, 16, 16, 255); // tab background colors
    inline ImVec4 lite_color = ImColor(15, 15, 15, 255);
    inline ImVec4 gray_color = ImColor(15, 15, 15, 255);
    inline ImVec4 Tab_Child = ImColor(15, 15, 15, 255);
    inline ImVec4 Tab_Border = ImColor(15, 15, 15, 255);

    inline ImVec4 Tab_Selected = ImColor(204, 0, 255, 255);
    inline ImVec4 Tab_Hovered = ImColor(180, 180, 180, 255);
    inline ImVec4 Tab = ImColor(100, 100, 100, 255);

    inline ImVec4 Checkbox = ImColor(14, 14, 14, 255);
    inline ImVec4 Checkbox_Hovered = ImColor(12, 12, 12, 255);
    inline ImVec4 Checkbox_Active = ImColor(204, 0, 255, 255);

    inline ImVec4 Car_Slider = ImColor(204, 0, 255, 255);
    inline ImVec4 Car_Slider_Hovered = ImColor(163, 0, 204, 255);
    inline ImVec4 Car_Slider_Active = ImColor(204, 0, 255, 255);

    inline ImVec4 Slider = ImColor(16, 16, 16, 255);
    inline ImVec4 Slider_Hovered = ImColor(18, 18, 18, 255);
    inline ImVec4 Slider_Active = ImColor(18, 18, 18, 255);

    inline ImVec4 Circle_Slider = ImColor(255, 255, 255, 255);
    inline ImVec4 Circle_SliderHovered = ImColor(255, 255, 255, 255);
    inline ImVec4 Circle_SliderActive = ImColor(255, 255, 255, 255);

    inline ImVec4 Combo = ImColor(26, 26, 26, 255);
    inline ImVec4 Combo_Hovered = ImColor(26, 26, 26, 255);
    inline ImVec4 Combo_Active = ImColor(26, 26, 26, 255);

    inline ImVec4 InputText = ImColor(18, 18, 18, 255);
    inline ImVec4 InputText_Hovered = ImColor(22, 22, 22, 255); // text boxes not font
    inline ImVec4 InputText_Active = ImColor(22, 22, 22, 255);

    inline ImVec4 Button = ImColor(10, 10, 10, 255);
    inline ImVec4 Button_Hovered = ImColor(163, 0, 204, 255);
    inline ImVec4 Button_Active = ImColor(204, 0, 255, 255);

    inline ImVec4 Selectable_Hovered = ImColor(15, 15, 15, 255);
    inline ImVec4 Selectable_Active = ImColor(15, 15, 15, 255);

    inline ImVec4 Picker_Active = ImColor(20, 20, 20, 255);

    inline ImVec4 Text = ImColor(204, 0, 255, 255);
    inline ImVec4 Text_Hovered = ImColor(163, 0, 204, 255);
    inline ImVec4 Text_Active = ImColor(204, 0, 255, 255);

    inline ImVec4 CheckMark = ImColor(255, 255, 255, 255);

    inline ImVec4 Transparent = ImColor(0, 0, 0, 0);

    inline ImVec4 tab_tooltip = ImColor(180, 180, 180, 255);

    inline ImVec4 keybind_background = ImColor(17, 17, 17, 255);
    inline ImVec4 keybind_border = ImColor(28, 28, 28, 255);
}