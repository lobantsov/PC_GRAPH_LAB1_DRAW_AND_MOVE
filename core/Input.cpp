#include "Input.h"

#include <GLFW/glfw3.h>

Input::Input(GLFWwindow* window) : window_(window) {
    glfwSetWindowUserPointer(window_, this);
    glfwSetKeyCallback(window_, keyCallbackThunk);
}

Input::~Input() {
    glfwSetKeyCallback(window_, nullptr);
    glfwSetWindowUserPointer(window_, nullptr);
}

bool Input::isKeyDown(int key) const {
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

void Input::keyCallbackThunk(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input* self = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if (self && self->keyCallback_) {
        self->keyCallback_(key, action);
    }
}