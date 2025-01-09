// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <GL/glew.h>
#include <GLFW/\glfw3.h>
#include <VertexBuffer.h>
#include <VertexArrayLayout.h>
#include <Renderer.h>
#include <Log.h>
#include <iostream>
#include <Shader.h>
#include <Texture.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context cursrent */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(10);
    // call glewinit to initialize the lib and check if it runs succesfully.
    glewInit();

    {
            // Vertex buffer
        float positions[] = {
            -0.5f, -0.5,  0.0f, 0.0f,         // x, y vertex pos 1
             0.5f, -0.5f, 1.0f,0.0f,         // x, y vertex pos 2
             0.5f,  0.5f, 1.0f,1.0f,        // x, y vertex pos 3
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        GLLOGCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLLOGCALL(glEnable(GL_BLEND));

        VertexBuffer vb(sizeof(float) * 4 * 4, positions);
        VertexArray va;
        VertexArrayLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        //index buffer
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        IndexBuffer ib(6, indices);

        /*shader*/
        //appox pipeline: draw call () -> vertext shader -> fragment shader -> see result on screen~
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color",1.0f, 0.8f, 0.2f, 1.0f);

        Texture texture("res/texture/background.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        
        Renderer renderer;
        float r = 0;
        float increment;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            shader.SetUniform4f("u_Color", r, 0.8f, 0.2f, 1.0f);
            renderer.Draw(va, ib, shader);
            
            increment = (r > 1.0) ? -0.6f : 0.05f;
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}