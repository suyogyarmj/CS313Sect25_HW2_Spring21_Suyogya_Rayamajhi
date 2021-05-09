/*
	@Suyogya Rayamajhi
	@CSCI-313
	@Date: 04/11/21
    Homework 2 Program 6
    Write a prefix stack and show how it works (in main).    
*/

#include <iostream>
#include <stack>

using namespace std;

bool check (char);
double calc (string);

int main ()
{
  string exp = "++69+*42/42"; // testing the work in main
  cout << calc (exp) << endl;
  return 0;
}

bool check (char c) // bool function to check if each char is a digit
{
  return isdigit (c); // if char = a digit then it is an operand
}

double calc (string exp) // double function that evaluates the prefix
{
  stack < double >Stack; // declaring a stack that can store double values

  // for loop that iterates through the entire expression
  for (int i = exp.size () - 1; i >= 0; i--) // traverses through the expression
    {  
      if (check(exp[i])) // checking if the value is a digit
	  Stack.push(exp[i] - '0'); // converting to a digit by negating with '0' and pushing to the stack
      else
	  {
        double element1 = Stack.top ();
        Stack.pop (); // popping two elements from the stack
        double element2 = Stack.top ();
        Stack.pop ();

        switch (exp[i]) // using switch case to chose the operation to perform on element1 and element2
            {
            case '+':
            Stack.push (element1 + element2); // if sum
            break;
            case '-':
            Stack.push (element1 - element2); // if difference
            break;
            case '*':
            Stack.push (element1 * element2); // if multiplication
            break;
            case '/':
            Stack.push (element1 / element2); // if division
            break;
            }
	   }
    }

  return Stack.top ();
}

