#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stb_image.h>
#include <math.h>
#include <vector>

#define M_PI 3.14159265358979323846

#define SPHERE_RADIUS 1
#define SPHERE_SLICE 360
#define SPHERE_STACK 180

#define WASD_SPEED 0.08
#define SCROLL_SPEED 0.1

using namespace std;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void create_sphere_vertices(double r, int slice, int stack);
void my_sphere(unsigned int texture);
void my_cube();

//------------- TO DO ------------- 
// Declaration: ex. mouse events variables, camera positions ...
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int texture1, texture2, texture3;
vector<vector<float>> sphereVertices;

unsigned int currentImage = 1;
float xCameraPosition = 0.0f;
float yCameraPosition = 0.0f;
float zCameraPosition = 5.0f;
float xCameraTarget = 0.0f;
float yCameraTarget = 0.0f;

bool rotation = TRUE;
bool rotationReverse = FALSE;

int main() {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG_HW1_TA", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //------------- TO DO ------------- 
    // Generate textures

    glGenTextures (1, &texture1);
    glGenTextures (1, &texture2);
    glGenTextures (1, &texture3);

    for (int i = 0; i < 3; ++i) {
        switch (i) {
            case 0:
                glBindTexture (GL_TEXTURE_2D, texture1);
                break;
            case 1:
                glBindTexture (GL_TEXTURE_2D, texture2);
                break;
            case 2:
                glBindTexture (GL_TEXTURE_2D, texture3);
                break;
        }
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // load image, create texture and generate mipmaps
        int w, h, nrChannels;
        stbi_set_flip_vertically_on_load (true); // tell stb_image.h to flip loaded texture's on the y-axis.

        unsigned char* data;
        switch (i) {
            case 0:
                data = stbi_load ("../resources/container.jpg", &w, &h, &nrChannels, 0);
                break;
            case 1:
                data = stbi_load ("../resources/earth.jpg", &w, &h, &nrChannels, 0);
                break;
            case 2:
                data = stbi_load ("../resources/moon.jpg", &w, &h, &nrChannels, 0);
                break;
            default:
                data = NULL;
                break;
        }

        if (data) {
            cout << "Success to load texture #" << i + 1 << endl;
            glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            cout << "Failed to load texture #" << i + 1 << endl;
        }

        glBindTexture (GL_TEXTURE_2D, 0);
    }

    create_sphere_vertices(SPHERE_RADIUS, SPHERE_SLICE, SPHERE_STACK);

    //------------- TO DO ------------- 
    // Declare variables

    float angle = 0.0f;
    float time = glfwGetTime();

    //------------- TO DO ------------- 
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat AmbientLight[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat DiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat LightPosition[] = {10, 10, 10, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);


    while (!glfwWindowShouldClose(window)) {

        //------------- TO DO ------------- 
        //Declare your variables
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        //Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, width / (GLfloat)height, 0.1, 1000);

        // ModelView Matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(xCameraPosition, yCameraPosition, zCameraPosition, xCameraTarget, yCameraTarget, -1.0f, 0.0f, 1.0f, 0.0f);

        //Viewport Matrix
        glViewport(0, 0, width, height);

        //------------- TO DO ------------- 
        // Enable GL capabilities
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // clear
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //------------- TO DO ------------- 
        // Draw, Rotate, and Switch objects
        // glPushMatrix();

        glRotatef(angle, 1.0, 1.0, 0.0);

        switch (currentImage) {
            case 1:
                my_cube();
                break;
            case 2:
                my_sphere(texture2);
                break;
            case 3:
                my_sphere(texture3);
                break;
            default:
                currentImage = 1;
                break;
        }

        // glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();

        float delta_time = glfwGetTime() - time;
        if (delta_time >= 0.01) {
            time = glfwGetTime();
            if (rotation) {
                if (rotationReverse) {
                    if (currentImage == 1) {
                        angle += 0.8;
                    } else {
                        angle += 5;
                    }
                    if (angle >= 360) {
                        angle -= 360;
                    }
                } else {
                    if (currentImage == 1) {
                        angle -= 0.8;
                    } else {
                        angle -= 5;
                    }
                    if (angle <= 0) {
                        angle += 360;
                    }
                }
            }
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}



static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //------------- TO DO ------------- 
    // Define your keyboard event

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        currentImage = 1;
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        currentImage = 2;
    }

    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        currentImage = 3;
    }



    if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        yCameraPosition += WASD_SPEED;
        yCameraTarget += WASD_SPEED;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        yCameraPosition += WASD_SPEED;
        yCameraTarget += WASD_SPEED;
    }


    if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        xCameraPosition -= WASD_SPEED;
        xCameraTarget -= WASD_SPEED;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        xCameraPosition -= WASD_SPEED;
        xCameraTarget -= WASD_SPEED;
    }


    if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        yCameraPosition -= WASD_SPEED;
        yCameraTarget -= WASD_SPEED;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        yCameraPosition -= WASD_SPEED;
        yCameraTarget -= WASD_SPEED;
    }


    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        xCameraPosition += WASD_SPEED;
        xCameraTarget += WASD_SPEED;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        xCameraPosition += WASD_SPEED;
        xCameraTarget += WASD_SPEED;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //------------- TO DO ------------- 
    // Define your mouse event
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        rotation = !rotation;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rotationReverse = !rotationReverse;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //------------- TO DO ------------- 
    // (optional) Define your scroll event
    zCameraPosition -= yoffset * SCROLL_SPEED;
}

