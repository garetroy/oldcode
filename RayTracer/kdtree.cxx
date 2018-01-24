#include "kdtree.h"
#include <typeinfo>

Kdnode::Kdnode(void)
{
    init = false;
}

Kdnode* 
Kdnode::Build(vector<Triangle*>& tris)
{
    int     i       = 0;
    Kdnode* node    = (Kdnode*) new Kdnode();
    node->triangles = tris;
    node->left      = NULL;
    node->right     = NULL;
    node->bbox      = Boundingbox();
    node->init      = true;
    
    if(tris.size() == 0)
        return node;
    
    if(tris.size() == 1){
        node->bbox             = *tris[0]->GetBoundingBox();
        node->left             = new Kdnode();
        node->right            = new Kdnode();
       return node;
    } 

    Boundingbox *tempbox;
    //#pragma omp parallel for default(shared) private(i) firstprivate(tempbox)
    for(i = 0; i < tris.size(); i++){
        tempbox = tris[i]->GetBoundingBox();
        node->bbox.ExpandBoundingBox(tempbox);
    }

    Vec3 midpt   = Vec3(0,0,0);
    Vec3 current = Vec3(0,0,0);
    for(i = 0; i < tris.size(); i++){
        tris[i]->GetMidPoint(current);
        midpt[0] = midpt[0] + (current[0] * (1.0 / tris.size()));
        midpt[1] = midpt[1] + (current[1] * (1.0 / tris.size()));
        midpt[2] = midpt[2] + (current[2] * (1.0 / tris.size()));
    }

    vector<Triangle*> left_tris; 
    vector<Triangle*> right_tris;
    char axis = node->bbox.LongestAxis();

    //#pragma omp parallel for default(shared) private(i)
    for(i = 0; i < tris.size(); i++){

        tris[i]->GetMidPoint(current); 

        switch(axis){
            case 'x':
                midpt[0] >= current[0] ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
                break;
            case 'y':
                midpt[1] >= current[1] ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
                break;
            case 'z':
                midpt[2] >= current[2] ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
                break;
        }
    }

    if (left_tris.size() == 0 && right_tris.size() > 0) left_tris = right_tris;
    if (right_tris.size() == 0 && left_tris.size() > 0) right_tris = left_tris;

    int matches,j = 0;
    //#pragma omp parallel for collapse(2) private(i,j) shared(matches,right_tris,left_tris) 
    for(i = 0; i < left_tris.size(); i++){
        for(j = 0; j < right_tris.size(); j++){
            if(left_tris[i] == right_tris[i])
                matches++;
        }
    }
    
     if(matches / (double) left_tris.size() < 0.5 && matches / (double) right_tris.size() < 0.5){
        node->left  = Kdnode::Build(left_tris);
        node->right = Kdnode::Build(right_tris);

   } else {
        node->left             = new Kdnode();
        node->right            = new Kdnode();
        node->left->triangles  = vector<Triangle*>();
        node->right->triangles = vector<Triangle*>();
    }
   return node;
}

bool
Kdnode::Hit(Kdnode *node, Ray &ray, Screen &screen,double &u, double &v, double &y) const 
{
    if(node->bbox.Hit(ray)){
        bool hit_tri = false;
        if(node->left->init == false && node->right->init == false){
            for(int i = 0; i < triangles.size(); i++){
                if(triangles[i]->Hit(ray,screen,u,v)){
                    screen.DrawTriangle(v,y,triangles[i]->colors);
                    hit_tri = true;
                }
            }
            return hit_tri;
        } else {
            if(node->left->triangles.size() > 0 || node->right->triangles.size() > 0){
                bool hitleft  = Hit(node->left,ray,screen,u,v,y);
                bool hitright = Hit(node->right,ray,screen,u,v,y);
                return hitleft || hitright;
            } else {
                for(int i = 0; i < node->triangles.size(); i++) {
                    if(node->triangles[i]->Hit(ray,screen,u,v)){
                        screen.DrawTriangle(v,y,node->triangles[i]->colors);
                        hit_tri = true;
                    }
                }
                return hit_tri;
            }
        }
   } 
    return false;
}
