import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# 1. Load data
try:
    df = pd.read_csv('burgers_sine.csv')
except FileNotFoundError:
    print("Error: 'burgers_sine.csv' not found. Run the C++ code first!")
    exit()

# 2. Setup Subplots
plot_times = [0.0, 2.0, 5.0]
fig, axes = plt.subplots(len(plot_times), 1, figsize=(8, 12), sharex=True)
x_shock_formation = np.pi + 2 

for i, t in enumerate(plot_times):
    actual_t = df['t'].unique()[np.abs(df['t'].unique() - t).argmin()]
    subset = df[df['t'] == actual_t]
    
    ax = axes[i]
    ax.plot(subset['x'], subset['u'], color='blue', lw=2)
    ax.set_title(f"Time t = {actual_t:.1f}")
    ax.grid(True, linestyle=':', alpha=0.6)
    ax.set_ylabel("u(x,t)")
    ax.set_xlim(0, 10)
    ax.set_ylim(-0.2, 2.2)

    # Label key features
    if i == 0:
        ax.annotate("Initial Sine Wave", xy=(np.pi, 1.5), xytext=(4, 1.8),
                    arrowprops=dict(arrowstyle="->"))
    if i == 1:
        ax.axvline(x_shock_formation, color='red', linestyle='--', alpha=0.5)
        ax.text(x_shock_formation+0.2, 0.2, "Shock Forms", color='red')
    if i == 2:
        # Expected position at t=5 is x = 5.14 + (1.0 * 3) = 8.14
        ax.axvline(8.14, color='green', linestyle='--', alpha=0.5)
        ax.text(8.14-2.5, 0.2, "Shock Propagated", color='green')

axes[-1].set_xlabel("Position (x)")
plt.tight_layout()

# 3. Save
plt.savefig('burgers_subplots.png')
print(f"--- Success! ---")
print(f"Subplots saved to: {os.getcwd()}/burgers_subplots.png")