void create_sphere_vertices(double r, int slice, int stack) {

    float xPosition, yPosition, zPosition;

    float sliceCount = 2 * M_PI / slice;
    float stackCount = M_PI / stack;
    float sliceAngle, stackAngle;

    for (int i = 0; i < stack; ++i) {

        // -pi/2 to pi/2
        stackAngle = (i * stackCount) - (M_PI / 2);
        yPosition = r * sin(stackAngle);    // r * sin(u)

        for (int j = 0; j <= slice; ++j) {

            // 0 to 2pi
            sliceAngle = j * sliceCount;

            zPosition = r * cos(stackAngle) * cos(sliceAngle);    // r * cos(u) * cos(v)
            xPosition = r * cos(stackAngle) * sin(sliceAngle);    // r * cos(u) * sin(v)

            vector<float> coords;

            coords.push_back(xPosition);
            coords.push_back(yPosition);
            coords.push_back(zPosition);

            sphereVertices.push_back(coords);
        }
    }
}

void my_sphere(unsigned int texture) {
    //------------- TO DO ------------- 
    // Draw your sphere

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    for (int i = 0; i < sphereVertices.size() - (SPHERE_SLICE + 1); ++i) {

        if ((i + 1) % (SPHERE_SLICE + 1) == 0) {
            continue;
        }

        for (int j = 0; j < 4; ++j) {

            int PolyVertex;

            switch (j) {
                case 0:
                    PolyVertex = i;
                    break;
                case 1:
                    PolyVertex = i + 1;
                    break;
                case 2:
                    PolyVertex = i + SPHERE_SLICE + 2;
                    break;
                case 3:
                    PolyVertex = i + SPHERE_SLICE + 1;
                    break;
            }

            float x = sphereVertices[PolyVertex][0];
            float y = sphereVertices[PolyVertex][1];
            float z = sphereVertices[PolyVertex][2];

            float s, t; // Texture coords

            s = PolyVertex % (SPHERE_SLICE + 1);
            s = s / SPHERE_SLICE;

            t = PolyVertex / SPHERE_SLICE;
            t = t / SPHERE_STACK;

            glNormal3f(x / SPHERE_RADIUS, y / SPHERE_RADIUS, z / SPHERE_RADIUS);
            glTexCoord2f(s, t);
            glVertex3f(x, y, z);
        }
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void my_cube() {
    //------------- TO DO ------------- 
    // Draw your cube

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBegin(GL_QUADS);

    ////////////////// Front face //////////////////
    glNormal3f(0.0f, 0.0f, -1.0f);
    // Bottom left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Top right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Bottom right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    ////////////////// Back face //////////////////
    glNormal3f(0.0f, 0.0f, 1.0f);
    // Bottom Left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Top Left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Top Right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Bottom Right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    ////////////////// Left face //////////////////
    glNormal3f(-1.0f, 0.0f, 0.0f);
    // Far Bottom
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Far Top
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Near Top
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Near Bottom
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    ////////////////// Right face //////////////////
    glNormal3f(1.0f, 0.0f, 0.0f);
    // Far Bottom
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    // Far Top
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Near Top
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Near Bottom
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    ////////////////// Top face //////////////////
    glNormal3f(0.0f, -1.0f, 0.0f);
    // Near Left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Far Left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Far Right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Near Right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    ////////////////// Bottom face //////////////////
    glNormal3f(0.0f, 1.0f, 0.0f);
    // Near Left
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Far Left
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Far Right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    // Near Right
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

}