using namespace std;
#include <iostream>
#include <vector>
template <typename T>

class LinkedList {
  
public:
  struct Node {
    T data;
    Node* next;
    Node* prev;
  };

  LinkedList() { //default constructor
    _nodecount = 0;
    //_head = new Node;
    //_tail = new Node;
  };

  ~LinkedList() { //destructor
    Node* currentnode = _head;

    while (currentnode != nullptr) { //iterates through all nodes and deletes each one
      Node* nextnode = currentnode->next; //pointer object initialized for each following node object
      delete currentnode; //the current node iteration is deleted
      currentnode = nextnode; //current node pointer gets updated to the following node object
    }

  };

  void AddHead(T newData) { //creates a new Node at the front of the list to store the passed in parameter
    Node* newnode = new Node; //initializes new node object
    newnode->data = newData; //assigns data to the node object
    newnode->next = _head; //assigns the head to the node after
    newnode->prev = nullptr; //the node before the tail node is always set to null

    if (_head) { //checks if the head is empty. done to connect head and tail together               
        _head->prev = newnode; //assigns the new node object to the previous node
    } else {                   
        _tail = newnode; //if it's not empty, assign the newnode to the tail  
    }

    _head = newnode; //head is assigned as newnode
    
    _nodecount += 1;

    
  };

  void AddTail(T newData) { //ditto, but creates a new Node at the end of the list
    Node* newnode = new Node;
    newnode->data = newData;
    newnode->next = nullptr;
    newnode->prev = _tail;
    
    if (_tail) {               
        _tail->next = newnode; 
    } else {                   
        _head = newnode;       
    }

    _tail = newnode;

    _nodecount += 1;
  }

  void AddNodesHead(T newData[], int size) { //Inserts an array of values as nodes at the beginning of the list
    int i= size-1; //i variable initialized, which is the highest array position possible
    while (i!=-1) { //while loop keeps going until i position [0] is reached
      AddHead(newData[i]); //node object added
      //cout << "added " <<newData[i];
      i -=1;
    }
  };

  void AddNodesTail(T newData[], int size) {
    for (int i=0 ; i<size ; i++) { //for loop starts at array position [1] and iterates through all other values
      AddTail(newData[i]);
    } 
  };

  int NodeCount() {return _nodecount;}; //returns the current node count in the list

  void PrintForward() { //iterates through all the nodes and prints out their values one at a time
    Node* currentnode = _head;
    while (currentnode != nullptr) { //keeps iterating until the next node will be nullptr
      cout << currentnode->data << endl; //prints the current node iteration's value
      currentnode=currentnode->next; //updates current node pointer to the next one
    }
  };

  void PrintReverse() { //ditto, but in reverse
    Node* currentnode = _tail; // Start at the tail
    if (!currentnode) {
      cout<< "list is empty." << endl;
    }
    while (currentnode != nullptr) { // Iterate until currentnode is nullptr
        cout << currentnode->data << endl; // Print current node's value
        currentnode = currentnode->prev;
    }
  };

  Node* getHead() {return _head;}; //returns the head pointer
  
  Node* getTail() {return _tail;};

  Node* GetNode(T index) const { //returns a node pointer at the index
    if (index >= _nodecount) { //throwns an exception if the index is out of range
      throw out_of_range("Index is out of range.");
    }

    Node* currentnode = _head;
    for (int i=0 ; i<index ; i++) { //iterates through all nodes until it reaches the index position
      currentnode = currentnode->next;
    }
    return currentnode; //when the above loop exhausts, return the node pointer at the index position
  };

  Node* Find(T DataValue) const { //finds the first node with a data value matching the passed in parameter
    Node* currentnode = _head;
    for (int i=0 ; i<_nodecount ; i++) {
      if (currentnode->data == DataValue) { //if the current node's data matches the parameter, return that node pointer
        return currentnode;
      }
      currentnode = currentnode->next;
    }

    return nullptr; //if the above loop exhausts and no matching pointer found, return nullptr
  };

