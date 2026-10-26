#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM; //Location of node
  head[0] = size - 2; //Size of node minus the header
  head[1] = nullptr; //Pointer to next node
}

long int*
freeList::reserve_space( int size ) {
  long int* curr = head;
  
  while(curr != NULL){ //While the current node still exists
    if(size - 2 > head[0]){ //If the current node is too small, go to the next node
      curr = (long int*) curr[1];
    }else{
      head = curr + size; //Sets the head to the address at the end of the size of allocated node
      head[0] = curr[0] - size;
      head[1] = curr[1];
      long int* loc = curr; //Creates a node without a pointer for space we just allocated
      curr[0] = size - 2;
      curr[1] = 0;
      
      return loc;
    }
  }
  std::cout<< "No free space available!\n"<<endl;
  return nullptr;
}

void
freeList::free_space( long int* location ) {
  location[1] = *head; //Sets the pointer of the allocated node to the head
  head = location; //Sets the new head to the previously allocated node
}

void
freeList::coalesce_forward() {
  //Creates variables that keeps track of the current node and the next node
  long int* curr = head;
  long int* next = (long int*)head[1];
  while(next != NULL){
    if((*curr + curr[0] + 2) = *next){ //If the location plus size of the node equals the location of the next node...
      curr[0] = curr[0] + 2 + next[0]; //Add the sizes together
      curr[1] = next[1]; //And set the pointer of the current node to the pointer of the next node
    }
    //Iterate to both of the next nodes in sequence for both variables
    curr = next;
    next = (long int*) next[1];
  }
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
