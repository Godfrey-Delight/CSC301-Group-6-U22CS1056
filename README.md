# CSC301-Group-6-U22CS1056
Godfrey Nzubechukwu Delight
Simplex Tableau Solver


This project implements the Simplex Algorithm for solving linear programming problems using the Simplex Tableau Method. The program allows users to input the number of decision variables, constraints, and the respective coefficients to compute the optimal solution for a maximization problem.

Features
- Accepts user input for decision variables, constraints, and coefficients.
- Constructs the Simplex tableau dynamically.
- Iteratively performs pivoting to find the optimal solution.
- Detects and handles unbounded problems.
- Displays intermediate tableau steps for better understanding.

How It Works
1. The user inputs the number of variables and constraints.
2. The program constructs the initial Simplex tableau.
3. The algorithm iterates through pivoting steps until an optimal solution is found.
4. The final solution and the maximum objective function value are displayed.


Input Example

Enter the number of decision variables: 2
Enter the number of constraints: 2
Enter the coefficients of the constraints (row by row):
a11: 1
a12: 1
b1: 4
a21: 2
a22: 1
b2: 5
Enter the coefficients of the objective function:
c1: 3
c2: 2


Output Example

Optimal Solution Found!
x1 = 2.00
x2 = 2.00
Maximum Value (Z) = 10.00


## Code Structure
- 'Simplex' Class:
  - Constructor: Initializes the tableau with constraints and slack variables.
  - printTableau(): Displays the tableau at each iteration.
  - getPivotColumn(): Finds the entering variable.
  - getPivotRow(): Finds the leaving variable.
  - pivot(): Performs row operations for updating the tableau.
  - solve(): Executes the Simplex algorithm.

- 'main()' Function:
  - Takes user input and initializes the 'Simplex' class.
  - Calls 'solve()' to find the optimal solution.



