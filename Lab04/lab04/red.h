#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class Red {
private:
    map<string, Router> routers;
    void recalcularTablas();

public:
    void agregarRouter(const string &nombre);
    void eliminarRouter(const string &nombre);
};

#endif
