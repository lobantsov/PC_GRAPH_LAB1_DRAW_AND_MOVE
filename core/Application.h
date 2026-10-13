#ifndef LAB1_APPLICATION_H
#define LAB1_APPLICATION_H

#include <functional>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Color.h"
#include "Input.h"
#include "NdcPoint .h"

class Application {
public:
    using FrameFn = std::function<void()>;

    Application(int width, int height, const std::string &title);

    ~Application();

    bool isValid() const { return window_ != nullptr; }

    void setBackgroundColor(float r, float g, float b, float a = 1.0f);

    void setBackgroundColor(const Color &color);

    Color backgroundColor() const { return backgroundColor_; }

    Input &input() { return *input_; }

    void requestClose() { glfwSetWindowShouldClose(window_, GLFW_TRUE); }

    void run(const FrameFn &onFrame);

    void convertToNdc(std::vector<float>& vertices, int stride, float halfWidthUnits) const;

private:
    static void onFramebufferResize(GLFWwindow *window, int width, int height);

    int _width;
    int _height;
    GLFWwindow *window_ = nullptr;
    Color backgroundColor_;
    std::unique_ptr<Input> input_;
};

#endif //LAB1_APPLICATION_H
