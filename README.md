# 2020 CG HW1 Spec
###### tags: `NCTU Computer Graphics`

* [OpenGL API](https://rb.gy/ocp4jq)
* [Demo Schedule](https://rb.gy/0wwthz) (10/20-10/22): Register from 10/18 00:00
* HW1 DueDate: 10/19 23:59:59
---

:::info

***Computer Graphics 2020 - Homework 1***

In this homework, you’re required to write a program that implements several visual effects using GLFW, FreeGlut.

:::

* In CG_HW1_EXAMPLE, you can execute and show a plane with texture.

    [![](https://i.imgur.com/J8ai3by.jpg =400x)](https://i.imgur.com/J8ai3by.jpg)

* Follow the TODO instructions and write your code in project CG_HW1.



## Object Overview

* Overview:

    1. Render a **3D cube** with texture and let it rotate over time. (20%)

    2. Render two **spheres** with two textures and let them rotate over time. (20%)
    
    3. Add lighting component to the scene. (10%)
    
    4. Some keyboard callback functions for **switching** three objects (2 spheres and 1 cube). (20%)

    5. Use keyboard or mouse event to change **camera view**. (10%)

    6. Report (CH/EN is available) (20%)
    
    7. Bonus: Any other design about multiple spheres/objects can be a plus. (10%)

* Preview (Click the Picture for full resolution pictures)
    * [Demo Video](https://rb.gy/zericx)

| Cube | Sphere(texture1) | Sphere(texture2) |
| -------- | -------- | -------- |
|[![](https://i.imgur.com/Kaz5xQr.jpg =400x)](https://i.imgur.com/Kaz5xQr.jpg) | [![](https://i.imgur.com/v2hqi76.jpg =400x)](https://i.imgur.com/v2hqi76.jpg) |[![](https://i.imgur.com/gn9Dfnl.jpg =400x)](https://i.imgur.com/gn9Dfnl.jpg) |


## Details in each part

1. Render a 3D cube with texture and let cube rotate over time. (20%)
    * Cube:
        * position: (0, 0, 0)
        * length: 1
        * rotation axis: (1, 1, 0)

    * Hint function:
        ```
        void glTexCoord2f(GLfloat s, GLfloat t)
        void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
        void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
        
        double glfwGetTime(void)
        ```
    * Use **glEnable** to make your 3D cube realistic.


2. Render two **spheres** with two textures and let them rotate over time. (20%)
    * Sphere:
        * position: (0, 0, 0)
        * radius: 1
        * slice: 360
        * stack: 180

    * You should **implement the sphere function by yourself**, that is, you cannot use gluSphere().
    ![](https://i.imgur.com/5o5EpiI.jpg =300x)



3. Add lighting component to the scene. (10%)
    * light:
        * position: (10, 10, 10)
        * ambient color: (0.5, 0.5, 0.5, 1.0)
        * diffuse color: (1.0, 1.0, 1.0, 1.0)

    * Hint function:
        ```
        void glNormal3f(GLfloat s, GLfloat t)
        void glLightfv (GLenum light, GLenum pname, const GLfloat *params)
        ```


4. Some keyboard callback functions for **switching** three objects (2 spheres and 1 cube). (20%)

    * Any key on the keyboard is available. (Must be specified in the report)
 



5. Use keyboard or mouse event to change **camera view**. (10%)
    * Camera:
        * position: (0, 0, 5)
        * center: (0, 0, -1)
        * up vector: (0, 1, 0)

    * GLFW input reference:
    https://www.glfw.org/docs/3.3/group__input.html

    * You should be able to translate the camera view in all dimensions(x, y, z-axis).

    * Hint function:
        ```
        void gluPerspective(GLdouble fovy, GLdouble aspect,GLdouble zNear,GLdouble zFar)
        void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
                       GLdouble centerx, GLdouble centery, GLdouble centerz,
                       GLdouble upx, GLdouble upy, GLdouble upz)
        ```






6. Report (CH/EN is available) (20%)
    * Specify your programming environment.
    * Explain how you implement the above reqirements. 
    * Describe the problems you met and how you solved them.
    * Illustrate extra features of your design. (optional)






7. Bonus: Any other design can be a plus. (10%)
    * Be creative! All extra features are welcomed! :+1: 
    * Some Recommendations:
        * Rotate Camera view.
        * Add other shapes.



## Deadline

Please hand in your code and report (in a .zip file) using E3, deadline will be at **2020/10/19 23:59:59**.

Penalty of 10 points of the value of the assignment per late day. 

## Running Enviornment

Visual Studio 2019 is recommended.

You may specify your target environment by providing a ```README``` or ```MAKEFILE```, but it’s better to inform the TAs beforehand, just in case we cannot execute your program.

## Upload Format

:::danger
If your uploading format doesn't match our requirement, there will be penalty to your score.
:::

Please hand in your project file and report as ```STUDENTID_hw1.zip``` ​ to e3 platform.

e.g. ```309123456_hw1.zip```

## References

* [Sphere Wiki](https://en.wikipedia.org/wiki/Sphere)
* [GLFW-input guide](https://www.glfw.org/docs/latest/input_guide.html)
* [GLM library](https://openframeworks.cc/documentation/glm/)
* [FreeGlut library](http://freeglut.sourceforge.net/docs/api.php)


