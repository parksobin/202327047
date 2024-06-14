#pragma once
#include <GLFW/glfw3.h>

class Object {
public:
    float x, y, width, height;
    float r, g, b; // Color

    Object(float x = 0, float y = 0, float width = 0, float height = 0, float r = 1, float g = 1, float b = 1)
        : x(x), y(y), width(width), height(height), r(r), g(g), b(b) {}

    virtual void OnCollisionEnter(Object& other) {
    }

    void Draw(float borderThickness = 0.0f);
};

class Player : public Object {
public:
    Player(float x, float y, float width, float height, float r, float g, float b)
        : Object(x, y, width, height, r, g, b) {}

    void OnCollisionEnter(Object& other) override {
    }
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float x = 0, float y = 0, float width = 0, float height = 0, float r = 0, float g = 1, float b = 0)
        : Object(x, y, width, height, r, g, b) {}

    void Move(float dx) {
        x += dx;
    }

    void OnCollisionEnter(Object& other) override {
    }
};

class Floor : public Object {
public:
    Floor(float x, float y, float width, float height, float r, float g, float b)
        : Object(x, y, width, height, r, g, b) {}

    void OnCollisionEnter(Object& other) override {
    }
};

int PhysicsAABB(Object A, Object B);
