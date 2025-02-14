#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Simplex {
private:
    int numVars, numConstraints;
    vector<vector<double>> tableau;
    vector<int> basicVars;

public:
    // Constructor to initialize the Simplex tableau
    Simplex(int variables, int constraints, vector<vector<double>> &A, vector<double> &b, vector<double> &c) {
        numVars = variables;
        numConstraints = constraints;

        // Initialize the tableau with constraints and slack variables
        tableau.resize(numConstraints + 1, vector<double>(numVars + numConstraints + 1, 0));

        // Fill constraints in tableau
        for (int i = 0; i < numConstraints; i++) {
            for (int j = 0; j < numVars; j++) {
                tableau[i][j] = A[i][j]; // Coefficients of constraints
            }
            tableau[i][numVars + i] = 1;  // Slack variable
            tableau[i].back() = b[i];     // RHS values
            basicVars.push_back(numVars + i); // Track basic variables
        }

        // Fill objective function row
        for (int j = 0; j < numVars; j++) {
            tableau[numConstraints][j] = -c[j];
        }
    }

    // Function to print the Simplex tableau with a descriptive iteration label
    void printTableau(int iteration) {
        if (iteration == 0) {
            cout << "\nInitial Iteration:\n";
        } else if (iteration == 1) {
            cout << "\nFirst Iteration:\n";
        } else if (iteration == 2) {
            cout << "\nSecond Iteration:\n";
        } else if (iteration == 3) {
            cout << "\nThird Iteration:\n";
        } else {
            cout << "\nIteration " << iteration + 1 << ":\n";
        }
        
        for (const auto &row : tableau) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(2) << value << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Function to find the pivot column (entering variable)
    int getPivotColumn() {
        int pivotCol = 0;
        for (int j = 1; j < numVars + numConstraints; j++) {
            if (tableau[numConstraints][j] < tableau[numConstraints][pivotCol]) {
                pivotCol = j;
            }
        }
        return tableau[numConstraints][pivotCol] >= 0 ? -1 : pivotCol;
    }

    // Function to find the pivot row (leaving variable)
    int getPivotRow(int pivotCol) {
        int pivotRow = -1;
        double minRatio = 1e9;

        for (int i = 0; i < numConstraints; i++) {
            if (tableau[i][pivotCol] > 0) {
                double ratio = tableau[i].back() / tableau[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }
        return pivotRow;
    }

    // Function to perform row operations for pivoting
    void pivot(int pivotRow, int pivotCol) {
        double pivotElement = tableau[pivotRow][pivotCol];

        // Normalize the pivot row
        for (double &val : tableau[pivotRow]) {
            val /= pivotElement;
        }

        // Make other rows zero in the pivot column
        for (int i = 0; i <= numConstraints; i++) {
            if (i != pivotRow) {
                double factor = tableau[i][pivotCol];
                for (int j = 0; j <= numVars + numConstraints; j++) {
                    tableau[i][j] -= factor * tableau[pivotRow][j];
                }
            }
        }

        // Update basic variables
        basicVars[pivotRow] = pivotCol;
    }

    // Function to execute the Simplex algorithm
    void solve() {
        cout << "\nSolving using Simplex Algorithm...\n";

        int iteration = 0;
        printTableau(iteration); 

        while (true) {
            int pivotCol = getPivotColumn();
            if (pivotCol == -1) break; 

            int pivotRow = getPivotRow(pivotCol);
            if (pivotRow == -1) {
                cout << "The problem is *Unbounded*.\n";
                return;
            }

            pivot(pivotRow, pivotCol);

            iteration++;  
            printTableau(iteration);  
        }

        // Display the optimal solution
        cout << "Optimal Solution Found!\n";
        vector<double> solution(numVars, 0);
        for (int i = 0; i < numConstraints; i++) {
            if (basicVars[i] < numVars) {
                solution[basicVars[i]] = tableau[i].back();
            }
        }

        for (int i = 0; i < numVars; i++) {
            cout << "x" << i + 1 << " = " << fixed << setprecision(2) << solution[i] << endl;
        }
        cout << "Maximum Value (Z) = " << fixed << setprecision(2) << -tableau[numConstraints].back() << endl;
    }
};

int main() {
    int variables, constraints;

    // Get user input for number of variables and constraints
    cout << "Enter the number of decision variables: ";
    cin >> variables;
    cout << "Enter the number of constraints: ";
    cin >> constraints;

    vector<vector<double>> A(constraints, vector<double>(variables));
    vector<double> b(constraints);
    vector<double> c(variables);

    // Get user input for the coefficients of the constraints
    cout << "Enter the coefficients of the constraints (row by row):\n";
    for (int i = 0; i < constraints; i++) {
        for (int j = 0; j < variables; j++) {
            cout << "a" << i + 1 << j + 1 << ": ";
            cin >> A[i][j];
        }
    }

    // Get user input for the right-hand side values of the constraints
    cout << "Enter the right-hand side values of the constraints:\n";
    for (int i = 0; i < constraints; i++) {
        cout << "b" << i + 1 << ": ";
        cin >> b[i];
    }

    // Get user input for the coefficients of the objective function
    cout << "Enter the coefficients of the objective function:\n";
    for (int i = 0; i < variables; i++) {
        cout << "c" << i + 1 << ": ";
        cin >> c[i];
    }

    // Create an object of the Simplex class and solve the problem
    Simplex simplex(variables, constraints, A, b, c);
    simplex.solve();

    return 0;
}
