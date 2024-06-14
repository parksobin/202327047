#pragma comment(lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include "object.h"
#include "Transform.h"

// ȭ�� ũ��
const int WIDTH = 800;
const int HEIGHT = 600;

// ��ֹ� ��
const int MAX_OBSTACLES = 2;

// �߷� ���ӵ�
const float GRAVITY = -9.8f; // �߷� ���ӵ�

// �÷��̾� ���� �ӵ�
const float JUMP_VELOCITY = 5.0f;

// �÷��̾� ����
bool isJumping = false;
float playerVelocityY = 0.0f;

// ���� ��ǥ�� �ȼ� ��ǥ�� ��ȯ�ϴ� �Լ�
float meterToPixel(float meter) {
    return meter * 10.0f; // 1 cm = 10 pixels
}

// �ȼ� ��ǥ�� OpenGL ��ǥ�� ��ȯ�ϴ� �Լ�
float pixelToOpenGL(float pixel, float screenSize) {
    return (2.0f * pixel / screenSize) - 1.0f;
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) {
        isJumping = true;
        playerVelocityY = JUMP_VELOCITY; // ���� ���� �� �ӵ� ����
    }
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

void ApplyPhysics(Player& player, Floor& ground, float deltaTime) {
    if (isJumping) {
        playerVelocityY += GRAVITY * deltaTime; // �߷� ���ӵ� ����
        player.y += playerVelocityY * deltaTime; // y ��ġ ������Ʈ

        // ���鿡 ������ ���� ����
        if (player.y - player.height / 2 <= ground.y + ground.height / 2) {
            player.y = ground.y + ground.height / 2 + player.height / 2;
            isJumping = false;
            playerVelocityY = 0.0f;
        }
    }
}

void UpdateObstacles(EnemyBlock obstacles[], int obstacleCount, float deltaTime, float ground_y_opengl) {
    // �� ��ֹ��� �������� �̵���ŵ�ϴ�.
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles[i].Move(-1.0f * deltaTime); // ��ֹ��� �������� �̵���ŵ�ϴ�.
    }

    // ȭ�� ������ ���� ��ֹ��� Ȯ���ϰ� ��Ȱ���մϴ�.
    for (int i = 0; i < obstacleCount; ++i) {
        if (obstacles[i].x + obstacles[i].width / 2 < -1.0f) {
            // ��ֹ��� ȭ�� ������ ������ �ٽ� �̵���ŵ�ϴ�.
            float heights[2] = { 0.2f, 0.6f }; // ���� ���� ��ֹ��� ����
            float newX = 1.0f + 0.25f * (rand() % 5); // ���ο� x ��ġ�� �������� ����
            int heightIndex = rand() % 2;
            float newHeight = heights[heightIndex];
            float newY = ground_y_opengl + newHeight / 2; // ���� ���� ��ֹ��� ��ġ
            obstacles[i] = EnemyBlock(newX, newY, 0.1f, newHeight, 0.0f, 1.0f, 0.0f); // ��ֹ� ��Ȱ��
        }
    }
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW ���̺귯�� �ʱ�ȭ
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



    // �ʱ� ��ġ ����
    float x_meter = 5.0f; // ���鿡�� 50cm ���������� �̵�
    float y_meter = 10.0f; // ���鿡�� 1m ���� ��ġ

    float x_pixel = meterToPixel(x_meter);
    float y_pixel = meterToPixel(y_meter);

    float x_opengl = pixelToOpenGL(x_pixel, WIDTH);
    float y_opengl = pixelToOpenGL(y_pixel, HEIGHT);

    // �簢���� ũ��
    const float square_size_meter = 5.0f; // 50cm = 5m
    const float border_thickness_meter = 0.3f; // 3cm = 0.3m
    float square_size_opengl = 2.0f * meterToPixel(square_size_meter) / WIDTH; // OpenGL ��ǥ�� ��ȯ
    float border_thickness_opengl = 2.0f * meterToPixel(border_thickness_meter) / WIDTH; // OpenGL ��ǥ�� ��ȯ

    // ȭ�� ����
    float aspectRatio = (float)WIDTH / (float)HEIGHT;

    // ������ y ��ġ
    float ground_y_meter = 10.0f; // 100cm = 10m
    float ground_y_pixel = meterToPixel(ground_y_meter);
    float ground_y_opengl = pixelToOpenGL(ground_y_pixel, HEIGHT);

    // ��ü ����
    Player player(x_opengl, y_opengl, square_size_opengl, square_size_opengl, 1.0f, 0.0f, 0.0f);
    Floor ground(0.0f, ground_y_opengl - 1.0f, 4.0f, 2.0f, 1.0f, 0.78f, 0.06f); // �ʺ� 4.0���� �����Ͽ� ������ �ø�

    // ��ֹ� ����
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

        // ������ (R:0, G:30, B:100)�� ����
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // ������ ���۸� ����� �Լ� ȣ��

        glfwPollEvents();

        // ���� ����
        ApplyPhysics(player, ground, deltaTime);

        // ��ֹ� ������Ʈ
        UpdateObstacles(obstacles, obstacleCount, deltaTime, ground_y_opengl);

        // ��ü �׸���
        ground.Draw();
        player.Draw(border_thickness_opengl);
        for (int i = 0; i < obstacleCount; ++i) {
            obstacles[i].Draw();
        }

        // ���۸� ��ü�Ͽ� ȭ�鿡 �׸��ϴ�.
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

