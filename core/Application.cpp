#include "Application.h"

#include <iostream>

Application::Application(int width, int height, const std::string &title) {
    if (!glfwInit()) {
        std::cerr << "ERROR::GLFW::INIT_FAILED\n";
        return;
    }
    _width = width;
    _height = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        std::cerr << "ERROR::GLFW::WINDOW_FAILED\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, onFramebufferResize);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "ERROR::GLAD::INIT_FAILED\n";
        glfwDestroyWindow(window_);
        window_ = nullptr;
        glfwTerminate();
        return;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window_, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);
    input_ = std::make_unique<Input>(window_);
}

Application::~Application() {
    input_.reset();
    if (window_) glfwDestroyWindow(window_);
    glfwTerminate();
}

void Application::run(const FrameFn &onFrame) {
    while (!glfwWindowShouldClose(window_)) {
        glClearColor(backgroundColor_.r, backgroundColor_.g, backgroundColor_.b, backgroundColor_.a);
        glClear(GL_COLOR_BUFFER_BIT);

        if (onFrame) onFrame();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Application::convertToNdc(std::vector<float>& vertices, int stride, float halfWidthUnits) const {
    float aspect = static_cast<float>(_width) / _height;

    for (size_t i = 0; i + 1 < vertices.size(); i += stride) {
        vertices[i]     = vertices[i] / halfWidthUnits;
        vertices[i + 1] = vertices[i + 1] * aspect / halfWidthUnits;
    }
}

void Application::setBackgroundColor(float r, float g, float b, float a) {
    backgroundColor_ = Color{
        r / 255.f, g / 255.f, b / 255.f, a
    };
}

void Application::setBackgroundColor(const Color &color) {
    setBackgroundColor(color.r, color.g, color.b, color.a);
}

void Application::onFramebufferResize(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}
