/*
	@Suyogya Rayamajhi
	@CSCI-313
	@Date: 04/11/21
    Homework 2 Program 6
   Create your own stack functions to do the following:
    a. List all the elements in the stack
    b. Iterate through the stack and change one of the values based on its position   
*/

#include <iostream>
#include <string>

using namespace std;

//using linked list to implement stack
struct Node // node declaration
{ 
	string data;
	Node* next;
};

class stk //stack implementation
{
private:
	int size;
	Node* top;
public:
	stk();
	~stk();
	void push(string str);
	string pop();
	bool isEmpty();
	void print();
	void replace(int i, string);
};

stk::stk() 
{
	//constructor to allocate memory
	size = 0;
	top = nullptr;
}

stk::~stk() 
{
	//destructor to deallocate memory
	
	if (!isEmpty()) {
		while (!isEmpty()) {
			pop();
		}
	}
	else cout << "Empty stack!";
}

void stk::push(string str) 
{
	Node* temp = new Node;
	temp->data = str; // initializing data into the temp 
	temp->next = top; // putting top pointer reference into temp next
	top = temp; // temp = top of the stack
	size++;
}

string stk::pop() 
{
	if (!isEmpty()) 
    {
		Node* temp;
		temp = top; // top is assigned to temp
		top = top->next; // assigning second node to the top
		size--;
		return temp->data;
	}
	else cout << "Empty stack!";
}

bool stk::isEmpty() // function to check if stack is empty
{
	return(size == 0);
}

//function for printing all elements in the stack
void stk::print() 
{
	if (isEmpty()) 
    cout << "Empty stack!"; //check if empty
	else {
		Node* temp;
		temp = top;
		while (temp != NULL) 
        {
			cout << temp->data << endl; //printing node data
			temp = temp->next; // assigning temp next to temp
		}
	}
}

//iterate thorugh stack and change an element based on its position... part b
void stk::replace(int i, string s) {
	if (isEmpty()) {
		cout << "Empty stack!";
		return;
	}
	int counter = 0;    // checking against the input
	Node* temp = top;
	while (true) 
    {
		if (counter == i) // perform until the position specified is reached, in this case, 3
        {
			temp->data = s;
			break;
		}
		if (temp->next != nullptr) 
        {
			temp = temp->next;
			counter++;
		}
		else break;
	}
	
}

int main() 
{
	stk stack1;

	stack1.push("y"); // pushing elements to the stack
    stack1.push("t");
    stack1.push("r");
    stack1.push("e");
	stack1.push("w");
	stack1.push("q");

	stack1.print(); // displaying stack elements 

	stack1.replace(3, "Bazinga!"); // replacing the element in the 3rd position

	cout << endl;

	stack1.print();
}