  void FindAll(vector<Node*>& DataStorage, T& DataValue) { //finds all nodes which match the parameter value and stores it to the vector
    Node* currentnode = _head;
    for (int i=0 ; i<_nodecount ; i++) {
      if (currentnode->data == DataValue) {
        DataStorage.push_back(currentnode);
      }
      currentnode = currentnode->next;
    }
  };

  void Set(const LinkedList& otherList) { //set function will set this linkedlist's variables to the other list's
    //this->_nodecount = otherList._nodecount;
    this->_nodecount = otherList._nodecount;
    
    Node* currentnode = _head;

    while (currentnode != nullptr) { //iterates through all nodes and deletes each one
      Node* nextnode = currentnode->next; //pointer object initialized for each following node object
      delete currentnode; //the current node iteration is deleted
      currentnode = nextnode; //current node pointer gets updated to the following node object
    }

    currentnode = otherList._head;
    while (currentnode != nullptr) {
      AddHead(currentnode->data);
      currentnode = currentnode->next;
    }


    //this->_head = otherList._head;
    //this->_tail = otherList._tail;
    
  }; //WILL NEED TO UPDATE TO MAKE A DEEP COPY FROM THE OTHER LIST HERE ^^^

  LinkedList(const LinkedList& otherList) { //copy constructor
    _head = nullptr;
    _tail = nullptr;

    this->_nodecount = otherList._nodecount;
    
    Node* currentnode = _head;

    while (currentnode != nullptr) { //iterates through all nodes and deletes each one
      Node* nextnode = currentnode->next; //pointer object initialized for each following node object
      delete currentnode; //the current node iteration is deleted
      currentnode = nextnode; //current node pointer gets updated to the following node object
    }

    currentnode = otherList._head;
    while (currentnode != nullptr) {
      AddTail(currentnode->data);
      currentnode = currentnode->next;
    }
  };

  LinkedList& operator=(const LinkedList& otherList) { //copy assignment operator
    if (this == &otherList) {
      return *this;
    }

    Node* currentnode = _head;

    while (currentnode != nullptr) { //iterates through all nodes and deletes each one
      Node* nextnode = currentnode->next; //pointer object initialized for each following node object
      //cout << "deleted node " << currentnode->data << endl;
      delete currentnode; //the current node iteration is deleted
      currentnode = nextnode; //current node pointer gets updated to the following node object
    }
    
    _head = nullptr;
    _tail = nullptr;
    _nodecount = 0;

    Node* newnode = otherList._head;
    while (newnode != nullptr) {
      AddTail(newnode->data);
      newnode = newnode->next;
    }

    this->_nodecount = otherList._nodecount;

    return *this;
  };

  T& operator[](int index) {
    if (index < 0) {
      throw out_of_range("Invalid index.");
    }
    
    Node* currentnode = _head;
    for (int i=0 ; i<index ; i++) {
      if (currentnode == nullptr) {
        throw out_of_range("Invalid index.");
      }
      currentnode = currentnode->next;
    }
    return currentnode->data;
  };

  void InsertAfter(Node* nodePointer, T value) { //inserts a new node w/ the passed in value after the passed in node pointer
    Node* currentnode = _head;
    for (int i=0 ; i<_nodecount ; i++) {
      if (currentnode == nodePointer) { //if it finds a node pointer that matches the parameter..
        Node* newnode = new Node; //creates new node object
        newnode->data = value;
        newnode->next = currentnode->next; 
        currentnode->next = newnode;
        _nodecount += 1;
        break; 
      }
      
      currentnode = currentnode->next;

    }
  };

  void InsertBefore(Node* nodePointer, T value) { //ditto, but before the passed in node
    Node* currentnode = _head;
    for (int i=0 ; i<_nodecount ; i++) {
      if (currentnode == nodePointer) {
        Node* newnode = new Node;
        newnode->data = value;
        //cout << "adding node " << newnode->data << endl;
        newnode->next = currentnode;
        currentnode = currentnode->prev;
        currentnode->next = newnode;
        _nodecount += 1;
        break;
      }

      currentnode = currentnode->next;
    }
  };

