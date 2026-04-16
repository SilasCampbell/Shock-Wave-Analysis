# Shock Wave Analysis: Burgers' Equation
## Overview
This repository contains the code and numerical experiments for analyzing the formation and propagation of shock waves derived from the inviscid Burgers' Equation.

The project bridges theoretical partial differential equations with computational physics, starting with a singularity analysis using the Method of Characteristics to calculate the theoretical shock formation time. It then implements the Lax-Wendroff method to simulate how shocks propagate while respecting the physical requirements of mass and momentum conservation.

## Features
Implicit Classical Solution: Tracks the Lagrangian evolution of the wave using the Method of Characteristics.

Lax-Wendroff Simulation: A second-order accurate finite difference scheme that utilizes numerical dissipation to stabilize the shock front.

Data Visualization: Python scripts included to plot the .csv outputs from the C++ simulations.

## Prerequisites
To compile and run the simulations, you will need:

C++ Compiler: GCC (GNU Compiler Collection) or equivalent.

Environment: Windows Subsystem for Linux (WSL), Linux, or macOS.

Python 3.x: For generating plots from the output data.

Python Libraries: matplotlib and numpy (or pandas, depending on your script setup) for plotting.

## Repository Structure
lagrangian_characteristic_tracker.cc - Generates the implicit model data tracking the path of individual particles. Outputs a .csv over 20,000 time steps.

lagrange_plot.py - Python script to visualize the output from the implicit model.

lax-wendroff.cc - Implements the Lax-Wendroff scheme from an Eulerian perspective. Outputs a .csv over 20,000 time steps.

lax_wendroff_plot.py - Python script to visualize the numerical solution and stabilized shock front.

## Reproducibility Instructions

### Implicit Model (Method of Characteristics)
To replicate the characteristic evolution and observe the wave steepening until the shock formation time:


#### Compile the C++ file:
g++ lagrangian_characteristic_tracker.cc -o lagrange_tracker

#### Run the executable (this will generate a .csv file):
./lagrange_tracker

#### Run the plotting script:
python3 lagrange_plot.py

### Lax-Wendroff Numerical Method
To replicate the numerical solution that demonstrates the stabilized shock front:


#### Compile the C++ file
g++ lax-wendroff.cc -o lax_wendroff

#### Run the executable (this will generate a .csv file)
./lax_wendroff

#### Run the plotting script
python3 lax_wendroff_plot.py

## Simulation Parameters (Hard-coded for stability):

Grid Resolution (dx): 0.002

Time Step (dt): 10^-4

Max Courant Number: ~0.075 (satisfying the CFL condition)

# Author
Silas Campbell

# Acknowledgements
Dr. Todd Young for reviewing the Model PDE and Weak Solutions analysis.

C. Rhys Campbell for assistance with the project's website deployment.
