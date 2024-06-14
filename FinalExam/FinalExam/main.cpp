#pragma comment(lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include "object.h"
#include "Transform.h"

// 화면 크기
const int WIDTH = 800;
const int HEIGHT = 600;

// 장애물 수
const int MAX_OBSTACLES = 2;

// 미터 좌표를 픽셀 좌표로 변환하는 함수
float meterToPixel(float meter) {
    return meter * 10.0f; // 1 cm = 10 pixels
}

// 픽셀 좌표를 OpenGL 좌표로 변환하는 함수
float pixelToOpenGL(float pixel, float screenSize) {
    return (2.0f * pixel / screenSize) - 1.0f;
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
}

void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    if (aspectRatio > 1.0f) {
        // Wider than tall
        glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    }
    else {
        // Taller than wide
        glOrtho(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio, -1.0f, 1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
}

int Physics() {
    return 0;
}

int Initialize() {
    return 0;
}

int Update() {
    return 0;
}

int Render() {
    return 0;
}

void UpdateObstacles(EnemyBlock obstacles[], int obstacleCount, float deltaTime, float ground_y_opengl) {
    // 각 장애물을 왼쪽으로 이동시킵니다.
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles[i].Move(-1.0f * deltaTime); // 장애물을 왼쪽으로 이동시킵니다.
    }

    // 화면 밖으로 나간 장애물을 확인하고 재활용합니다.
    for (int i = 0; i < obstacleCount; ++i) {
        if (obstacles[i].x + obstacles[i].width / 2 < -1.0f) {
            // 장애물을 화면 오른쪽 끝으로 다시 이동시킵니다.
            float heights[2] = { 0.2f, 0.6f }; // 낮고 높은 장애물의 높이
            float newX = 1.0f + 0.25f * (rand() % 5); // 새로운 x 위치를 무작위로 설정
            int heightIndex = rand() % 2;
            float newHeight = heights[heightIndex];
            float newY = ground_y_opengl + newHeight / 2; // 지면 위에 장애물을 배치
            obstacles[i] = EnemyBlock(newX, newY, 0.1f, newHeight, 0.0f, 1.0f, 0.0f); // 장애물 재활용
        }
    }
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Google Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    // 초기 위치 설정
    float x_meter = 5.0f; // 지면에서 50cm 오른쪽으로 이동
    float y_meter = 10.0f; // 지면에서 1m 위에 위치

    float x_pixel = meterToPixel(x_meter);
    float y_pixel = meterToPixel(y_meter);

    float x_opengl = pixelToOpenGL(x_pixel, WIDTH);
    float y_opengl = pixelToOpenGL(y_pixel, HEIGHT);

    // 사각형의 크기
    const float square_size_meter = 5.0f; // 50cm = 5m
    const float border_thickness_meter = 0.3f; // 3cm = 0.3m
    float square_size_opengl = 2.0f * meterToPixel(square_size_meter) / WIDTH; // OpenGL 좌표로 변환
    float border_thickness_opengl = 2.0f * meterToPixel(border_thickness_meter) / WIDTH; // OpenGL 좌표로 변환

    // 화면 비율
    float aspectRatio = (float)WIDTH / (float)HEIGHT;

    // 지면의 y 위치
    float ground_y_meter = 10.0f; // 100cm = 10m
    float ground_y_pixel = meterToPixel(ground_y_meter);
    float ground_y_opengl = pixelToOpenGL(ground_y_pixel, HEIGHT);

    // 객체 생성
    Player player(x_opengl, y_opengl, square_size_opengl, square_size_opengl, 1.0f, 0.0f, 0.0f);
    Floor ground(0.0f, ground_y_opengl - 1.0f, 4.0f, 2.0f, 1.0f, 0.78f, 0.06f); // 너비를 4.0으로 설정하여 지면을 늘림

    // 장애물 생성
    EnemyBlock obstacles[MAX_OBSTACLES];
    int obstacleCount = MAX_OBSTACLES;
    float obstacle_width_opengl = 2.0f * meterToPixel(5.0f) / WIDTH; // 50cm = 5m
    float obstacle_height_low_opengl = 2.0f * meterToPixel(10.0f) / HEIGHT; // 100cm = 10m
    float obstacle_height_high_opengl = 2.0f * meterToPixel(30.0f) / HEIGHT; // 300cm = 30m

    obstacles[0] = EnemyBlock(0.75f, ground_y_opengl + obstacle_height_low_opengl / 2, obstacle_width_opengl, obstacle_height_low_opengl, 0.0f, 1.0f, 0.0f);
    obstacles[1] = EnemyBlock(1.25f, ground_y_opengl + obstacle_height_high_opengl / 2, obstacle_width_opengl, obstacle_height_high_opengl, 0.0f, 1.0f, 0.0f);

    glfwSetFramebufferSizeCallback(window, reshape);
    reshape(window, WIDTH, HEIGHT);

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // 배경색을 (R:0, G:30, B:100)로 설정
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // 프레임 버퍼를 지우는 함수 호출

        glfwPollEvents();
        Physics();
        Update();

        // 장애물 업데이트
        UpdateObstacles(obstacles, obstacleCount, deltaTime, ground_y_opengl);

        // 객체 그리기
        ground.Draw();
        player.Draw(border_thickness_opengl);
        for (int i = 0; i < obstacleCount; ++i) {
            obstacles[i].Draw();
        }

        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
