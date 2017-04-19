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
    num = -1;
    xcor = -1;
    ycor = -1;
    
}

NODE::NODE(double number, double x, double y){

    num = number;
    xcor = x;
    ycor = y;   
    
}


void NODE::newNode(double num, double x, double y){
    
    NODE temp(num, x, y);
    
    
    
}



/*
 * Read file at specified path.  Change late to accept arguments when
 * running program if possible 
 * @param filename
 */
int read(string filename){
  
    string PATH = "/home/nate/Documents/"+filename+".txt";
    cout << "Path: " << PATH << "\n";
    
    
    ifstream tspFile;
    //myFile.open("C:/home/nate/documents/test.txt");
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
        //cout << line << "\n";
        found = line.find("DIMENSION");
        
        if(found != string::npos){
            dimFound = true;
            //cout << line << "\n";     //for debugging purposes 
            //cout << line.substr(11) << "\n";
            dimension = atoi(line.substr(11).c_str());
        }        
        
    }
    
    //Get nodes
    bool alreadyFound = false, start_node_gather = false, all_nodes_fnd = false;
    int foundNodeSec, count = 0;
    
    while(getline(tspFile, line) && !all_nodes_fnd){ 
        
        char * curLine = (char *)line.c_str();
        
        if(start_node_gather){
            char * node = strtok(curLine, " \t");            
            
            while(node != NULL){
                
                if (node == "EOF"){
                    all_nodes_fnd = true;
                    break;
                }
                
                //Save node #
                //cout << "NODE: " <<node ;
                node = strtok(NULL, " ");
                
                //Save X coordinate
                //cout << " X: " << node;
                node = strtok(NULL, " ");
                
                //Save Y coordinate
                //cout << " Y: " << node << "\n";
                node = strtok(NULL, " ");
            }
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
double TSP_brute(NODE *cities[]){
    
    

}

/*
 * 
 */
int main(int argc, char** argv) {

    string filename = "";
    
    NODE map;
    
    cout << "Please enter a file name from TSPLIB to test (e.g. a280):  ";
    cin >> filename;
    
    //Initializing array of nodes
    map.num_cities =     read(filename); 
    
    cout << "Cities found: " << map.num_cities << "  "<< sizeof(map.cities);
   // TSP_brute();
    
 
    return 0;
}

