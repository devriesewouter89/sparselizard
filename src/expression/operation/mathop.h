// sparselizard - Copyright (C) 2017- A. Halbach and C. Geuzaine, University of Liege
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <alexandre.halbach at gmail.com>.


#ifndef MATHOP_H
#define MATHOP_H

#include <iostream>
#include <string>
#include "expression.h"
#include "integration.h"
#include "universe.h"
#include "iointerface.h"
#include "vec.h"
#include "mat.h"
#include "formulation.h"

class expression;
class integration;
class mat;
class vec;
class field;
class formulation;

namespace mathop
{
    double getpi(void);
    
    // Perform operations (union, intersection, exclusion) on physical regions:
    int regionunion(const std::vector<int> physregs);
    int regionintersection(const std::vector<int> physregs);
    int regionexclusion(int physreg, int toexclude);
    
    void printvector(std::vector<double> input);
    void printvector(std::vector<int> input);
    
    void writevector(std::string filename, std::vector<double>& towrite);
    
    // Compute the L2 norm of a vector expression:
    expression norm(expression expr);
    
    // Define the (unit norm) vector normal to a surface in 3D (or to a line in 2D). 
    expression normal(int surfphysreg);
    
    // Write scalar or vector values at given coordinates to file:
    void scatterwrite(std::string filename, std::vector<double> xcoords, std::vector<double> ycoords, std::vector<double> zcoords, std::vector<double> compxevals, std::vector<double> compyevals = {}, std::vector<double> compzevals = {});
    
    void setaxisymmetry(void);
    
    void setfundamentalfrequency(double f);
    void settime(double t);
    double gettime(void);
    
    // The time variable:
    expression t(void);
    
    // Get the size of every element in the region, i.e. the 
    // volume, surface and length in respectively a 3D, 2D and 1D problem.
    // The output field is of 'one' type.
    field elementsize(int physreg);
    
    expression dx(expression input);
    expression dy(expression input);
    expression dz(expression input);
    
    expression dt(expression input);
    expression dtdt(expression input);
    
    expression sin(expression input);
    expression cos(expression input);
    expression tan(expression input);
    expression asin(expression input);
    expression acos(expression input);
    expression atan(expression input);
    expression abs(expression input);
    expression sqrt(expression input);
    expression log10(expression input);
    expression pow(expression base, expression exponent);
    
    expression comp(int selectedcomp, expression input);
    expression compx(expression input);
    expression compy(expression input);
    expression compz(expression input);
    
    expression entry(int row, int col, expression input);
    
    expression transpose(expression input);
    expression inverse(expression input);
    expression determinant(expression input);
    
    expression grad(expression input);
    expression div(expression input);
    expression curl(expression input);
    
    // Cross product between vector a and vector b.
    // Any argument that does not have 3 components will be filled with zeros.
    expression crossproduct(expression a, expression b);
    
    // Get the determinant of the physical to reference element variable change Jacobian:
    expression detjac(void);
    
    integration integral(int physreg, expression tointegrate, int integrationorderdelta = 0, int blocknumber = 0);
    integration integral(int physreg, expression meshdeform, expression tointegrate, int integrationorderdelta = 0, int blocknumber = 0);
    // For the multiharmonic resolution an extra integer is required 
    // to know with how many harmonics the coef multiplying the tf 
    // and/or dof should be approximated. Set 'numcoefharms' negative
    // and it will be as if you were calling the above non 
    // multiharmonic functions.
    integration integral(int physreg, int numcoefharms, expression tointegrate, int integrationorderdelta = 0, int blocknumber = 0);
    integration integral(int physreg, int numcoefharms, expression meshdeform, expression tointegrate, int integrationorderdelta = 0, int blocknumber = 0);
    
    expression dof(expression input, int physreg = -1);
    expression tf(expression input, int physreg = -1);
    
    
    
    // Define typically used arrays for convenience:
    expression array1x1(expression term11);
    expression array1x2(expression term11, expression term12);
    expression array1x3(expression term11, expression term12, expression term13);
    expression array2x1(expression term11, expression term21);
    expression array2x2(expression term11, expression term12, expression term21, expression term22);
    expression array2x3(expression term11, expression term12, expression term13, expression term21, expression term22, expression term23);
    expression array3x1(expression term11, expression term21, expression term31);
    expression array3x2(expression term11, expression term12, expression term21, expression term22, expression term31, expression term32);
    expression array3x3(expression term11, expression term12, expression term13, expression term21, expression term22, expression term23, expression term31, expression term32, expression term33);
    
    // Direct resolution (with or without diagonal scaling):
    vec solve(mat A, vec b, bool diagscaling = false);
    
    // Generate, solve and save to field a formulation:
    void solve(formulation formul);
    void solve(std::vector<formulation> formuls);
    
    
    ////////// PREDEFINED OPERATORS
    
    // Gives the engineering strains of a 2D or 3D mechanical displacement vector (Voigt form):
    expression strain(expression input);
    // Gives the Green-Lagrange strains of a 2D or 3D mechanical displacement vector (Voigt form):
    expression greenlagrangestrain(expression gradu);
    // Gives the von Mises stress (Voigt form expected for the argument):
    expression vonmises(expression stress);
    
    ////////// PREDEFINED FORMULATIONS
    
    // Isotropic linear elasticity:
    expression predefinedelasticity(expression dofu, expression tfu, expression Eyoung, expression nupoisson, std::string myoption = "");
    // General anisotropic linear elasticity:
    expression predefinedelasticity(expression dofu, expression tfu, expression hookesmatrix, std::string myoption = "");
    
    // Isotropic elasticity with geometrical nonlinearity and prestress (ignored if zero):
    expression predefinedelasticity(expression dofu, expression tfu, field u, expression Eyoung, expression nupoisson, expression prestress, std::string myoption = "");
    // General anisotropic elasticity with geometrical nonlinearity and prestress (ignored if zero):
    expression predefinedelasticity(expression dofu, expression tfu, field u, expression hookesmatrix, expression prestress, std::string myoption = "");
    
    expression predefinedelectrostaticforce(expression tfu, expression E, expression epsilon);
    expression predefinedelectrostaticforce(std::vector<expression> dxyztfu, expression E, expression epsilon);
    expression predefinedmagnetostaticforce(expression tfu, expression H, expression mu);
    expression predefinedmagnetostaticforce(std::vector<expression> dxyztfu, expression H, expression mu);
};

#endif
