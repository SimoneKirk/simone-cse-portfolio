#ifndef LINE_H
#define LINE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <Point.h>
#include <ArrayList.h>

struct Line {
    void createLine(Point a, Point b) {
        // set color to black and line width to 5 pixels
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(5.0);

        glBegin(GL_LINES);
            // line segment
            glVertex2f(a.x, a.y);
            glVertex2f(b.x, b.y);
        glEnd();
    }
};

#endif