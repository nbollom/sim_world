#include <simworld/simworld.h>

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <functional>

// Sate Variables
bool show_fps = false;
double previousTime = 0;
int frameCount = 0;
int fps = 0;
bool show_editor = true; // TODO: Set to false when gameplay working with key combo to show

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_E && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)) {
            show_editor = !show_editor;
        }
        else if (key == GLFW_KEY_F10) {
            show_fps = !show_fps;
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
    GLFWwindow* window = glfwCreateWindow(1280, 720, "SimWorld", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwSetKeyCallback(window, glfw_key_callback);

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

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Font
    io.Fonts->AddFontDefault();
    //ImFont* font = io.Fonts->AddFontFromFileTTF("font.ttf", 18.0f);
    //IM_ASSERT(font != NULL);

    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    io.FontGlobalScale = xscale;

    previousTime = glfwGetTime();

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

        if (show_fps) {
            double currentTime = glfwGetTime();
            frameCount++;
            // If a second has passed.
            if ( currentTime - previousTime >= 1.0 ) {
                fps = frameCount;
                frameCount = 0;
                previousTime = currentTime;
            }
            ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
            ImGui::Text("%3d", fps);
            ImGui::End();
        }

        if (show_editor) {
            if (ImGui::Begin("Data Editor", &show_editor)) {
                // Add controls only if not minimised to save cpu cycles
                if (ImGui::BeginTabBar("Editor Tabs", ImGuiTabBarFlags_None)) {
                    if (ImGui::BeginTabItem("Materials")) {
                        ImGui::Text("Placeholder");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Tiles")) {
                        ImGui::Text("Placeholder");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Objects")) {
                        ImGui::Text("Placeholder");
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
            }
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

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
