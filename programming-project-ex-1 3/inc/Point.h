#ifndef POINT_H
#define POINT_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

struct Point {
    float r, g, b, x, y;
    std::string name;
    
    Point(float x, float y, std::string name) {
        r = 0.0;
        g = 0.0;
        b = 0.0;
        
        this->x = x;
        this->y = y;
        this->name = name;
    }
    
    void draw() {
        glColor3f(r, g, b);
        
        glPointSize(20);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }

    void select() {
        r = 1.0;
        draw();
    }

    void deselect() {
        r = 0.0;
        draw();
    }
};

inline std::ostream &operator<<(std::ostream &os, const Point *p) {
    os << "Point " << p->name << " - R: " << p->r << ", G: " << p->g << ", B: " << p->b;
    return os;
}

#endif