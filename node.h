/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   node.h
 * Author: nate
 *
 * Created on April 17, 2017, 12:18 PM
 */

#ifndef NODE_H
#define NODE_H


//Define our nodes.  Probably not going to be connected
/*
typedef struct node{

    int x;
    int y; 
    
}node;
*/

class NODE{

public: 
    int num_cities, node_num;
    double xcor, ycor, total_weight;
    bool visited;
    NODE **cities = new NODE*[num_cities];
    //node *next;
    int index;    //keeping an index for cities array
       
public:
    NODE();
    NODE(bool ifVisited, int num, double x, double y);
    void newNode(bool ifVisited, int num, double x, double y);
    double TSP_brute(NODE args);

};


#endif /* NODE_H */

