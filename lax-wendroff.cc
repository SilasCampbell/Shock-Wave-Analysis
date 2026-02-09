#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

int main() {
    // --- Parameters ---
    const int nx = 5000; 
    const double x_start = 0.0, x_end = 10.0;
    const double dx = (x_end - x_start) / (nx - 1);
    const double dt = 0.0001; 
    const double t_max = 5.01;
    const int nt = static_cast<int>(t_max / dt);

    std::vector<double> u(nx), u_next(nx), x(nx);
    
    // Initialize: u(x,0) = 1 + 0.5*sin(x)
    for (int i = 0; i < nx; ++i) {
        x[i] = x_start + i * dx;
        u[i] = 1.0 + 0.5 * std::sin(x[i]);
    }

    std::ofstream outFile("burgers_lax_wendroff.csv");
    outFile << "t,x,u\n";

    double global_max_slope = 0.5; 
    double t_star = 0.0;

    // --- Main Time Loop ---
    for (int n = 0; n <= nt; ++n) {
        double t = n * dt;

        // Save snapshots at specific whole seconds for the paper
        bool save_frame = false;
        if (std::abs(t - 0.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 1.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 2.0) < dt/2.0) save_frame = true;
        if (std::abs(t - 4.0) < dt/2.0) save_frame = true;

        if (save_frame) {
            for (int i = 0; i < nx; ++i) outFile << t << "," << x[i] << "," << u[i] << "\n";
        }

        // --- SHOCK DETECTION ---
        double current_max_slope = 0.0;
        // Search interior (indices ~10 to nx-10) to avoid boundary noise
        for (int i = 10; i < nx - 10; ++i) {
            double slope = std::abs((u[i+1] - u[i-1]) / (2.0 * dx));
            if (slope > current_max_slope) current_max_slope = slope;
        }
        if (current_max_slope > global_max_slope) {
            global_max_slope = current_max_slope;
            t_star = t;
        }

        // --- LAX-WENDROFF STEP ---
        for (int i = 1; i < nx - 1; ++i) {
            double c = u[i] * dt / dx; // Local Courant number
            u_next[i] = u[i] 
                        - 0.5 * c * (u[i+1] - u[i-1]) 
                        + 0.5 * std::pow(c, 2) * (u[i+1] - 2.0*u[i] + u[i-1]);
        }
        
        // Periodic Boundary Conditions
        u_next[0] = u_next[nx-2];
        u_next[nx-1] = u_next[1];
        u = u_next;
    }

    outFile.close();
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n----------- LAX-WENDROFF ANALYSIS -----------" << std::endl;
    std::cout << "Detected Shock Time (t*): " << t_star << " s" << std::endl;
    std::cout << "Analytical Prediction:    2.0000 s" << std::endl;
    std::cout << "---------------------------------------------\n" << std::endl;

    return 0;
}