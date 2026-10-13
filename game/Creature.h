#ifndef LAB1_CREATURE_H
#define LAB1_CREATURE_H

#include "../core/Input.h"

class Creature {
public:
    Creature(float speed);

    void update(Input& input, float dt);

    float x() const { return x_; }
    float y() const { return y_; }

private:
    float speed_;
    float x_ = 0.0f;
    float y_ = 0.0f;
};

#endif //LAB1_CREATURE_H