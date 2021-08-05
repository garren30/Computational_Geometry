## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

# -- Base configuration
cmake_minimum_required(VERSION 3.0)
project(MyConvexHullAlgorithms VERSION 1.0.0.1)

# -- Packages
find_package(CGAL REQUIRED)

# -- Executables
add_executable(myConvexHullExperiments experiment.cxx)

## eof - $RCSfile$
