#pragma comment(lib, "Opengl32.lib") 

#include <GLFW/glfw3.h> 
#include <stdio.h>


int width = 1280;
int height = 768;

float X = 0.0f; // 초기 X 좌표
float Y = 0.0f; // 초기 Y 좌표
double prevX, prevY; // 마우스 위치 저장

float zoom = 1.0f; // 초기 줌


float cameraX = 0.0f; // 카메라 X 좌표
float cameraY = 0.0f; // 카메라 Y 좌표

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}
int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "HAHAHAHAHAHAHA", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    glViewport(0, 0, width, height); // 뷰포트 설정

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        setProjection(); // 프로젝션 매트릭스 설정

        glLoadIdentity(); //프로젝션 행렬을 초기화
        glTranslatef(-cameraX, -cameraY, -5.0f); // 카메라 이동

        drawTriangle(-0.3f, 0.0f, 0.0f, -0.5f, 0.3f, 0.0f);
        drawTriangle(0.0f, 0.3f, 0.1f, -0.32f, -0.2f, -0.85f);
        drawTriangle(0.0f, 0.3f, -0.1f, -0.32f, 0.2f, -0.85f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}