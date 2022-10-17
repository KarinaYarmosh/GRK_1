#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <io.h>

#include "Shader_Loader.cpp"
#include "Render_Utils.cpp"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

    // Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
    float time = glfwGetTime();

    glUseProgram(program);

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    glm::mat4 rotation =
            { cos(time),-sin(time),0,0.1,
              sin(time),cos(time),0,0.6,
              0,0, 1,0.6,
              0,0,0,1 };

    rotation = glm::transpose(rotation);

    glm::mat4 translation =
            { 1,0,0,0,
              0,1,0,sin(time),
              0,0,1,0,
              0,0,0,1 };

    translation = glm::transpose(translation);

    //glm::mat4 translation_rotation = rotation*translation;
    glm::mat4 rotation_translation = translation*rotation;

    //glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&translation_rotation);
    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&rotation_translation);
    Core::drawVAOIndexed(quadVAO, 6);
    glUseProgram(0);

    glfwSwapBuffers(window);
    // ZADANIE: Wyswietl czworokat, ktory jednoczesnie przesuwa sie i obraca.
    //
    // Uzyj kodu do translacji i rotacji czworokatu z poprzednich zadan
    //
    // Stworz taka macierz transformacji, ktora powoduje ze czworokat przesuwa sie w gore i w dol ekranu, jednoczesnie obracajac sie.
    // Wyslij stworzona macierz do GPU za pomoca funkcji glUniformMatrix4fv zamiast macierzy "translation" i "rotation" z poprzednich zadan

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("../shaders/shader_1_2.vert", "../shaders/shader_1_2.frag");

    //Przekopiuj kod do ladowania z poprzedniego zadania

    float points[] = {
            -0.3,-0.3,0.,1.,
            0.3,-0.3,0.,1.,
            0.3,0.3,0.,1.,
            -0.3,0.3,0.,1.,
    };
    unsigned int ix[] = {
            0,1,3,
            1,2,3,
    };
    //4 elem po 4 w nim
    quadVAO = Core::initVAOIndexed(points, ix, 4, 4, 6);
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}


//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderScene(window);
        glfwPollEvents();
    }
}
//}