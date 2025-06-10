﻿#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "frame_timer.h"
#include "load_mesh.h"

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);  // 스케일 시 normal 보정
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_dir[] = { -1.0f, -1.0f, -1.0f, 0.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat ka[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat kd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ks[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
}

void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000);  // OpenGL에서는 n, f 양수
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

}



void draw_bunny() {
    for (const Triangle& tri : gTriangles) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; ++i) {
            unsigned int idx = tri.indices[i];
            const Vector3& n = gNormals[idx];
            const Vector3& v = gPositions[idx];
            glNormal3f(n.x, n.y, n.z);
            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("OpenGL Bunny");

    GLenum err = glewInit(); // GLUT 윈도우 생성 후 호출해야 함
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW initialization failed\n");
        return -1;
    }

    init_timer();                     // ← FPS 측정용 쿼리 초기화
    load_mesh("bunny.obj");           // ← bunny 로딩
    init();                           // ← 조명 및 머티리얼 설정
    setProjection();                  // ← 투영 설정

    glutDisplayFunc(display);        // ← frame_timer.cpp의 display() 사용
    glutMainLoop();

    return 0;
}
