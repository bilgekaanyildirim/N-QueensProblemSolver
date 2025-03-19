#include <iostream>
#include <vector>
#include "stack.h"
#include <fstream>

using namespace std;

// Structure to hold the state of a queen's position on the board
struct state
{
    int columnNum;   // Column where the queen is placed
    int* matrixSt;   // Pointer to the current state of the matrix

    // Default constructor initializing default values
    state()
    {
        columnNum = 0;
        matrixSt = nullptr;
    }

    // Parameterized constructor to set column and matrix state
    state(int columnNumber, int* matrixState)
    {
        columnNum = columnNumber;
        matrixSt = matrixState;
    }
};

int main()
{
    int boardSize;

    // Prompt the user to enter the board size for the N-Queens problem
    cout << "Enter the value of N for the N-Queens problem: ";
    cin >> boardSize;

    // Validate input for board size
    if (boardSize <= 0)
    {
        cout << "Invalid input. Please enter a positive integer" << endl;
        return 0;
    }

    // Function declarations
    void PrintMatrix(int** matrix, const int & boardSize);
    void InitializeMatrix(int** matrix, const int & boardSize);
    void PlaceQueen(int** matrix, const int & row, const int & column, const int & boardSize);
    void RemoveQueen(int** matrix,  int  row,  int  column, const int & boardSize);

    // Dynamically allocate a matrix to represent the board
    int** matrix = new int* [boardSize];
    for (int i = 0; i < boardSize; i++)
    {
        matrix[i] = new int[boardSize];
    }

    InitializeMatrix(matrix, boardSize); // Initialize the board to 0 (empty)

    // Stack to keep track of the queen placement states
    MyStack<state> stack(boardSize + 1);
    stack.Push(state(-1, matrix[0])); // Initial state in the stack
    vector<vector<int>> solutions;     // Stores all valid solutions
    vector<int> solution;              // Temporary solution for a single configuration

    int row = 0;                       // Start from the first row
    int col = 0;                       // Start from the first column

    // Backtracking loop to find all solutions
    while (!stack.IsEmpty())
    {
        // If solution is complete, store it and backtrack
        if (solution.size() == boardSize)
        {
            solutions.push_back(solution);
            col = solution.back();    // Retrieve last column
            RemoveQueen(matrix, row, col, boardSize);
            col += 1;
            solution.pop_back();
        }

        bool isFound = false;         // Flag to indicate if a valid position was found

        // Try placing a queen in each column of the current row
        for (int i = col; i < boardSize && !isFound; i++)
        {
            if (matrix[row][i] == 0)  // If position is not attacked
            {
                PlaceQueen(matrix, row, i, boardSize);  // Place queen
                solution.push_back(i);                  // Add to solution

                if (solution.size() == boardSize)       // Solution found
                {
                    isFound = true;
                    break;
                }
                else
                {
                    row++;                              // Move to next row
                    col = 0;                            // Reset column to 0
                    stack.Push(state(i, matrix[row]));  // Push state to stack
                    isFound = true;
                    break;
                }
            }
        }

        // If no valid position was found, backtrack
        if (!isFound)
        {
            row--;                            // Move back to previous row
            solution.pop_back();              // Remove last queen position
            col = stack.Pop().columnNum;      // Retrieve column from stack
            if(stack.IsEmpty())               // If stack is empty, break loop
            {
                break;
            }
            else
            {
                RemoveQueen(matrix, row, col, boardSize); // Remove queen
                col++;
            }
        }
    }

    // Clean up the dynamically allocated matrix
    for (int i = 0; i < boardSize; ++i)
    {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;

    // Save the solutions to a file
    string filename = to_string(boardSize) + "queens_solutions.txt";
    ofstream output(filename);

    output << "Total solutions for N=" << boardSize << ": " << solutions.size() << endl << endl;

    // Write each solution to the file
    for (int i = 1; i <= solutions.size(); i++)
    {
        output << "Solution " << i << ": " << "[";
        for (int j = 0; j < boardSize; j ++)
        {
            if (j != boardSize-1)
            {
                output << solutions[i-1][j] << ", ";
            }
            else
            {
                output << solutions[i-1][j] << "]" << endl;
            }
        }
    }
    output.close();
    cout << "Solutions have been saved to '" << filename << "'" << endl;

    return 0;
}

// Function to print the board matrix
void PrintMatrix(int** matrix, const int & boardSize)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Initialize matrix to 0 (no queens placed)
void InitializeMatrix(int** matrix, const int & boardSize)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

// Place a queen on the board and mark attacked positions
void PlaceQueen(int** matrix, const int & row, const int & column, const int & boardSize)
{
    for (int i = 0; i < boardSize; i++)
    {
        matrix[row][i]++;
        matrix[i][column]++;
    }

    // Mark diagonals as attacked
    int tempRow = row;
    int tempCol = column;

    while (tempCol > 0 && tempRow > 0)
    {
        tempRow--;
        tempCol--;
        matrix[tempRow][tempCol]++;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol < boardSize - 1 && tempRow > 0)
    {
        tempCol++;
        tempRow--;
        matrix[tempRow][tempCol]++;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol > 0 && tempRow < boardSize - 1)
    {
        tempCol--;
        tempRow++;
        matrix[tempRow][tempCol]++;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol < boardSize - 1 && tempRow < boardSize - 1)
    {
        tempCol++;
        tempRow++;
        matrix[tempRow][tempCol]++;
    }
}

// Remove a queen from the board and unmark attacked positions
void RemoveQueen(int** matrix, int row, int column, const int & boardSize)
{
    for (int i = 0; i < boardSize; i++)
    {
        matrix[row][i]--;
        matrix[i][column]--;
    }

    // Unmark diagonals
    int tempRow = row;
    int tempCol = column;

    while (tempCol > 0 && tempRow > 0)
    {
        tempRow--;
        tempCol--;
        matrix[tempRow][tempCol]--;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol < boardSize - 1 && tempRow > 0)
    {
        tempCol++;
        tempRow--;
        matrix[tempRow][tempCol]--;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol > 0 && tempRow < boardSize - 1)
    {
        tempCol--;
        tempRow++;
        matrix[tempRow][tempCol]--;
    }

    tempCol = column;
    tempRow = row;

    while (tempCol < boardSize - 1 && tempRow < boardSize - 1)
    {
        tempCol++;
        tempRow++;
        matrix[tempRow][tempCol]--;
    }
}
