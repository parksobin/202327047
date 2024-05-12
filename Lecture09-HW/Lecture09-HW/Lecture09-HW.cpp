#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float earthOrbit = 0.0f; // 지구의 공전 각도
float moonOrbit = 0.0f;  // 달의 공전 각도

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int drawSun(float size)
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); 

    glVertex2f(-size / 2.0f, -size / 2.0f);
    glVertex2f(size / 2.0f, -size / 2.0f);
    glVertex2f(size / 2.0f, size / 2.0f);
    glVertex2f(-size / 2.0f, size / 2.0f);

    glEnd();
    return 0;
}

int drawCircle(float radius)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 50; i++)
    {
        glVertex3f(
            radius * cos(6.28f * float(i) / 50.0),
            radius * sin(6.28f * float(i) / 50.0), 0.0);
    }

    glEnd();
    return 0;
}

int drawEarth(float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.5f, 1.0f);

    float x_center = 0.5f * cos(earthOrbit);
    float y_center = 0.5f * sin(earthOrbit);
    glVertex2f(x_center, y_center);

    for (int i = 0; i <= 50; i++)
    {
        float theta = earthOrbit + 2.0f * 3.1415926f * float(i) / 50.0f;
        float x = radius * cosf(theta) + x_center;
        float y = radius * sinf(theta) + y_center;

        glVertex2f(x, y);
    }

    glEnd();
    return 0;
}

int drawMoon(float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.7f, 0.7f, 0.7f);

    float x_center = 0.2f * cos(moonOrbit) + 0.5f * cos(earthOrbit);
    float y_center = 0.2f * sin(moonOrbit) + 0.5f * sin(earthOrbit);
    glVertex2f(x_center, y_center);

    for (int i = 0; i <= 50; i++)
    {
        float theta = moonOrbit + 2.0f * 3.1415926f * float(i) / 50.0f;
        float x = radius * cosf(theta) + x_center;
        float y = radius * sinf(theta) + y_center;

        glVertex2f(x, y);
    }

    glEnd();
    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Solar System", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, 800, 600);

    while (!glfwWindowShouldClose(window))
    {
        earthOrbit += 0.0009f;
        moonOrbit -= 0.001f;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        drawSun(0.1f); 
        drawCircle(0.5); 
        drawEarth(0.05f); 
        drawMoon(0.02f); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
