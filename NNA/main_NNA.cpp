/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main_NNA.cpp
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
#include <algorithm>
#include <time.h>
#include "node_NNA.h"


using namespace std;


node *root = NULL;
node *tail = NULL;
int dimension = 0;

//Creating new node in linked list
void newNode(int num, double x, double y){

    node* temp = new node;
    temp->xcor = x;
    temp->ycor = y;
    temp->neighbor = NULL;
    temp->visited = false;
    temp->num = num;
    
    
    if(root == NULL){
        root = temp;
        tail = temp;
        temp = NULL;
    }else{
    
        tail->neighbor = temp;        
        tail = temp;
    }

}



/*
 * Read file at specified path.  Change later to accept different path arguments when
 * running program if possible 
 * @param filename
 */
int read(string filename){
    
  
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
            
            while(node != NULL ){
                
                if (node == "EOF"){
                    all_nodes_fnd = true;
                    break;
                }
                                
                //Save X or Y cor based on where we are in the line
                (count == 0) ? saveNum = atof(node) : (count == 1) ? saveX = atof(node) : (count == 2) ? saveY = atof(node) : count = count;
                
                node = strtok(NULL, " ");
                
                count++;
                
            }
            newNode(saveNum, saveX, saveY);
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


double CalculateDistance(node *current, node *prospect){

    double x = current->xcor - prospect->xcor;
    double y = current->ycor - prospect->ycor;
    
    x = pow(x, 2);
    y = pow(y, 2);    
    
    return sqrt(x+y);

}

/**
 * Compute Brute force solution to this problem 
 *
 */
double NNA(){
    
    node *tmp;
    tmp = root;
    
    int index = 0;
    
    node **array = new node*[dimension];
    
    while(tmp->neighbor != NULL){
        //printf("Node %d (x,y): (%f, %f)\n", tmp->num, tmp->xcor, tmp->ycor);
         
        array[index] =  tmp;
        index++;
        
        tmp = tmp->neighbor;
       
    }
    
    int i = 0, j, nodes_left = dimension - 1;
    double minDistance = 100000000000000;
    double tour_length = 0;
    int nearest_index = 0;
    array[0]->visited = true;

    while(i != -1){
        
        double distance = 0;
        minDistance = 100000000000000000;       //resetting our minDistance
        
        for(j = 0; j < dimension; j++){
          
        
             if(!(array[j]->visited) && i != j ){
                    distance = CalculateDistance(array[i], array[j]);
            
                 if(distance < minDistance && (distance != 0)) {
                     
                     minDistance = distance;
                     nearest_index = j;
                   }
            
            }
            
        }
        
        array[nearest_index]->visited = true;
        nodes_left--;
        i = nearest_index; 
        tour_length += minDistance;
        
        if(nodes_left == 0){
            
           distance = CalculateDistance(array[nearest_index], array[0]);
            tour_length += distance;
            i = -1;
        }
    
    }
  
    cout << "Tour Length: " << tour_length << endl;
    
    delete [] array;
 
}


/*
 * 
 */
int main(int argc, char** argv) {

    string filename = "";   
    clock_t t1, t2;
    
    t1 = clock();
    cout << "Please enter a file name from TSPLIB to test (e.g. a280):  ";
    cin >> filename;
    
    dimension = read(filename);
    NNA();
    
    t2 = clock();
    float diff((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Runtime: " << seconds;
    
    return 0;
}

