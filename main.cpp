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


using namespace std;


/*
 *Read file at specified path.  Change late to accept arguments when
 * running program if possible 
 * 
 */
void read(string filename){

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
    while(getline(tspFile, line) && !all_nodes_fnd && count != 50){ // added count strictly for debuggin purposes
        
        char * curLine = (char *)line.c_str();
        //cout << line << endl;
        
        if(start_node_gather){
            char * node = strtok(curLine, " \t");            
            
            while(node != NULL){
                
                if (node == "EOF"){
                    all_nodes_fnd = true;
                    break;
                }
                
                cout << "NODE: " <<node ;
                node = strtok(NULL, " ");
                cout << " X: " << node;
                node = strtok(NULL, " ");
                cout << " Y: " << node << "\n";
                node = strtok(NULL, " ");
            }
        }
        
        if(!alreadyFound) {
           
            foundNodeSec = line.find("NODE_COORD_SECTION");
            //(foundNodeSec != string::npos) ? start_node_gather = true : start_node_gather = false;
            //cout << "FOUND: " << foundNodeSec << " SNG: " << start_node_gather << endl;
            //(foundNodeSec != string::npos) ? cout << "NODECOORDSEC: "<< line << endl : start_node_gather = false;
            if(foundNodeSec != string::npos){
                start_node_gather = true;
                alreadyFound = true;
            }
        }
        
        //count++;
    
    }
        
    cout << "through: " << count << endl;
    cout << "Dimension: " << dimension;
    
    tspFile.close();
    
}


/*
 * 
 */
int main(int argc, char** argv) {

    string filename = "";
    
    cout << "Please enter a file name from TSPLIB to test (e.g. a280):  ";
    cin >> filename;
    read(filename);  
    
 
    return 0;
}

