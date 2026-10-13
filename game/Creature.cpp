#include "Creature.h"

#include <GLFW/glfw3.h>

Creature::Creature(float speed) : speed_(speed) {}

void Creature::update(Input& input, float dt) {
    float move = speed_ * dt;

    if (input.isKeyDown(GLFW_KEY_W)) y_ += move;
    if (input.isKeyDown(GLFW_KEY_S)) y_ -= move;
    if (input.isKeyDown(GLFW_KEY_D)) x_ += move;
    if (input.isKeyDown(GLFW_KEY_A)) x_ -= move;
}