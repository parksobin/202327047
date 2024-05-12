#pragma comment(lib, "Opengl32.lib") 

#include <GLFW/glfw3.h> 
#include <iostream>

int width = 1280;
int height = 768;

float X = 0.0f; // 초기 X 좌표
float Y = 0.0f; // 초기 Y 좌표
double prevX, prevY; // 마우스 위치 저장

float zoom = 1.0f; // 초기 줌
bool zoomin = false;
bool dragging = false;

float cameraX = 0.0f; // 카메라 X 좌표
float cameraY = 0.0f; // 카메라 Y 좌표

// 화면창
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height); // 뷰포트 설정
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        dragging = true;
        zoomin = false;
        glfwGetCursorPos(window, &prevX, &prevY); // 마우스 위치 저장
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        dragging = true;
        zoomin = true;
        glfwGetCursorPos(window, &prevX, &prevY); // 마우스 위치 저장
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        dragging = false;
    }
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    if (dragging) {
        float sensitivity = 0.01f; // 이동 감도
        double deltaX = xPos - prevX;
        double deltaY = yPos - prevY;

        if (zoomin) {
            if (deltaX > 0) {
                zoom *= (1.0f + sensitivity * deltaX); // 줌 인
            }
            else if (deltaX < 0) {
                zoom /= (1.0f - sensitivity * deltaX); // 줌 아웃
            }
        }
        else {
            cameraX -= sensitivity * deltaX; // 카메라 이동
            cameraY += sensitivity * deltaY; // 카메라 이동
        }

        prevX = xPos;
        prevY = yPos;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 3D를 2D 를 변화해주는것같음 잘모르겠음 이거는
void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f); // 원근 투영 설정
    glMatrixMode(GL_MODELVIEW);
}

// 별그리기 삼각형으로
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

int main(void) {
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "HAHAHAHAHAHAHA", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    glViewport(0, 0, width, height); // 뷰포트 설정

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        setProjection(); // 프로젝션 매트릭스 설정

        glLoadIdentity(); //프로젝션 행렬을 초기화
        glTranslatef(-cameraX, -cameraY, -5.0f); // 카메라 이동
        glScalef(zoom, zoom, 1.0f); // 줌 인/아웃

        // 삼각형 그리기
        drawTriangle(-0.3f, 0.0f, 0.0f, -0.5f, 0.3f, 0.0f);
        drawTriangle(0.0f, 0.3f, 0.1f, -0.32f, -0.2f, -0.85f);
        drawTriangle(0.0f, 0.3f, -0.1f, -0.32f, 0.2f, -0.85f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}