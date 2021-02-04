#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyShader.h"
#include "global.h"
#include "../imgui/imgui_internal.h"

unsigned int loadTexture(const char* path);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

inline float to_radius(float degree)
{
    return degree * IM_PI / 180.0f;
}

inline float to_degree(float radius)
{
    return radius * 180.0f / IM_PI;
}


int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#ifdef __APPLE__
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Cube", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

     // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif

    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // set up state
    bool cube_change_by_time = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // create shader
    Shader shader(
    "/Users/yvettemuki/Documents/code/OpenGL/HelloCube/src/1.0.cube.vs.glsl",
    "/Users/yvettemuki/Documents/code/OpenGL/HelloCube/src/1.0.cube.fs.glsl"
    );
    glColor3i(255, 180, 0);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            //back
            -0.5f, -0.5f, -0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 0.0f,

            //front
            -0.5f, -0.5f,  0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,    142.0/255.0, 84.0/255.0, 233.0/255.0,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   142.0/255.0, 84.0/255.0, 233.0/255.0,   0.0f, 0.0f,

            // left
            -0.5f,  0.5f,  0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 0.0f,

            // right
            0.5f,  0.5f,  0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,    61.0/255.0, 126.0/255.0, 170.0/255.0,   1.0f, 0.0f,

            // bottom
            -0.5f, -0.5f, -0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 1.0f,

            // top
            -0.5f,  0.5f, -0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,    1.0, 228.0/255.0, 122.0/255.0,          1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   1.0, 228.0/255.0, 122.0/255.0,          0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3,    // front
        0, 3, 4, 0, 4, 5,    // right
        0, 5, 6, 0, 6, 1,    // up
        1, 6, 7, 1, 7, 2,    // left
        7, 4, 3, 7, 3, 2,    // down
        4, 7, 6, 4, 6, 5     // back
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    unsigned int textureID = loadTexture("/Users/yvettemuki/Documents/code/OpenGL/HelloCube/src/container.jpg");

    // shader configuration
    shader.use();
    shader.setInt("texture1", 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        //Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 3. Show the simple window.
        bool show_another_window;
        ImGui::Begin("Control Panel", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("try to click the buttons");
        if (ImGui::Button("Change the Cube Color"))
        {
            std::cout << "test change color" << std::endl;
        }
        ImGui::Checkbox("set cube change by time", &cube_change_by_time);
        ImGui::Text("Edit Background Color");
        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        float x_radius;
        float y_radius;
        float z_radius;
        ImGui::SliderAngle("x-axis", &x_radius, -180.0f, 180.0f);
        ImGui::SliderAngle("y-axis", &y_radius, -180.0f, 180.0f);
        ImGui::SliderAngle("z-axis", &z_radius, -180.0f, 180.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // detecting imgui setting
        if (cube_change_by_time)
        {
            float time = glfwGetTime();
            shader.setFloat("time", time);
        }
        else
        {
            shader.setFloat("time", 1);
        }


        // draw cubes
        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(to_degree(x_radius)), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate by x
        model = glm::rotate(model, glm::radians(to_degree(y_radius)), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate by x
        model = glm::rotate(model, glm::radians(to_degree(z_radius)), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate by x
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)display_h / (float)display_w, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

unsigned int loadTexture(const char *path)
{
    // load and create texture
    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(
            path,
            &width,
            &height,
            &nrChannels,
            0
    );
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return ID;
}

