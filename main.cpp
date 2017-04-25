/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nate
 *
 * Created on April 15, 2017, 5:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <math.h>
//#include <array>
#include "node.h"


using namespace std;





/**
 * 
 * @param NULL
 */
NODE::NODE(){
    visited = false;
    xcor = -1;
    ycor = -1;
    
}

NODE::NODE(bool ifVisited, int num, double x, double y){

    visited = ifVisited;
    node_num = num;
    xcor = x;
    ycor = y;   
    
}

/**
 * 
 * @param ifVisited - determines whether or not the nodes has been visited
 * @param x -  x coordinate
 * @param y -  y coordinate
 */
void NODE::newNode(bool ifVisited, int num, double x, double y){
    
    NODE *temp = new NODE(ifVisited, num, x, y);   
    
    cities[index] = temp;
    
    index++;
    
    
    
}



/*
 * Read file at specified path.  Change later to accept different path arguments when
 * running program if possible 
 * @param filename, NODE object
 */
int read(string filename, NODE *tmp){
    
  
    string PATH = "/home/nate/Documents/"+filename+".txt";
    cout << "Path: " << PATH << "\n";
    
    
    ifstream tspFile;
    tspFile.open(PATH.c_str());
    
    if(tspFile.is_open())
        cout <<"opened file!\n";
    else 
        cerr << "no bueno\n";
    
    
    string line;
    int found, dimension;
    bool dimFound = false;
    
    //Get Dimension
    while(getline(tspFile, line) && (!dimFound)){
        found = line.find("DIMENSION");
        
        if(found != string::npos){
            dimFound = true;
            dimension = atoi(line.substr(11).c_str());
        }        
        
    }
    
    //Identifiers for getting nodes
    bool alreadyFound = false, start_node_gather = false, all_nodes_fnd = false;
    int foundNodeSec;
    double saveX, saveY;
    int saveNum = 0;
    //NODE temp;  //for some reason it didn't like this
    
    while(getline(tspFile, line) && !all_nodes_fnd){ 
        
        char * curLine = (char *)line.c_str();
        
        //Letting us know that we can start collecting data points
        if(start_node_gather){
            char * node = strtok(curLine, " \t");    
            int count = 0;
            
            while(node != NULL){
                
                if (node == "EOF"){
                    all_nodes_fnd = true;
                    break;
                }
                                
                //Save X or Y cor based on where we are in the line
                (count == 0) ? saveNum = atof(node) : (count == 1) ? saveX = atof(node) : (count == 2) ? saveY = atof(node) : count = count;
                
                node = strtok(NULL, " ");
                
                count++;
                
                
                
                
            }
            
            tmp->newNode(false, saveNum, saveX, saveY);            
        }
        
        if(!alreadyFound) {
           
            foundNodeSec = line.find("NODE_COORD_SECTION");
            if(foundNodeSec != string::npos){
                start_node_gather = true;
                alreadyFound = true;
            }
            
        }
        
    
    }
      
    cout << "Dimension: " << dimension << endl;
    
    tspFile.close();
    
    delete tmp;
    
    return dimension;
    
}


double CalculateDistances(NODE *startVertex, NODE *arg ){
        
    //NODE nextNode;
    double distance;
    double nearest = 100000000000000;   //Nearest Neighbor 
    int i, neighbor;
    
    for(i = 0; i < arg->num_cities; i++){
        
        distance = sqrt( pow((arg->cities[i]->ycor - startVertex->ycor), 2) + pow((arg->cities[i]->xcor - startVertex->xcor), 2) );
        
        if(distance < nearest && arg->cities[i]->visited == false && distance != 0){
            nearest = distance;
            neighbor = i;
            arg->cities[i]->visited = true;
        }
    
    }
    
    return nearest + CalculateDistances(arg->cities[neighbor], arg);
}

/**
 * 
 * 
 * @param NODE object
 * @return eventually will return brute force solution to TSP 
 */
double TSP_brute(NODE *arg){
    
    double weight2NxtCity;
    
    
    
    for(int i = 0; i < arg->num_cities; i++){
        
       printf("Node (X,Y): (%f, %f)\n", arg->cities[i]->xcor, arg->cities[i]->ycor);
       
    }
    
   
   // for(int i = 0; i < arg.num_cities; i++){
        
      //arg->total_weight = CalculateDistances(arg->cities[0], arg);  
      //cout << "total weight: " << arg.total_weight;
     
    //}
    
     
    
}


/*
 * 
 */
int main(int argc, char** argv) {

    string filename = "";
    
    NODE *mapOf = new NODE;
    mapOf->index = 0;
    
    cout << "Please enter a file name from TSPLIB to test (e.g. a280):  ";
    cin >> filename;
    
    //Initializing array of nodes      
    mapOf->num_cities = read(filename, mapOf);
    cout << "Cities found: " << mapOf->num_cities << endl;
    
    TSP_brute(mapOf);
    
    
    delete [] mapOf->cities;
    
    
    return 0;
}

