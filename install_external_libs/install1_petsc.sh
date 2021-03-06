#!/bin/bash

# !!! THE GFORTRAN, GCC, AND G++ COMPILERS MUST BE AVAILABLE !!!
#
# THIS SCRIPT INSTALLS IN ~/SLlibs THE PETSC LIBRARY.



########## ALL LIBRARIES REQUIRED BY SPARSELIZARD ARE PUT IN ~/SLlibs.

rm -rf ~/SLlibs/petsc;
mkdir ~/SLlibs;
cd ~/SLlibs;


########## COMPILING PETSC :

echo '__________________________________________';
echo 'FETCHING THE LATEST PETSC VERSION FROM GIT';
git clone -b maint https://bitbucket.org/petsc/petsc petsc;
echo '__________________________________________';
echo 'CONFIGURING PETSC';
cd petsc;

if [ "$(uname)" == "Linux" ]; then
PETSC_DIR=$(pwd);
PETSC_ARCH=arch-linux2-c-opt;
elif [ "$(uname)" == "Darwin"  ]; then
PETSC_DIR=$(pwd);
PETSC_ARCH=arch-darwin-c-opt;
fi

./configure --with-mpi=0 --with-mumps-serial=1 --download-mumps=1 --download-openblas --with-debugging=0 COPTFLAGS='-O3' CXXOPTFLAGS='-O3' FOPTFLAGS='-O3';
echo '__________________________________________';
echo 'COMPILING PETSC';
make $PETSC_DIR $PETSC_ARCH all;
make $PETSC_DIR $PETSC_ARCH test;    

cd ..;


