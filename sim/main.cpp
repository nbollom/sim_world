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
#include "editor.h"
#include "menu_stack.h"

State state;
Editor *editor;
MenuStack *menu_stack;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_resize_callback(GLFWwindow *window, int new_width, int new_height) {
    state.width = new_width;
    state.height = new_height;
}

static void glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_E && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)) {
            editor->ToggleVisibility();
        }
        else if (key == GLFW_KEY_F10) {
            state.show_fps = !state.show_fps;
        }
    }
}

int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);            // 3.0+ only
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(state.width, state.height, "SimWorld", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetWindowSizeCallback(window, glfw_resize_callback);
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

    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    // TODO: throw this away and make setting for ui scaling
#if defined(__APPLE__)
    io.FontGlobalScale = xscale * 0.75;
#else
    io.FontGlobalScale = xscale * 1.5;
#endif

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Font
    io.Fonts->AddFontDefault();
    //ImFont* font = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);
    //IM_ASSERT(font != NULL);

    state.previousTime = glfwGetTime();

    Database *shared_db = Database::Shared();
    shared_db->InitializeDatabase();

    editor = new Editor(&state);
    MainMenu *main_menu = new MainMenu(&state);
    main_menu->Show();
    menu_stack = MenuStack::Shared();
    menu_stack->PushMenu(main_menu);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        double currentTime = glfwGetTime();
        state.frameCount++;
        // If a second has passed.
        if ( currentTime - state.previousTime >= 1.0 ) {
            state.fps = state.frameCount;
            state.frameCount = 0;
            state.previousTime = currentTime;
        }
        if (state.show_fps) {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
            ImGui::Text("%3d", state.fps);
            ImGui::End();
        }

        menu_stack->Draw();
        editor->Draw();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

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

    return 0;
}