  void InsertAt(T value, int index) { //inserts a new node at the index-th location
    if (index < 0) { //checks if the index is a negative number
      throw out_of_range("Invalid index.");
    }

    Node* currentnode = _head;
    for (int i=0 ; i<index-1 ; i++) {
       if (currentnode == nullptr) {
        throw out_of_range("Invalid index.");
      }
      currentnode = currentnode->next; //iterates to the node at the index
    }

    if (index==0) { //adds a head if the index is 0
      AddHead(value);
    }
    else { //inserts after for all other cases
      InsertAfter(currentnode,value);
    }
  };
  
  bool operator==(const LinkedList& otherList) { //overload equality operator
    Node* list1currentnode = _head; //two separate pointers initialized to compare both lists
    Node* list2currentnode = otherList._head;
    bool identical = true;

    if (_nodecount != otherList._nodecount) { //first checks to see whether their lengths are equal. sets identical to false if otherwise
      identical = false;
    }

    for (int i=0 ; i<_nodecount ; i++)
      if (list1currentnode->data != list2currentnode->data) { //checks both lists and if they dont match at an index, set identical to false
        identical = false;
      }
      
      list1currentnode = list1currentnode->next;
      list2currentnode = list2currentnode->next;

    return identical;
  };

  Node* Head() {
    return _head;
  };

  Node* Tail() {
    return _tail;
  };

  bool RemoveHead() { //Deletes the first node in the list
    if (_head != nullptr) { //checks if the head node is not null. if so, delete it
      Node* newnode = _head->next;
      delete _head;
      _head = newnode;
      _nodecount -= 1;
      return true;
    }
    else { //if the head node is null (empty), return false
      return false;
    }
  };
  
  bool RemoveTail() { //Deletes the last node in the list
    if (_tail != nullptr) {
      Node* newnode = _tail->prev;
      newnode->next = nullptr;
      delete _tail;
      _tail = newnode;
      _nodecount -= 1;
      return true;
    }
    else {
      return false;
    }
  };

  int Remove(T value) { //Removes all nodes containing values matching the passed in parameter
    int removednodes = 0; //removednodes variable initialized. will keep track of how many nodes were removed
    Node* currentnode = _head;
    while (currentnode != nullptr) {
      if (currentnode->data == value) { //if the current node's value matches the parameter, delete it
        Node* newnode = currentnode->prev;
        newnode->next = currentnode->next;
        delete currentnode;
        currentnode = newnode;
        removednodes += 1;
        _nodecount -= 1;
      }

      currentnode = currentnode->next;
    }

    return removednodes;
  };

  bool RemoveAt(int index) { //Delete the node at the index, returning whether or not it was successful
    if (index < 0) { //first checks if the index is valid
      //throw out_of_range("Invalid index.");
      return false;
    }
    
    Node* currentnode = _head;
    for (int i=0 ; i<index ; i++) {
      if (currentnode == nullptr) { //traverses through list to get the node at the index
        //throw out_of_range("Invalid index.");
        return false;
      }
      currentnode = currentnode->next;
    }

    Node* newnode = currentnode->prev;
    newnode->next = currentnode->next;
    delete currentnode;
    currentnode = newnode;
    _nodecount -= 1;
    return true;
  };

  void Clear() { //deletes all nodes
    Node* currentnode = _head;

    while (currentnode != nullptr) { //iterates through all nodes and deletes each one
      Node* nextnode = currentnode->next; //pointer object initialized for each following node object
      delete currentnode; //the current node iteration is deleted
      currentnode = nextnode; //current node pointer gets updated to the following node object
      _nodecount -= 1; //node count reduced by 1 each time
    }

    _head = nullptr; //once the loop exhausts and all nodes are deleted, set the head and tail pointers back to nullptr
    _tail = nullptr;

  };

  void PrintForwardRecursive(Node* node) {

  };

  void PrintReverseRecursive(Node* node) {

  };

private:
  Node* _head = nullptr;
  Node* _tail = nullptr;
  int _nodecount;
};