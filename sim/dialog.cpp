//
// Created by Nathan Bollom on 11/12/20.
//

#include "dialog.h"
#include <imgui.h>
#include <cmath>
#include <simworld/utils.h>

Dialog::Dialog(State *state, std::string title, std::string message): Dialog(state, std::move(title), std::move(message), 50, 20) {
}

Dialog::Dialog(State *state, std::string title, std::string message, float button_witdth, float button_height):
_state(state), _title(std::move(title)), _message(std::move(message)), _button_width(button_witdth), _button_height(button_height) {
    _button_method = nullptr;
}

void Dialog::AddButton(const std::string& text, std::function<void ()> callback) {
    _buttons.emplace_back(text, std::move(callback));
}

void Dialog::Draw() {
    ImVec2 title_height = ImGui::GetStyle().WindowMinSize;
    ImVec2 window_padding = ImGui::GetStyle().WindowPadding;
    ImVec2 item_spacing = ImGui::GetStyle().ItemSpacing;
    float buttons_width = _button_width * _buttons.size() + item_spacing.x * static_cast<float>(_buttons.size() - 1);
    float min_size = MAX(buttons_width, 400.0f);
    float max_size = MIN(min_size, _state->width - window_padding.x * 2.0f);
    ImVec2 message_size = ImGui::CalcTextSize(_message.c_str(), nullptr, false, max_size);
    float width = max_size + window_padding.x * 2.0f;
    int buttons_per_row = _buttons.size();
    float max_buttons_width = width - window_padding.x * 2.0f;
    while (buttons_width > max_buttons_width) {
        buttons_per_row--;
        buttons_width = _button_width * static_cast<float>(buttons_per_row) + item_spacing.x * static_cast<float>(buttons_per_row - 1);
    }
    int rows = static_cast<int>(std::ceil(static_cast<float>(_buttons.size()) / static_cast<float>(buttons_per_row)));
    float height = title_height.y + message_size.y + window_padding.y * 2.0f + item_spacing.y * 2.0f + _button_height * static_cast<float>(rows) + item_spacing.y * (static_cast<float>(rows) - 1);
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::OpenPopup(_title.c_str());
    if (ImGui::BeginPopupModal(_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::PushTextWrapPos(max_size);
        ImGui::Text("%s", _message.c_str());
        ImGui::PopTextWrapPos();
        ImGui::Dummy(ImVec2(1.0f, item_spacing.y * 2.0f));
        int start = 0;
        while(start < _buttons.size()) {
            auto begin = _buttons.begin() + start;
            auto end = _buttons.begin() + (MIN(start + buttons_per_row, static_cast<int>(_buttons.size())));
            auto buttons = std::vector<std::pair<std::string, std::function<void()>>>(begin, end);
            buttons_width = _button_width * static_cast<float>(buttons.size()) + item_spacing.x * static_cast<float>(buttons.size() - 1);
            float button_indent = width - buttons_width - window_padding.x * 2.0f;
            if (button_indent > 0) {
                ImGui::Indent(button_indent);
            }
            int index = 0;
            for (const auto& button: buttons) {
                if (index++ > 0) {
                    ImGui::SameLine();
                }
                if (ImGui::Button(button.first.c_str(), ImVec2(_button_width, _button_height))) {
                    _button_method = button.second;
                }
            }
            if (button_indent > 0) {
                ImGui::Unindent(button_indent);
            }
            start += buttons_per_row;
        }
        ImGui::EndPopup();
    }
    // Call the button press method at the end since it deletes the dialogue and would throw an error in the middle of rendering
    if (_button_method) {
        _button_method();
    }
}
