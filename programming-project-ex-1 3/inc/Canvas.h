#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <Point.h>
#include <Line.h>

class Canvas : public bobcat::Canvas_ {
    
public:
    Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
        
    }
    ArrayList<Point *> points;
    
    // Creating every edge
    Line line;

    void render() {
        points.append(new Point(-0.8, 0.4, "SFO"));     // 0
        points.append(new Point(-0.4, 0.8, "NYC"));     // 1
        points.append(new Point(0.4, 0.8, "RJ"));       // 2
        points.append(new Point(0.8, 0.4, "PAR"));      // 3
        points.append(new Point(0.0, 0.0, "JHB"));      // 4
        points.append(new Point(-0.8, -0.4, "MOW"));    // 5
        points.append(new Point(-0.4, -0.8, "SYD"));    // 6
        points.append(new Point(0.4, -0.8, "TYO"));     // 7
        points.append(new Point(0.8, -0.4, "BJ"));      // 8
        
        
        // visualizing vertices
        for (int i = 0; i < points.size(); i++) {
            points[i]->draw();
        }
    }
};

#endif