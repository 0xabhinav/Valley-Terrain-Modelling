#include "data.cpp"
#include "funcs.cpp"
#include<bits/stdc++.h>
#include<GL/freeglut.h>
#include<GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
GLuint VAO, VBO, EBO, programID, texID, terrainVAO, terrainNumVertices;
int frame = 0, Time = 0, timebase=0;
const int FPS = 120;
bool fullScreen = true, maxFPS = false, wireframe = false;
void timer(int) {
    glutPostRedisplay();
    if(!maxFPS)
        glutTimerFunc(1000/FPS, timer, 0);
}
void debugmat(glm::mat4 m)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<m[j][i]<<" ";
        }
        cout<<endl;
    }
}
void fps()
{
    frame++;
	Time=glutGet(GLUT_ELAPSED_TIME);
    if (Time - timebase > 1000) {
        char s[1000];
		sprintf(s,"Valley Terrain Modelling FPS:%4.2f",
			frame*1000.0/(Time-timebase));
		timebase = Time;
		frame = 0;
        glutSetWindowTitle(s);
	}
}
void setup()
{
    programID = LoadProgram("vertex.vs", "fragment.frag");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(float)*7));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    texID = loadTexture("grass.bmp");
    terrainNumVertices = generateTerrain(terrainVAO);
    timer(0);
    // mvp = projection * view * model;
}
void displayMe()
{
    adjustCam();
    glm::mat4 model = glm::rotate(glm::mat4(1.f),glm::radians(-45.f),glm::vec3(1.f,0.f,0.f));
    glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glClearColor(0.2,0.5,0.8,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(terrainVAO);
    // GLuint uid = glGetUniformLocation(programID, "Trans");
    // glUniformMatrix4fv(uid, 1, GL_FALSE, glm::value_ptr(mvp));
    // debugmat(projection);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, terrainNumVertices, GL_UNSIGNED_INT, 0);
    glutSwapBuffers();
    if(maxFPS)
        glutPostRedisplay();
    fps();
}
void keyboard(unsigned char c, int x, int y)
{
    // io.lock();
    // translate(-origin.x,-origin.y,-origin.z);
    switch(c)
    {
        case 'Q':case 'q':exit(0);
        // case 'x':scale(1./scale_ratio,1,1);break;
        // case 'X':scale(scale_ratio,1,1);break;
        // case 'y':scale(1,1./scale_ratio,1);break;
        // case 'Y':scale(1,scale_ratio,1);break;
        // case 'z':scale(1,1,1./scale_ratio);break;
        // case 'Z':scale(1,1,scale_ratio);break;
        // case 'w':case 'W':reflectXZ();break;
        // case 'e':case 'E':reflectXY();break;
        // case 'r':case 'R':reflectYZ();break;
        // case 'j':case 'J':Shear(-scale_ratio,0,0);break;
        // case 'l':case 'L':Shear(scale_ratio,0,0);break;
        // case 'i':case 'I':Shear(0,-scale_ratio,0);break;
        // case 'k':case 'K':Shear(0,scale_ratio,0);break;
        // case 'o':case 'O':Shear(0,0,-scale_ratio);break;
        // case 'm':case 'M':Shear(0,0,scale_ratio);break;
        // case ';':translate(translate_val,0,0);break;
        // case ':':translate(-translate_val,0,0);break;
        // case '\'':translate(0,translate_val,0);break;
        // case '\"':translate(0,-translate_val,0);break;
        // case '/':translate(0,0,translate_val);break;
        // case '?':translate(0,0,-translate_val);break;
        // case '6':rotateZ(theta);break;
        // case '4':rotateZ(-theta);break;
        // case '2':rotateX(theta);break;
        // case '8':rotateX(-theta);break;
        // case '5':rotateY(theta);break;
        // case '0':rotateY(-theta);break;
        // case '.':rotate(6,2,0,theta);break;
        // case '3':rotate(6,2,0,-theta);break;
        // case '1':reflect(6,2,0);break;
        case 'f':case 'F':
        fullScreen = !fullScreen;
        if(fullScreen)
        {
            glutFullScreen();
        }
        else
        {
            glutPositionWindow(0,0);
            glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
        }
        break;
        case '`':case '~':
        maxFPS = !maxFPS;
        if(!maxFPS)
        {
            timer(0);
        }
        break;
        case ' ':
        wireframe = !wireframe;
        if(wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        break;
    }
    // translate(origin.x,origin.y,origin.z);
    // io.unlock();
    // glutPostRedisplay();
}
void mousetoCenter()
{
    static int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    static int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    glutWarpPointer(centerX,centerY);
}
void mouseFunc(int button, int state, int x, int y)
{
    switch(button)
    {
        case 3:camera+=.1f*dirn;break; //scroll down
        case 4:camera+=-.1f*dirn;break; //scroll up
        case 5:camera-=.1f*cross(up,dirn);break; //scroll left
        case 6:camera+=.1f*cross(up,dirn);break; //scroll right
        // case GLUT_RIGHT_BUTTON:camera.z++;break;
    }
}
void mouseMovement(int x, int y) 
{
    static int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    static int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    static bool warpCall = true;
    if(warpCall)
    {
        warpCall = false;
        return;
    }
    static float lastx = x;
    static float lasty = y;
    lastx = (float)x - lastx;
    lasty = (float)y - lasty;
    float sensitivity = 0.1f;
    lastx *= sensitivity;
    lasty *= sensitivity;
    yaw += lastx;
    pitch -= lasty;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    dirn = glm::normalize(front);
    if(1)
    {
        mousetoCenter();
        warpCall = true;
        x = centerX;
        y = centerY;
    }
    lastx = (float)x;
    lasty = (float)y;
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutCreateWindow("LearnOpenGL");
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    GLenum glewError = glewInit();
    if(glewError!= GLEW_OK)
    {
        throw GlewInitError();
    }
    setup();
    glutReshapeFunc(changeSize);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(mouseMovement);
    glutPassiveMotionFunc(mouseMovement);
    glutMainLoop();
    return 0;
}
