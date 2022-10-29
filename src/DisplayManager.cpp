#include <GL/glew.h>
#include "DisplayManager.h"
#include "Engine.h"
#include "util.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

DisplayManager::DisplayManager(int width, int height, const char *title) : width(width), height(height), title(title) {
    if (!glfwInit()) fatal("glfw initialization failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) fatal("failed to glfwCreateWindow");
    
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) fatal("glewInit is not OK");
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int newWidth, int newHeight){
        Engine::instance->onWindowSizeChanged(newWidth, newHeight);
        Engine::instance->getDisplay()->onWindowSizeChanged(newWidth, newHeight);
    });

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430 core");

    ImGui::GetIO().IniFilename = ImGui::GetIO().LogFilename = nullptr;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glViewport(0, 0, width, height);
}

void DisplayManager::onWindowSizeChanged(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    glViewport(0, 0, width, height);
}

void DisplayManager::update() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glfwPollEvents();
    glfwSwapBuffers(window);
}

DisplayManager::~DisplayManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}