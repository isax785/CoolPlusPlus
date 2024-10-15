# DOC - Least Squares Regression 

- [DOC - Least Squares Regression](#doc---least-squares-regression)
- [Quadratic Curve Fitting](#quadratic-curve-fitting)
- [R square](#r-square)
- [Cubic Curve Fitting](#cubic-curve-fitting)
- [Linear Algebra Basis](#linear-algebra-basis)
  - [Determinant](#determinant)
    - [2x2 Matrix](#2x2-matrix)
    - [3x3 Matrix](#3x3-matrix)
  - [Cramer's Rule](#cramers-rule)
  - [4x4 Matrix](#4x4-matrix)
- [Quadratic Polynomial - `C#` Code](#quadratic-polynomial---c-code)
  - [Using the class](#using-the-class)
  - [Implementation](#implementation)
- [References:](#references)

[Source](https://www.codeproject.com/Articles/63170/Least-Squares-Regression-for-Quadratic-Curve-Fitti)

---

- [ ] `#u` set the *termine noto* to 0
- [ ] `#a` [Cubic Curve Fitting](#cubic-curve-fitting)

Quadratic and cubic polynomials are derived for a given set of points.

The implemented method is based on **Least Squares Regression**, and applies the **Cramer's Rule** to solve the linear system  of equations.


# Quadratic Curve Fitting

Scope: Derive the equation of a quadratic curve from a series of data points, i.e. determine a, b, and c, where `y = ax2 + bx + c`. Also the R-squared (the coefficient of determination) value is needed. 

Equation: `y = ax^2 + bx + c`
Given the series of points  `(x1,y1), (x2,y2) ... (xn,yn)`.

`for i = 1 to n` We want the values of a, b, and c that minimise the sum of squares of the deviations of yi from `a*xi^2 + bxi + c`. Such values will give the best-fitting quadratic equation.

Let the sum of the squares of the deviations be:

```
               n
   F(a,b,c) = SUM (a*xi^2 + bxi + c - yi)^2
              i=1

dF/da = SUM 2*(a*xi^2+b*xi+c-yi)*xi^2 = 0
dF/db = SUM 2*(a*xi^2+b*xi+c-yi)*xi = 0
dF/dc = SUM 2*(a*xi^2+b*xi+c-yi) = 0
```

All sums range over i = 1, 2, ..., n.

Dividing by 2 and rearranging gives these three simultaneous linear equations containing the three unknowns a, b, and c:

```
(SUM xi^4)*a + (SUM xi^3)*b + (SUM xi^2)*c = SUM xi^2*yi,
(SUM xi^3)*a + (SUM xi^2)*b +   (SUM xi)*c = SUM xi*yi,
(SUM xi^2)*a +   (SUM xi)*b +    (SUM 1)*c = SUM yi.
```

Using notation `Sjk` to mean the sum of `x_i^j*y_i^k`:

```
a*S40 + b*S30 + c*S20 = S21
a*S30 + b*S20 + c*S10 = S11
a*S20 + b*S10 + c*S00 = S01
```
Solve the simultaneous equations using Cramer's law:

```
  [ S40  S30  S20 ] [ a ]   [ S21 ]
  [ S30  S20  S10 ] [ b ] = [ S11 ]
  [ S20  S10  S00 ] [ c ]   [ S01 ] 

  D = [ S40  S30  S20 ] 
      [ S30  S20  S10 ] 
      [ S20  S10  S00 ]  
  
    = S40(S20*S00 - S10*S10) - S30(S30*S00 - S10*S20) + S20(S30*S10 - S20*S20)

 Da = [ S21  S30  S20 ]
      [ S11  S20  S10 ] 
      [ S01  S10  S00 ]  

    = S21(S20*S00 - S10*S10) - S11(S30*S00 - S10*S20) + S01(S30*S10 - S20*S20)

 Db = [ S40  S21  S20 ] 
      [ S30  S11  S10 ] 
      [ S20  S01  S00 ]  

    = S40(S11*S00 - S01*S10) - S30(S21*S00 - S01*S20) + S20(S21*S10 - S11*S20)
  
 Dc = [ S40  S30  S21 ] 
      [ S30  S20  S11 ] 
      [ S20  S10  S01 ] 
  
    = S40(S20*S01 - S10*S11) - S30(S30*S01 - S10*S21) + S20(S30*S11 - S20*S21)  

a = Da/D
b = Db/D
c = Dc/D
```

# R square

R2 = 1 - (residual sum of squares / total sum of squares).

```
                        n
total sum of squares = SUM (yi - y_mean)^2.
                       i=1
```

This is the sum of the squares of the differences between the measured y values and the mean y value.

```
                           n
residual sum of squares = SUM (yi - yi_predicted)^2.
                          i=1
```

This is the sum of the squares of the difference between the measured y values and the values of y predicted by the equation.


# Cubic Curve Fitting

Scope: Derive the equation of a cubic curve from a series of data points, i.e. determine a, b, and c, where `y = ax3 + bx2 + cx + d`. Also the R-squared (the coefficient of determination) value is needed.

Equation: `y = ax3 + bx2 + cx + d`
Given the series of points  `(x1,y1), (x2,y2) ... (xn,yn)`.

Let the sum of the squares of the deviations be:

```
               n
   F(a,b,c) = SUM (a*xi^3 + b*xi^2 + c*x + d - yi)^2
              i=1

dF/da = SUM 2*(a*xi^3 + b*xi^2 + c*x + d - yi)*xi^3 = 0
dF/db = SUM 2*(a*xi^3 + b*xi^2 + c*x + d - yi)*xi^2 = 0
dF/dc = SUM 2*(a*xi^3 + b*xi^2 + c*x + d - yi)*xi = 0
dF/dd = SUM 2*(a*xi^3 + b*xi^2 + c*x + d - yi) = 0
```

All sums range over i = 1, 2, ..., n.

```
(SUM xi^6)*a + (SUM xi^5)*b + (SUM xi^4)*c + (SUM xi^3)*d = SUM xi^3*yi
(SUM xi^5)*a + (SUM xi^4)*b + (SUM xi^3)*c + (SUM xi^2)*d = SUM xi^2*yi
(SUM xi^4)*a + (SUM xi^3)*b + (SUM xi^2)*c +   (SUM xi)*d = SUM xi*yi  
(SUM xi^3)*a + (SUM xi^2)*b +   (SUM xi)*c +    (SUM 1)*d = SUM yi     
```
Using notation `Sjk` to mean the sum of `x_i^j*y_i^k`:

```
a*S60 + b*S50 + c*S40 + d*S30 = S31
a*S50 + b*S40 + c*S30 + d*S20 = S21
a*S40 + b*S30 + c*S20 + d*S10 = S11
a*S30 + b*S20 + c*S10 + d*S00 = S01
```

Solve the simultaneous equations using Cramer's law:

```
| S60  S50  S40 | | a | = | S31 |
| S50  S40  S30 | | b | = | S21 |
| S40  S30  S20 | | c | = | S11 |
| S30  S20  S10 | | d | = | S01 |

D = | S60  S50  S40  S30 |
    | S50  S40  S30  S20 |
    | S40  S30  S20  S10 |
    | S30  S20  S10  S00 |

    = ???

Da = 
```


# Linear Algebra Basis

Linear algebra notes applied for this implementation.

## Determinant

NOTE: this method only works for 2x2 and 3x3 matrices. For larger matrices it is best to use a graphing utility or computer software.

### 2x2 Matrix

```
A = | a1 b1 |
    | a2 b2 |

det(A) = a1b2 - a2b1
```

### 3x3 Matrix

```
A = | a1 b1 c1 |
    | a2 b2 c2 |
    | a3 b3 c3 |    

det(A) = a1b2c3 + a3b1c2 + c1a2b3 - a3b2c1 - b3c2a1 - c3a2b1
```

![](img_md/2024-10-10-15-13-17.png)

## Cramer's Rule

Cramer’s Rule is a method that uses determinants to solve systems of equations that have the same number of equations as variables.

Consider a system of two linear equations in two variables.

```text
a1*x + b1*y = c1
a2*x + b2*y = c2
```

The solution using Cramer’s Rule is given as

```text

D = | a1 b1 |
    | a2 b2 |

            | c1 b1 |
     Dx     | c2 b2 |
x = ---- = ----------- != 0
     D      | a1 b1 |
            | a2 b2 |

            | a1 c1 |
     Dy     | a2 c2 |
y = ---- = ----------- != 0
     D      | a1 b1 |
            | a2 b2 |

```

If we are solving for `x`, the `x` column is replaced with the constant column. If we are solving for `y`, the `y` column is replaced with the constant column.

## 4x4 Matrix

$$\begin{bmatrix} a_{11} & a_{12} & a_{13} & a_{14} \\ a_{21} & a_{22} & a_{23} & a_{24} \\ a_{31} & a_{32} & a_{33} & a_{34} \\ a_{41} & a_{42} & a_{43} & a_{44} \end{bmatrix}$$

Where `Aij` denotes the submatrix by deleting ith row and jth column.

Determinant:

$$det(a) = a_{11}\cdot det(A_{11}) - a_{12}\cdot det(A_{12}) + a_{13}\cdot det(A_{13}) - a_{14}\cdot det(A_{14})$$


To find the determinant of a 4×4 matrix, you can use various methods such as expansion by minors, row reduction, or applying specific properties.

Cramer's rule is a method of solving a system of linear equations. It is based on the observation that each equation in the system can be written as a linear combination of the variables. The coefficients of the linear combination are then used to determine the value of each variable.

1. Write the 4x4 system of equations.

2. Calculate the determinant of the matrix (denoted by |A|).

3. Calculate the determinant of each matrix obtained by replacing one column of the original matrix with the constants from the system of equations (denoted by |A_x|).

4. Divide each of the determinants |A_x| by the determinant |A| to obtain the values of the variables.

5. Substitute these values into the system of equations to check the solution.

Cramer's rule can be used to solve linear equations with any number of variables and equations. The method can also be used to solve systems of equations with non-linear equations. The method is not limited to two equations, as long as the system of equations can be written in a linear form.

# Quadratic Polynomial - `C#` Code

## Using the class

Declare an instance:

```C#
LstSquQuadRegr solvr = new LstSquQuadRegr();
```

Pass it some point pairs (at least 3):

```C#
solvr.AddPoints(x1, y1);
solvr.AddPoints(x2, y2);
solvr.AddPoints(x3, y3);
solvr.AddPoints(x4, y4);
```

Get the values:

```C#
double the_a_term = solvr.aTerm();  
double the_b_term = solvr.bTerm();
double the_c_term = solvr.cTerm();
double the_rSquare = solvr.rSquare();
```
## Implementation

A bunch of helper methods calculate all the various sums of squares. When calculating the values of a, b, and c, I used the sjk notation above as I found it easier to keep track.

```C#
/******************************************************************************
                          Class LstSquQuadRegr
     A C#  Class for Least Squares Regression for Quadratic Curve Fitting
                          Alex Etchells  2010    
******************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;


public  class LstSquQuadRegr
{
     /* instance variables */
    ArrayList pointArray = new ArrayList(); 
    private int numOfEntries; 
    private double[] pointpair;          

    /*constructor */
    public LstSquQuadRegr()
    {
        numOfEntries = 0;
        pointpair = new double[2];
    }

    /*instance methods */    
    /// <summary>
    /// add point pairs
    /// </summary>
    /// <param name="x">x value</param>
    /// <param name="y">y value</param>
    public void AddPoints(double x, double y) 
    {
        pointpair = new double[2]; 
        numOfEntries +=1; 
        pointpair[0] = x; 
        pointpair[1] = y;
        pointArray.Add(pointpair);
    }

    /// <summary>
    /// returns the a term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>a term</returns>
    public double aTerm()
    {
        if (numOfEntries < 3)
        {
            throw new InvalidOperationException(
               "Insufficient pairs of co-ordinates");
        }
        //notation sjk to mean the sum of x_i^j*y_i^k. 
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //a = Da/D
        return (s21*(s20 * s00 - s10 * s10) - 
                s11*(s30 * s00 - s10 * s20) + 
                s01*(s30 * s10 - s20 * s20))
                /
                (s40*(s20 * s00 - s10 * s10) -
                 s30*(s30 * s00 - s10 * s20) + 
                 s20*(s30 * s10 - s20 * s20));
    }

    /// <summary>
    /// returns the b term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>b term</returns>
    public double bTerm()
    {
        if (numOfEntries < 3)
        {
            throw new InvalidOperationException(
               "Insufficient pairs of co-ordinates");
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //b = Db/D
        return (s40*(s11 * s00 - s01 * s10) - 
                s30*(s21 * s00 - s01 * s20) + 
                s20*(s21 * s10 - s11 * s20))
                /
                (s40 * (s20 * s00 - s10 * s10) - 
                 s30 * (s30 * s00 - s10 * s20) + 
                 s20 * (s30 * s10 - s20 * s20));
    }

    /// <summary>
    /// returns the c term of the equation ax^2 + bx + c
    /// </summary>
    /// <returns>c term</returns>
    public double cTerm()
    {
        if (numOfEntries < 3)
        {
            throw new InvalidOperationException(
                       "Insufficient pairs of co-ordinates");
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

        //c = Dc/D
        return (s40*(s20 * s01 - s10 * s11) - 
                s30*(s30 * s01 - s10 * s21) + 
                s20*(s30 * s11 - s20 * s21))
                /
                (s40 * (s20 * s00 - s10 * s10) - 
                 s30 * (s30 * s00 - s10 * s20) + 
                 s20 * (s30 * s10 - s20 * s20));
    }
    
    public double rSquare() // get r-squared
    {
        if (numOfEntries < 3)
        {
            throw new InvalidOperationException(
               "Insufficient pairs of co-ordinates");
        }
        // 1 - (residual sum of squares / total sum of squares)
        return 1 - getSSerr() / getSStot();
    }
   
    /*helper methods*/
    private double getSx() // get sum of x
    {
        double Sx = 0;
        foreach (double[] ppair in pointArray)
        {
            Sx += ppair[0];
        }
        return Sx;
    }

    private double getSy() // get sum of y
    {
        double Sy = 0;
        foreach (double[] ppair in pointArray)
        {
            Sy += ppair[1];
        }
        return Sy;
    }

    private double getSx2() // get sum of x^2
    {
        double Sx2 = 0;
        foreach (double[] ppair in pointArray)
        {
            Sx2 += Math.Pow(ppair[0], 2); // sum of x^2
        }
        return Sx2;
    }

    private double getSx3() // get sum of x^3
    {
        double Sx3 = 0;
        foreach (double[] ppair in pointArray)
        {
            Sx3 += Math.Pow(ppair[0], 3); // sum of x^3
        }
        return Sx3;
    }

    private double getSx4() // get sum of x^4
    {
        double Sx4 = 0;
        foreach (double[] ppair in pointArray)
        {
            Sx4 += Math.Pow(ppair[0], 4); // sum of x^4
        }
        return Sx4;
    }

    private double getSxy() // get sum of x*y
    {
        double Sxy = 0;
        foreach (double[] ppair in pointArray)
        {
            Sxy += ppair[0] * ppair[1]; // sum of x*y
        }
        return Sxy;
    }

    private double getSx2y() // get sum of x^2*y
    {
        double Sx2y = 0;
        foreach (double[] ppair in pointArray)
        {
            Sx2y += Math.Pow(ppair[0], 2) * ppair[1]; // sum of x^2*y
        }
        return Sx2y;
    }

    private double getYMean() // mean value of y
    {
        double y_tot = 0;
        foreach (double[] ppair in pointArray)
        {
            y_tot += ppair[1]; 
        }
        return y_tot/numOfEntries;
    }

    private double getSStot() // total sum of squares
    {
        //the sum of the squares of the differences between 
        //the measured y values and the mean y value
        double ss_tot = 0;
        foreach (double[] ppair in pointArray)
        {
            ss_tot += Math.Pow(ppair[1] - getYMean(), 2);
        }
        return ss_tot;
    }

    private double getSSerr() // residual sum of squares
    {
        //the sum of the squares of te difference between 
        //the measured y values and the values of y predicted by the equation
        double ss_err = 0;
        foreach (double[] ppair in pointArray)
        {
            ss_err += Math.Pow(ppair[1] - getPredictedY(ppair[0]), 2);
        }
        return ss_err;
    }

    private double getPredictedY(double x)
    {
        //returns value of y predicted by the equation for a given value of x
        return aTerm() * Math.Pow(x, 2) + bTerm() * x + cTerm();
    }
}
```


# References: 

- Least Squares Regression:
  - http://mathforum.org/library/drmath/view/72047.html
  - http://mathforum.org/library/drmath/view/53796.html
- 4x4 matrix:
  - https://www.geeksforgeeks.org/determinant-of-4x4-matrix/
- R square:
  - http://en.wikipedia.org/wiki/R_square
- Cramer's rule:
  -  http://www.purplemath.com/modules/cramers.htm
-  nxn matrix
   -  https://math.libretexts.org/Courses/Cosumnes_River_College/Math_420%3A_Differential_Equations_(Breitenbach)/11%3A_Appendices/04%3A_Determinants_and_Cramer's_Rule_for_n_x_n_Matrices
