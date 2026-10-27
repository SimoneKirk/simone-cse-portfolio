#include <Application.h>
#include <bobcat_ui/dropdown.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Canvas.h>

using namespace bobcat;
using namespace std;

void Application::initData() {
    fstream file;

    // read vertices from file
    file.open("./assets/vertices.csv", ios::in);
    if (file.is_open()) {
        string line;
        
        while(getline(file, line)) {
            cities.append(new Vertex(line));
        }

        file.close();
    }

    // add vertices to graph
    for (int i = 0; i < cities.size(); i++) {
        g.addVertex(cities[i]);
    }
    
    // read edges from file and add them as edges to the graph
    file.open("./assets/edges.csv", ios::in);
    if (file.is_open()) {
        string line;
        
        while(getline(file, line)) {
            stringstream ss(line);
            string from, to, time, cost;

            getline(ss, from, ',');
            getline(ss, to, ',');
            getline(ss, time, ',');
            getline(ss, cost, ',');

            g.addEdge(cities[stoi(from)], cities[stoi(to)], stoi(time));
        }

        file.close();
    }
}

void Application::initInterface() {
    window = new Window(25, 75, 800, 400, "Simple Navigation Project");

    fromDropdown = new Dropdown(25, 25, 350, 25, "Origin");
    toDropdown = new Dropdown(25, 75, 350, 25, "Destination");

    for (int i = 0; i < cities.size(); i++) {
        fromDropdown->add(cities[i]->data);
        toDropdown->add(cities[i]->data);
    }

    searchDropdown = new Dropdown(25, 125, 350, 25, "Search Options");
    searchDropdown->add("Cheapest Price");
    searchDropdown->add("Fastest Route");
    searchDropdown->add("Least Layovers");
    searchButton = new Button(25, 175, 350, 25, "Search");

    map = new Canvas(25, 225, 350, 150);

    resultScrollArea = new Fl_Scroll(425, 25, 350, 350, "Results");
    resultScrollArea->align(FL_ALIGN_TOP_LEFT);
    resultScrollArea->box(FL_THIN_UP_BOX);

    // register events
    ON_CLICK(searchButton, Application::onClick);

    window->show();
}

void Application::onClick(bobcat::Widget* sender) {
    if (sender == searchButton) {

        resultScrollArea->clear();

        int fromIndex = fromDropdown->value();
        int toIndex = toDropdown->value();

        map->points[fromIndex]->select();
        map->points[toIndex]->select();
        
        
        cout << map->points[fromIndex] << endl;
        cout << map->points[toIndex] << endl;

        int searchType = searchDropdown->value();
        Waypoint* path;

        // run search algorithm
        if (searchType == 0) {
            path = g.ucs(cities[fromIndex], cities[toIndex]);
        } else if (searchType == 1) {
            path = g.dfs(cities[fromIndex], cities[toIndex]);
        } else {
            path = g.bfs(cities[fromIndex], cities[toIndex]);
        }

        if (path) {
            cout << "Found path" << endl;
            int y = resultScrollArea->y() + 10;

            Waypoint* temp = path;

            while(temp != nullptr) {
                resultScrollArea->add(new TextBox(440, y, 300, 25, temp->vertex->data));

                y += 40;

                if (temp->parent != nullptr) {
                    resultScrollArea->add(new TextBox(440, y, 300, 25, "\t Flight Time:" + to_string(temp->weight) + " hours"));
                    y += 40;
                }
                temp = temp->parent;
            }
            
            map->redraw();
            window->redraw();

        } else {
            cout << "There is no path" << endl;
        }
    }
}

Application::Application() {
    initData();
    initInterface();
    cout << g;
}