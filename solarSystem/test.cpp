#include "texture.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertices.hpp"
#include "vextexObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.hpp"
#include "shader_s.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 70.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vShaderFile.glsl", "fShaderFile.glsl");

    vObject sunObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(sunRadius), sunRadius, GL_STATIC_DRAW);
    sunObject.arrtibArray();

    vObject mercuryObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(mercuryRadius), mercuryRadius, GL_STATIC_DRAW);
    mercuryObject.arrtibArray();

    vObject venusObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(venusRadius), venusRadius, GL_STATIC_DRAW);
    venusObject.arrtibArray();

    vObject earthObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(earthRadius), earthRadius, GL_STATIC_DRAW);
    earthObject.arrtibArray();

    vObject marsObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(marsRadius), marsRadius, GL_STATIC_DRAW);
    marsObject.arrtibArray();

    vObject jupiterObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(jupiterRadius), jupiterRadius, GL_STATIC_DRAW);
    jupiterObject.arrtibArray();

    vObject saturnObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(saturnRadius), saturnRadius, GL_STATIC_DRAW);
    saturnObject.arrtibArray();

    vObject uranusObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(uranusRadius), uranusRadius, GL_STATIC_DRAW);
    uranusObject.arrtibArray();

    vObject neptuneObject;
    glBufferData(GL_ARRAY_BUFFER, sizeof(neptuneRadius), neptuneRadius, GL_STATIC_DRAW);
    neptuneObject.arrtibArray();



    Texture sunTexture("images\\sunBlock.jpg");
    Texture mercuryTexture("images\\mercuryBlock.jpg");
    Texture venusTexture("images\\venusBlock.jpg");
    Texture earthTexture("images\\earthBlock.jpg");
    Texture marsTexture("images\\marsBlock.jpg");
    Texture jupiterTexture("images\\jupiterBlock.jpg");
    Texture saturnTexture("images\\saturnBlock.jpg");
    Texture uranusTexture("images\\uranusBlock.jpg");
    Texture neptuneTexture("images\\neptuneBlock.jpg");
    

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    //ourShader.setInt("texture1", texture1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        ///glActiveTexture(GL_TEXTURE0);
        //sunTexture.BindTexture();

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        
        // render boxes
        // sun
        sunTexture.BindTexture();
        sunObject.vBindArray();
        glm::mat4 sunModel = glm::mat4(1.0f);
        sunModel = glm::rotate(sunModel, static_cast<float>(glfwGetTime()) * sunRotation, glm::vec3(1.0f, 0.3f, 0.5f));
        sunModel = glm::translate(sunModel, cubePositions[0]);
        ourShader.setMat4("model", sunModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Mercury
        mercuryTexture.BindTexture();
        mercuryObject.vBindArray();
        glm::mat4 mercuryModel = glm::mat4(1.0f);
        mercuryModel = mercuryObject.createModel(mercuryModel, cubePositions[1], mercuryRotation, mercuryRevolution);
        ourShader.setMat4("model", mercuryModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Venus
        venusTexture.BindTexture();
        venusObject.vBindArray();
        glm::mat4 venusModel = glm::mat4(1.0f);
        venusModel = venusObject.createModel(venusModel, cubePositions[2], venusRotation, venusRevolution);
        ourShader.setMat4("model", venusModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Earth
        earthTexture.BindTexture();
        earthObject.vBindArray();
        glm::mat4 earthModel = glm::mat4(1.0f);
        earthModel = earthObject.createModel(earthModel, cubePositions[3], earthRotation, earthRevolution);
        ourShader.setMat4("model", earthModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Mars
        marsTexture.BindTexture();
        marsObject.vBindArray();
        glm::mat4 marsModel = glm::mat4(1.0f);
        marsModel = marsObject.createModel(marsModel, cubePositions[4], marsRotation, marsRevolution);
        ourShader.setMat4("model", marsModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Jupiter
        jupiterTexture.BindTexture();
        jupiterObject.vBindArray();
        glm::mat4 jupiterModel = glm::mat4(1.0f);
        jupiterModel = jupiterObject.createModel(jupiterModel, cubePositions[5], jupiterRotation, jupiterRevolution);
        ourShader.setMat4("model", jupiterModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Saturn
        saturnTexture.BindTexture();
        saturnObject.vBindArray();
        glm::mat4 saturnModel = glm::mat4(1.0f);
        saturnModel = saturnObject.createModel(saturnModel, cubePositions[6], saturnRotation, saturnRevolution);
        ourShader.setMat4("model", saturnModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //uranus
        uranusTexture.BindTexture();
        uranusObject.vBindArray();
        glm::mat4 uranusModel = glm::mat4(1.0f);
        uranusModel = uranusObject.createModel(uranusModel, cubePositions[7], uranusRotation, uranusRevolution);
        ourShader.setMat4("model", uranusModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Neptune
        neptuneTexture.BindTexture();
        neptuneObject.vBindArray();
        glm::mat4 neptuneModel = glm::mat4(1.0f);
        neptuneModel = neptuneObject.createModel(neptuneModel, cubePositions[8], neptuneRotation, neptuneRevolution);
        ourShader.setMat4("model", neptuneModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

