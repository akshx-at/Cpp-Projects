/* Your code here! */

#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>
#include "dsets.h"



void DisjointSets::addelements(int num){

// This function focuses on creating a vector if int where initially each value is set to i1 in the vector
// where we also create a new node for each value in the vector representing an individual subset for each element
for (int i = 0; i < num; i++){
    elementvect.push_back(-1);
}
}

void DisjointSets::setunion(int a, int b){
    // set union is used to set the values of b to a
        int roota = find(a); 
	    int rootb = find(b);
        if (roota == rootb) return;
	    int Size = elementvect[roota] + elementvect[rootb];
	    if (elementvect[roota] <= elementvect[rootb]) { 
		    elementvect[rootb] = roota; 
		    elementvect[roota] = Size; 
	    } else { 
		    elementvect[roota] = rootb; 
		    elementvect[rootb] = Size; 
        }
    }




int DisjointSets::size(int elem){
    // finds the number of nodes in the up tree containing the element
    // untill it reaches a negative value increment the number
    // as soon as it reaches the negative vlaue it means it has reached the root
    return -elementvect[find(elem)];
}

int DisjointSets::find(int elem){
    if(elementvect[elem] < 0){
        return elem;
    }
    //  int temp =  find(elementvect[elem]);
    //  elementvect[elem] = temp;
     return find(elementvect[elem]);
}