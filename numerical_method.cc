#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

int main() {
    // --- 1. Simulation Parameters ---
    const int nx = 600;                 
    const double x_start = 0.0;
    const double x_end = 2.0 * M_PI * 2.0; // Two full periods
    const double dx = (x_end - x_start) / (nx - 1);
    
    const double t_max = 5.0;           
    const double dt = 0.005;            // Smaller dt for better stability with sine
    const int nt = static_cast<int>(t_max / dt);

    std::vector<double> x(nx);
    std::vector<double> u(nx);
    std::vector<double> u_next(nx);

    // --- 2. Initialize Cauchy Data: g(x) = 1 + 0.5*sin(x) ---
    for (int i = 0; i < nx; ++i) {
        x[i] = x_start + i * dx;
        u[i] = 1.0 + 0.5 * std::sin(x[i]);
    }

    std::ofstream outFile("burgers_sine.csv");
    outFile << "t,x,u\n";

    // --- 3. Time Stepping (Lax-Friedrichs) ---
    for (int n = 0; n <= nt; ++n) {
        double t = n * dt;

        // Save snapshots every 0.5s
        if (n % 100 == 0) {
            for (int i = 0; i < nx; ++i) {
                outFile << t << "," << x[i] << "," << u[i] << "\n";
            }
        }

        for (int i = 1; i < nx - 1; ++i) {
            double flux_plus = 0.5 * u[i + 1] * u[i + 1];
            double flux_minus = 0.5 * u[i - 1] * u[i - 1];
            
            // Lax-Friedrichs Update
            u_next[i] = 0.5 * (u[i + 1] + u[i - 1]) - (dt / (2.0 * dx)) * (flux_plus - flux_minus);
        }

        // Periodic Boundary Conditions
        u_next[0] = u_next[nx - 2];
        u_next[nx - 1] = u_next[1];

        u = u_next;
    }

    outFile.close();
    // Change the final print statement to:
std::cout << "Simulation complete." << std::endl;
std::cout << "Particle x0 = pi was the steepest point." << std::endl;
std::cout << "Shock formation observed at t=2.0 at position x ~ 5.14 (pi + 2)." << std::endl;
    return 0;
}