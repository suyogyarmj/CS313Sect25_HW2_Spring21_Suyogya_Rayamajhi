/*
	@Suyogya Rayamajhi
	@CSCI-313
	@Date: 04/11/21
    Homework 2 Program 1 Part b
    Postfix.txt Commenting
*/
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"

using namespace std;

// headers of the functions used
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk);

int main()
{
    bool expressionOk; // bool expression creation that checks for the error in input

    char ch; // char value creation that reads the next element from the string

    stackType<double> stack(100); // stack creation that is used for the calculation

    ifstream infile; // fstream objects declarations
    ofstream outfile;

    //attempt to open the text file containing the expression
    infile.open("RpnData.txt"); // try to open the text file

    if (!infile) // if file cannot be accessed, the issue is reported and the program is terminated
    {
        cout << "Cannot open the input file. "
            << "Program terminates!" << endl;
        return 1;
    }

    //create an output file to write the answer
    outfile.open("RpnOutput.txt"); // output file creation to write the result

    outfile << fixed << showpoint; // since the file writes in 'doubles', we round off to 2 decimal places
    outfile << setprecision(2);

    infile >> ch; // reading the 1st character in the file

    while (infile) // creation of a while loop that reads multiple expressions and terminates when the file ends
    {
        stack.initializeStack(); // initializing the stack to empty

        expressionOk = true; // set the value of the flag to true for every new expression

        outfile << ch; // writing the character

        evaluateExpression(infile, outfile, stack, ch, expressionOk); // calling the evaluateExpression function

        printResult(outfile, stack, expressionOk); // writing the obtained result in the outfile

        infile >> ch; // next expression
    }  

    infile.close(); // closing the fstream objects
    outfile.close();

    return 0;

} 

void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk)
{
    double num; // creating a temp variable to store the numbers read from the file

    while (ch != '=') // this reads the entire expression until the end
    {
        switch (ch) // char check, if it is a number or an operand
        {
        case '#': // if its a number (#) case
            inpF >> num; // the number is read and stored in num
            outF << num << " "; // the number is written to the output file
            if (!stack.isFullStack()) // checking if the stack is full
                stack.push(num); // the value in 'num' is pushed to stack if its not full
            else // the program is terminated if the stack is full
            {
                cout << "Stack overflow. "
                    << "Program terminates!" << endl;
                exit(0); 
            }

            break;
        default: // case if it is not a number
            evaluateOpr(outF, stack, ch, isExpOk); // calling evaluateOpr function
        }

        if (isExpOk) // checking if the expression is ok i.e if there is any error
        {
            inpF >> ch; // reading the next character
            outF << ch; // writing to the output file

            if (ch != '#') // if the char is not a number, a space is included between the numbers and the operands
                outF << " ";
        }
        else // if the expression is NOT ok
            discardExp(inpF, outF, ch); // skip over the bad expressions until a good expression is obtained
    } 
} 

void evaluateOpr(ofstream& out, stackType<double>& stack, // function to evaluate operators & pushing the results obtained to the stack
    char& ch, bool& isExpOk)
{
    double op1, op2; // creation of two temp double variables

    if (stack.isEmptyStack()) // if stack is empty we know something is not right
    {
        out << " (Not enough operands)"; // user alert
        isExpOk = false; // isExpOk is set to false so the program can discard this expression
    }
    else // if stack is not empty, we proceed forward
    {
        op2 = stack.top(); // op2 is set equal to the stack top
        stack.pop(); // we pop the stack top

        if (stack.isEmptyStack()) // checking again is stack is empty
        {
            out << " (Not enough operands)"; // user alert
            isExpOk = false; // again, isExpOk is set to false so the program can discard this expression
        }
        else
        {
            op1 = stack.top(); // op1 is set to stack top
            stack.pop(); // pop the stack top

            switch (ch) // switch statement to char to evaluate the operation we need
            {
            case '+': // in case of addition
                stack.push(op1 + op2); // sum is pushed to stack
                break;
            case '-': // in case of subtraction
                stack.push(op1 - op2); // the difference is pushed to stack
                break;
            case '*': // in case of multiplication
                stack.push(op1 * op2); // product is pushed to stack
                break;
            case '/': // in case of division
                if (op2 != 0) // avoid division by 0
                    stack.push(op1 / op2); // quotient is pushed to the stack
                else // if division by 0 is required
                {
                    out << " (Division by 0)"; // user alert
                    isExpOk = false; // the expression is discarded
                }
                break;
            default: // operator is incorrect if none of the case is applied
                out << " (Illegal operator)"; // user alert
                isExpOk = false; // discarding the expression
            }
        } 
    } 
} 

void discardExp(ifstream& in, ofstream& out, char& ch) // function that prints the remaining expression to the output file if there is an error
{
    while (ch != '=') // read the string until the "=" sign
    {
        in.get(ch); // reading the next character
        out << ch; // print the character
    }
} 

// fucntion checks for remaining errors and writes the result after the "=" sign
void printResult(ofstream& outF, stackType<double>& stack,
    bool isExpOk)
{
    double result; // temporary value creation for result storage

    if (isExpOk) // true if there is any error
    {
        if (!stack.isEmptyStack()) // if the expression is written correctly, the stack contains a number
        {
            result = stack.top(); // result is set equal to the top stack
            stack.pop(); /// pop the top value in the stack

            if (stack.isEmptyStack()) // check is stack is empty
                outF << result << endl; // if the stack is empty, we print the result
            else
                outF << " (Error: Too many operands)" << endl; // If stack is non-empty then we know an error has ocurred
        } 
        else // if the stack was received empty by the function then we know there is an error and alert the user
            outF << " (Error in the expression)" << endl;
    }
    else // if the expressionOk =  false then there is an error and we alert the user
        outF << " (Error in the expression)" << endl; // user alert

    outF << "_________________________________" // underline that seperates multiple expressions
        << endl << endl;
} 