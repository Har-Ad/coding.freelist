#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size - 2;
  head[1] = NULL;
}

long int*
freeList::reserve_space( int size ) {
  long int* curr = head;
  
  while(head != NULL){
    if(size - 2 > head[0]){
      curr = long int* curr[1];
    }else{
      head = curr + size;
      head[0] = curr[0] - size;
      head[1] = curr[1];
      long int* loc = curr;
      curr[0] = size - 2;
      curr[1] = 0;
      
      return loc;
    }
  }
  std::cout<< "No free space available!\n"<<endl;
  return nullptr;
}

void
freeList::free_space( long int* location ) {\
  location[1] = (long int)head;
  head = location;
}

void
freeList::coalesce_forward() {
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
