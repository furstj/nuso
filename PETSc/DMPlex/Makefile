CC  = mpicc
CXX = mpic++
CXXFLAGS = -std=c++11 -g

CFLAGS  += `pkg-config --cflags PETSc`
CXXFLAGS  += `pkg-config --cflags PETSc`
LDFLAGS += `pkg-config --libs PETSc`

all: 01_dmplex_basic 02_dmplex_gmsh

clean:
	rm -f 01_dmplex_basic 02_dmplex_gmsh


