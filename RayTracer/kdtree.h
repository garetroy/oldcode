#ifndef _KDNODE_H_
#define _KDNODE_H_

#include <iostream>
#include <cstdlib>
#include <vector>

#include "boundingbox.h"
#include "triangle.h"
#include "vector.h"

using std::vector;

class Kdnode{
    
    public:
                Kdnode(void);
        Kdnode* Build(vector<Triangle*> &tris);
        bool    Hit(Kdnode *node, Ray &ray, Screen &screen, double &u, double &v, double &y); 
        bool              init;
    
    private:
        Boundingbox       bbox;
        Kdnode*           left;
        Kdnode*           right;
        vector<Triangle*> triangles;
};

#endif
