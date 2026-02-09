#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

int main() {
    // --- Parameters ---
    const int n_particles = 2000;
    const double L = 10.0;
    const double dx_xi = L / (n_particles - 1);
    const double dt = 0.001;
    const double t_max = 5.01; // Slightly over 5 to ensure we catch the final frame

    // Initial positions (xi) and constant velocities (u0)
    std::vector<double> xi(n_particles);
    std::vector<double> u0(n_particles);
    
    for (int i = 0; i < n_particles; ++i) {
        xi[i] = i * dx_xi;
        u0[i] = 1.0 + 0.5 * std::sin(xi[i]);
    }

    std::ofstream outFile("burgers_lagrange.csv");
    outFile << "t,x,u\n";

    double t_star = -1.0;
    bool shock_detected = false;

    // --- Simulation Loop ---
    int step = 0;
    for (double t = 0.0; t <= t_max; t += dt) {
        
        // Save only at specific whole-number intervals: 0, 1, 2, 3, 4, 5
        bool save_frame = false;
        if (std::abs(t - 0.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 1.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 2.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 3.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 4.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 5.0) < dt/2.0) save_frame = true;

        if (save_frame) {
            std::cout << "Saving snapshot at t = " << std::fixed << std::setprecision(1) << t << std::endl;
            for (int i = 0; i < n_particles; ++i) {
                // Lagrangian Position: x(t) = xi + u0 * t
                double current_x = xi[i] + u0[i] * t;
                outFile << t << "," << current_x << "," << u0[i] << "\n";
            }
        }

        // Detection: When do particles first cross?
        if (!shock_detected) {
            for (int i = 0; i < n_particles - 1; ++i) {
                double x_i = xi[i] + u0[i] * t;
                double x_next = xi[i+1] + u0[i+1] * t;
                if (x_next <= x_i) {
                    t_star = t;
                    shock_detected = true;
                    break;
                }
            }
        }
        step++;
    }

    outFile.close();

    std::cout << "\n----------- LAGRANGIAN ANALYSIS -----------" << std::endl;
    std::cout << "Detected Shock Formation (t*): " << t_star << " s" << std::endl;
    std::cout << "Analytical Prediction:         2.0000 s" << std::endl;
    std::cout << "-------------------------------------------\n" << std::endl;

    return 0;
}