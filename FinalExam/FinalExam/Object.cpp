#include "object.h"

void Object::Draw(float borderThickness) {
    // Draw filled rectangle
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y + height / 2.0f);
    glVertex2f(x - width / 2.0f, y + height / 2.0f);
    glEnd();

    if (borderThickness > 0.0f) {
        // Draw border
        glColor3f(0.0f, 0.0f, 0.0f); // Black color for border
        glBegin(GL_QUADS);
        // Bottom border
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f - borderThickness);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f - borderThickness);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f);
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f);

        // Top border
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f + borderThickness);
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f + borderThickness);

        // Left border
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f);
        glVertex2f(x - width / 2.0f, y - height / 2.0f);
        glVertex2f(x - width / 2.0f, y + height / 2.0f);
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f);

        // Right border
        glVertex2f(x + width / 2.0f, y - height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f, y + height / 2.0f);
        glEnd();
    }
}

int PhysicsAABB(Object A, Object B) {
    // AABB collision detection
    return (A.x - A.width / 2 < B.x + B.width / 2 &&
        A.x + A.width / 2 > B.x - B.width / 2 &&
        A.y - A.height / 2 < B.y + B.height / 2 &&
        A.y + A.height / 2 > B.y - B.height / 2);
}
