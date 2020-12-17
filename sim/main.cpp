#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <functional>

#include <simworld/simworld.h>
#include "state.h"
#include "main_menu.h"
#include "editor_menu.h"
#include "menu_stack.h"
#include "settings.h"

Settings *settings;
State state;
EditorMenu *editor;
MenuStack *menu_stack;
bool has_focus = true;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_resize_callback(GLFWwindow *window, int new_width, int new_height) {
    state.width = new_width;
    state.height = new_height;
}

static void glfw_focus_callback(GLFWwindow *window, int focused) {
#ifndef DEBUG
    has_focus = focused;
#endif
}

static void glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_E && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)) {
            editor->ToggleVisibility();
        }
        else if (key == GLFW_KEY_F10) {
            settings->show_fps = !settings->show_fps;
        }
    }
}

void LoadFonts(ImGuiIO& io) {
    io.FontGlobalScale = settings->font_scale;
    // Load Font
    io.Fonts->ClearFonts();
    io.Fonts->AddFontDefault();
    //ImFont* font = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);
    //IM_ASSERT(font != NULL);
    io.Fonts->Build();
}

int main(int argc, char *argv[]) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    settings = Settings::Shared();

    // Decide GL+GLSL versions
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);            // 3.0+ only
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, settings->refresh_rate);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(settings->window_width, settings->window_height, "SimWorld", settings->fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwSetWindowPos(window, 0, 0);
    state.window = window;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetWindowSizeCallback(window, glfw_resize_callback);
    glfwSetWindowFocusCallback(window, glfw_focus_callback);
    glfwGetWindowSize(window, &state.width, &state.height); // Size can change due to monitor size/scaling so update variables

    // Initialize OpenGL loader
    bool err = gl3wInit() != 0;
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    LoadFonts(io);

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.06f, 0.06f, 0.06f, 0.8f));

    state.previousTime = glfwGetTime();

    Database *shared_db = Database::Shared();
    shared_db->InitializeDatabase();

    editor = new EditorMenu(&state);
    auto *main_menu = new MainMenu(&state);
    menu_stack = MenuStack::Shared();
    menu_stack->PushMenu(main_menu);

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--editor") == 0) {
            editor->Show();
        }
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (has_focus) {
            // Don't actually update / run game logic if window has lost focus

            if (io.FontGlobalScale != settings->font_scale) {
                io.FontGlobalScale = settings->font_scale;
            }

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            double currentTime = glfwGetTime();
            state.frameCount++;
            // If a second has passed.
            if (currentTime - state.previousTime >= 1.0) {
                state.fps = state.frameCount;
                state.frameCount = 0;
                state.previousTime = currentTime;
            }

            menu_stack->Draw();
            editor->Draw();

            if (settings->show_fps) {
                ImVec2 text_size = ImGui::CalcTextSize("999");
                ImVec2 window_padding = ImGui::GetStyle().WindowPadding;
                ImGui::SetNextWindowPos(ImVec2(static_cast<float>(state.width) - text_size.x - window_padding.x * 2.0f, 0.0f), ImGuiCond_Always);
                ImGui::SetNextWindowSize(ImVec2(text_size.x + window_padding.x * 2.0f, text_size.y), ImGuiCond_Always);
                ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav);
                ImGui::Text("%03d", state.fps);
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        if (state.should_quit) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    // Cleanup
    menu_stack->Clear();
    delete editor;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    settings->Save();

    return 0;
}
