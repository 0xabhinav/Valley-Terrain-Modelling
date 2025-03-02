#include "data.cpp"
#include "funcs.cpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <algorithm>

// Replace GL headers with Emscripten versions
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <GL/glut.h>
#else
#include<GL/freeglut.h>
#include<GL/glew.h>
#include <glm/glm.hpp>
#endif
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
Font font;
void timer(int) {
    // yaw+=.1;
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
            cout<<fixed<<setprecision(1)<<m[j][i]<<" ";
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
        setWindowTitle(s);
	}
}
void setup()
{
    vector<string> available_fonts = {"assets/font.fnt","assets/comic-sans.fnt","assets/karumbi.fnt"};
    font.loadFont(available_fonts[1]);
    font.drawPrep(readFile("assets/helptext.txt"),-.8,.8,1,-.8,.001,1.,0.,1.);
    programID = LoadProgram("assets/vertex.vs", "assets/fragment.frag");
    waterProgramID = LoadProgram("assets/vertex.vs", "assets/fragwater.frag");
    texID = loadTexture("assets/grass_ground.bmp");
    // exit(0);
    terrainNumVertices = generateTerrain(terrainVAO);
    waterNumVertices = generateWater(waterVAO);
    cloudTexID = loadTexture("assets/cloud.png");
    cloudProgramID = LoadProgram("assets/vertexCloud.vs", "assets/fragmentCloud.frag");
    cloudVAO = setupClouds();
    sunTexID = loadTexture("assets/sun.png");
    objNumVertices = loadOBJ("assets/birch_tree.obj",objVAO);
    objTexID = loadTexture("assets/grass.bmp");
    objProgramID = LoadProgram("assets/vertex.vs", "assets/fragmentOBJ.frag");
    shadowTexID = GenShadows();
    timer(0);
    // mvp = projection * view * model;
}

void displayMe()
{
    glEnable(GL_DEPTH_TEST);
    adjustCam();
    // glm::mat4 model = glm::rotate(glm::mat4(1.f),glm::radians(-45.f),glm::vec3(1.f,0.f,0.f));
    glm::mat4 model(1.f);
    glUniform3fv(glGetUniformLocation(programID, "sunRayDirn"), 1, glm::value_ptr(sundirn));
    glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glClearColor(0.2,0.5,0.8,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(showHelp)
    {
        glEnable( GL_BLEND );  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(wireframe)
            setPolygonMode(false);            
        font.drawNow();
        if(wireframe)
            setPolygonMode(true);
        glDisable( GL_BLEND );  
    }
    drawSun(cloudVAO, cloudProgramID, sunTexID);
    drawTrees();
    drawClouds(cloudVAO, cloudProgramID, cloudTexID);
    drawTerrain();
    drawWater();
    glutSwapBuffers();
    if(maxFPS)
        glutPostRedisplay();
    fps();
}

#ifdef __EMSCRIPTEN__
void emscriptenMouseLock() {
    if (mouseLock) {
        emscripten_request_pointerlock("#canvas", true);
    } else {
        emscripten_exit_pointerlock();
    }
}
#endif

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
        case 'h':case 'H':
        showHelp = !showHelp;
        break;
        case 'u':case 'U':
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
            setPolygonMode(true);
        }
        else
        {
            setPolygonMode(false);
        }
        break;
        case 'c': mouseLock = !mouseLock;
        if(mouseLock)
        {
            #ifdef __EMSCRIPTEN__
            emscriptenMouseLock();
            #endif
            glutSetCursor(GLUT_CURSOR_NONE);
        }
        else
        {
            #ifdef __EMSCRIPTEN__
            emscriptenMouseLock();
            #endif
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
        break;
        case '+':
        scaleFac+=.1;
        break;
        case '-':
        if(scaleFac>.2f)
            scaleFac-=.1;
        break;
        case 'w':case 'W': camera+=scrollmult*glm::normalize(glm::vec3(dirn.x,0,dirn.z));
        clampCam(camera);
        break;
        case 's':case 'S': camera-=scrollmult*glm::normalize(glm::vec3(dirn.x,0,dirn.z));
        clampCam(camera);
        break;
        case 'a':case 'A': camera-=scrollmult*glm::normalize(glm::vec3(-dirn.z,0,dirn.x));
        clampCam(camera);
        break;
        case 'd':case 'D': camera+=scrollmult*glm::normalize(glm::vec3(-dirn.z,0,dirn.x));
        clampCam(camera);
        break;
        case 'z':case 'Z': camera.y+=scrollmult;
        clampCam(camera);
        break;
        case 'x':case 'X': camera.y-=scrollmult;
        clampCam(camera);
        break;
    }
    // translate(origin.x,origin.y,origin.z);
    // io.unlock();
    // glutPostRedisplay();
}
void mousetoCenter()
{
    warpPointer(centerX,centerY);
}
void mouseFunc(int button, int state, int x, int y)
{
    glm::vec3 temp;
    switch(button)
    {
        case 3:
                camera+=scrollmult*dirn;
            break; //scroll down
        case 4:
                camera+=-scrollmult*dirn;
                break; //scroll up
        case 5:
        temp =glm::normalize(cross(up,dirn));
            camera-=scrollmult*temp;
        break; //scroll left
        case 6:
        temp =glm::normalize(cross(up,dirn));
            camera+=scrollmult*temp;
        break; //scroll right
        // case GLUT_RIGHT_BUTTON:camera.z++;break;
    }
    clampCam(camera);
}

void computeYawPitch(float dx, float dy) {
    float sensitivity = 0.1f;
    dx *= sensitivity;
    dy *= sensitivity;
    yaw += dx;
    pitch -= dy;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void mouseMovement(int x, int y) 
{
    static bool warpCall = true;
    static float lastx = x;
    static float lasty = y;
    if(warpCall)
    {
        warpCall = false;
        lastx = centerX;
        lasty = centerY;
        return;
    }
    float dx = (float)x - lastx;
    float dy = (float)y - lasty;
    computeYawPitch(dx, dy);
    #ifndef __EMSCRIPTEN__
    if(mouseLock)
    {
        mousetoCenter();
        warpCall = true;
        x = 10;
        y = 10;
    }
    #endif

    lastx = (float)x;
    lasty = (float)y;
}

#ifdef __EMSCRIPTEN__
EM_BOOL emscriptenResizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    glutReshapeWindow(uiEvent->windowInnerWidth, uiEvent->windowInnerHeight);
    return EM_TRUE;
}
#endif

int main(int argc, char **argv)
{
    float val = height(10,10);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutCreateWindow("Valley Terrain Modelling");
    #ifndef __EMSCRIPTEN__
        glutFullScreen();
        fullScreen = true;
        glutSetCursor(GLUT_CURSOR_NONE);
        mouseLock = true;
        GLenum glewError = glewInit();
        if(glewError!= GLEW_OK)
        {
            throw GlewInitError();
        }
    #else
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, emscriptenResizeCallback);
    #endif
    setup();
    glutReshapeFunc(changeSize);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(mouseMovement);
    glutPassiveMotionFunc(mouseMovement);
    #ifdef __EMSCRIPTEN__
    // For emscripten to render the terrain properly, we need this hack
    displayMe();
    glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    #endif
    glutMainLoop();
    return 0;
}
