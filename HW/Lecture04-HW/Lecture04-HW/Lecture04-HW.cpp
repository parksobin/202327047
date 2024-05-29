#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

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

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            // 왼쪽 마우스 버튼이 눌렸을 때 윈도우를 녹색으로 변경
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            // 왼쪽 마우스 버튼이 떼어졌을 때 배경색을 검정색으로 돌림
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            // 오른쪽 마우스 버튼이 눌렸을 때 윈도우를 빨간색으로 변경
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            // 오른쪽 마우스 버튼이 떼어졌을 때 배경색을 검정색으로 돌림
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    int leftButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    if (leftButton == GLFW_PRESS)
    {
        // 왼쪽 버튼을 누르고 드래그 중이면 마젠타색으로 변경
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if (rightButton == GLFW_PRESS)
    {
        // 오른쪽 버튼을 누르고 드래그 중이면 파란색으로 변경
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }
}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (yoffset > 0)
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 
        else
            glClearColor(0.0f, 0.0f, 1.0f, 1.0); // 
    }
    // 왼쪽 마우스 버튼이 눌렸는지 확인
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

    }

    // 새로운 배경색을 설정한 후 화면을 다시 그려줌
   // glClear(GL_COLOR_BUFFER_BIT);
   // glfwSwapBuffers(window);
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    // 초기 배경색을 검정색으로 설정
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}