#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH 3800
#define WINDOW_HEIGHT 1600
#define NUM_SHAPES 500

typedef struct {
    float x;
    float y;
    float size;
} Shape;

void drawShape(float x, float y, float size) {
    float halfSize = size * 0.5f;
    glBegin(GL_TRIANGLES);
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glVertex2f(x - halfSize, y - halfSize);
    glVertex2f(x + halfSize, y - halfSize);
    glVertex2f(x, y + halfSize);
    glEnd();
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Shapes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glClear(GL_COLOR_BUFFER_BIT);

    Shape shapes[NUM_SHAPES];
    for (int i = 0; i < NUM_SHAPES; ++i) {
        shapes[i].x = (float)(rand() % WINDOW_WIDTH) / WINDOW_WIDTH * 2.0f - 1.0f;
        shapes[i].y = (float)(rand() % WINDOW_HEIGHT) / WINDOW_HEIGHT * 2.0f - 1.0f;
        shapes[i].size = (float)(rand() % 40 + 10) / 100.0f; // 크기를 0.1에서 0.5 사이의 랜덤 값으로 설정
        drawShape(shapes[i].x, shapes[i].y, shapes[i].size);
    }

    glfwSwapBuffers(window);

    glfwPollEvents();

    while (!glfwWindowShouldClose(window)) {
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}
