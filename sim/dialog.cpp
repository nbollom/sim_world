//
// Created by Nathan Bollom on 11/12/20.
//

#include "dialog.h"
#include <imgui.h>
#include <simworld/utils.h>

#include <utility>

Dialog::Dialog(State *state, std::string title, std::string message): _state(state), _title(std::move(title)), _message(std::move(message)) {

}

void Dialog::AddButton(const std::string& text, std::function<void ()> callback) {
    _buttons[text] = std::move(callback);
}

void Dialog::Draw() {
    std::function<void()> button_method = nullptr;
    ImVec2 window_padding = ImGui::GetStyle().WindowPadding;
    ImVec2 item_spacing = ImGui::GetStyle().ItemSpacing;
    float button_width = 50;
    float button_height = 20;
    for (const auto& button: _buttons) {
        ImVec2 button_size = ImGui::CalcTextSize(button.first.c_str(), nullptr, false, 100);
        button_width = MAX(button_size.x, button_width);
        button_height = MAX(button_size.y, button_height);
    }
    float buttons_width = button_width * _buttons.size() + item_spacing.x * static_cast<float>(_buttons.size() - 1);
    float max_size = MIN(buttons_width, _state->width - window_padding.x * 2);
    ImVec2 message_size = ImGui::CalcTextSize(_message.c_str(), nullptr, false, max_size);
    float width = message_size.x + window_padding.x * 2 * 2;
    float height = message_size.y + window_padding.y * 2 + item_spacing.y + button_height;
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::OpenPopup(_title.c_str());
    if (ImGui::BeginPopupModal(_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::PushTextWrapPos(max_size);
        ImGui::Text("%s", _message.c_str());
        ImGui::PopTextWrapPos();
        for (const auto& button: _buttons) {
            if (ImGui::Button(button.first.c_str())) {
                button_method = button.second;
            }
        }
        ImGui::EndPopup();
    }
    // Call the button press method at the end since it deletes the dialogue and would throw an error in the middle of rendering
    if (button_method) {
        button_method();
    }
}