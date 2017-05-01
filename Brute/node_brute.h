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

typedef struct node{

    double xcor;
    double ycor;
    bool visited;
    int num;
    node * neighbor;
    
}node;


#endif /* NODE_H */

