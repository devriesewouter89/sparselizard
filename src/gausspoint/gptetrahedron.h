// sparselizard - Copyright (C) 2017- A. Halbach and C. Geuzaine, University of Liege
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <alexandre.halbach at gmail.com>.


#ifndef GPTETRAHEDRON_H
#define GPTETRAHEDRON_H

#include <iostream>
#include <math.h>
#include <vector>
#include "gausspoints.h"

namespace gptetrahedron
{   
    void set(int integrationorder, std::vector<double>& coordinates, std::vector<double>& weights);
};

#endif
