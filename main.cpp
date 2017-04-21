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

NODE::NODE(bool ifVisited, double x, double y){

    visited = ifVisited;
    xcor = x;
    ycor = y;   
    
}


void NODE::newNode(bool ifVisited, double x, double y){
    
    NODE temp(ifVisited, x, y);   
    
    cities[index] = temp;
    
    index++;
    
}



/*
 * Read file at specified path.  Change late to accept arguments when
 * running program if possible 
 * @param filename
 */
int read(string filename, NODE tmp){
    
  
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
    
    //Get nodes
    bool alreadyFound = false, start_node_gather = false, all_nodes_fnd = false;
    int foundNodeSec;
    double saveX, saveY;
    bool save_x_cor, save_y_cor;
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
                (count == 1) ? saveX = atof(node) : (count == 2) ? saveY = atof(node) : count = count;
                
                node = strtok(NULL, " ");
                
                count++;
                
                
                
                
            }
            
            tmp.newNode(false, saveX, saveY);            
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
    
    return dimension;
    
}


/**
 * 
 * 
 * @param argc
 * @param argv
 * @return 
 */
double TSP_brute(NODE arg){
    
    //
    for(int i = 0; i < arg.num_cities; i++){
        printf("Node (X,Y): (%f, %f)\n", arg.cities[i].xcor, arg.cities[i].ycor);
    }
    
}

/*
 * 
 */
int main(int argc, char** argv) {

    string filename = "";
    
    NODE mapOf;
    mapOf.index = 0;
    
    cout << "Please enter a file name from TSPLIB to test (e.g. a280):  ";
    cin >> filename;
    
    //Initializing array of nodes
    //mapOf.num_cities =     read(filename, mapOf);      
    mapOf.num_cities = read(filename, mapOf);
    cout << "Cities found: " << mapOf.num_cities << endl;
    
    TSP_brute(mapOf);
    
    //cout << "Example: " << mapOf.cities[0].xcor << " " << mapOf.cities[0].ycor <<endl;
    
    delete [] mapOf.cities;
    
    
    return 0;
}

