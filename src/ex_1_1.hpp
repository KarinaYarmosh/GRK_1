#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <ctime>
#include "GLM/glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

int rand_int(int min, int max) {
    srand((unsigned)time(NULL));
    return min + (rand() % (max - min + 1));
}

float * getRandomRGBA(){
    float * color = new float[4];
//    color[0] = rand_int(0.0, 255.0);
//    color[1] = rand_int(0.0, 255.0);
//    color[2] = rand_int(0.0, 255.0);
//    color[3] = 1.0;
    color[0] = (float)rand()/ (float)(RAND_MAX / 255.0);
    color[1] = (float)rand() / (float)(RAND_MAX / 255.0);
    color[2] = (float)rand() / (float)(RAND_MAX / 255.0);
    color[3] = 1.0;
    return color;
}
// funkcja renderujaca scene
void renderScene(GLFWwindow* window)
{
    // renderuje scene, jaki kolor
    // ZADANIE: Przesledz kod i komentarze
    // ZADANIE: Zmien kolor tla sceny, przyjmujac zmiennoprzecinkowy standard RGBA
    float* color = getRandomRGBA();
    glClearColor(color[0] / 255.0, color[1]/255.0, color[2]/255.0, color[3]);
    //glClearColor(0.3f, 0.5f, 0.9f, 1.0f);
    //czysti ekran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Powinno byc wywolane po kazdej klatce
    //zamienia ekran - podmienianie
    glfwSwapBuffers(window);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
//raz na poczaku
void init(GLFWwindow* window) {
    //przekazujemy , zminie sie rozmiar buffora, okna
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void shutdown(GLFWwindow* window)
{
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
    //wszystko sie renderuje po kolei
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderScene(window);
        //wszysktkie wydarzenia wykonywaj
        glfwPollEvents();
    }
}
//}