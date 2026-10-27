#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include <FL/Fl_Scroll.H>
#include <Graph.h>
#include <Canvas.h>

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    bobcat::Dropdown* fromDropdown;
    bobcat::Dropdown* toDropdown;

    bobcat::Dropdown* searchDropdown;
    bobcat::Button* searchButton;

    Fl_Scroll* resultScrollArea;
    Canvas* map;
    bobcat::Image* image;

    Graph g;
    ArrayList<Vertex*> cities;

    void initData();
    void initInterface();
    void initMap();

    void onClick(bobcat::Widget* sender);
    
public:
    Application();
};

#endif