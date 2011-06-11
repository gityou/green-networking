
### Files Overview ###

*qcr.cpp*, *rcr.cpp*, and *optimal.cpp* implement three linear-programming routing simulations. 

*lp.cpp* is a clean interface wrapping the lpsolve linear-program solver.

### Linear Programming ###
Linear programming is a way to solve linear optimization problems. Given a set of linear equations (constraints), the solution set can have

*   no solution (overdetermined)
*   one unique solution
*   infinitely many solutions (underdetermined)

In underdetermined systems it may be useful to find a "best" solution within this solution space. This would be the "optimal" solution, hence linear optimization.

### Example ###

    Maximize x in
    x <= 100
    x + y = 250

The optimal solution to this problem would be

    x = 100
    y = 150


