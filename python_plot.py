import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_lagrange_evolution():
    # 1. Load the data
    try:
        df = pd.read_csv('burgers_lagrange.csv')
    except FileNotFoundError:
        print("Error: burgers_lagrange.csv not found. Run the C++ code first!")
        return

    # Get the unique timestamps saved in the file
    available_times = sorted(df['t'].unique())
    print(f"Plotting snapshots for times: {available_times}")

    # 2. Setup Plot
    fig, axes = plt.subplots(len(available_times), 1, figsize=(10, 15), sharex=True)
    fig.suptitle("Lagrangian Evolution: Wave Overturning (Inviscid)", fontsize=16, fontweight='bold')

    for i, t in enumerate(available_times):
        ax = axes[i]
        subset = df[df['t'] == t]
        
        # Plot particles as small dots to show density
        ax.scatter(subset['x'], subset['u'], s=1, color='red', alpha=0.6, label='Particles')
        # Draw a thin line connecting them in their original order
        ax.plot(subset['x'], subset['u'], color='red', lw=0.5, alpha=0.3)

        # Formatting
        ax.set_title(f"Time t = {t:.1f} s", fontsize=12, loc='right')
        ax.set_ylabel("u(x,t)")
        ax.set_ylim(0.4, 1.6)
        ax.set_xlim(0, 15) # Extended X to see propagation
        ax.grid(True, linestyle=':', alpha=0.5)

        # Annotations
        if t == 0.0:
            ax.annotate("Initial Sine Wave", xy=(np.pi, 1.5), xytext=(1, 1.4),
                        arrowprops=dict(arrowstyle="->"))
        elif t == 2.0:
            ax.axvline(np.pi + 2, color='black', linestyle='--', alpha=0.5)
            ax.text(np.pi + 2.2, 0.5, "Shock Formation (t=2)", fontweight='bold')
        elif t > 2.0:
            ax.text(8, 1.4, "Overturning Region (Multi-valued)", color='darkred', fontsize=10)

    axes[-1].set_xlabel("Position (x)")
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    plt.savefig('lagrange_detailed_evolution.png', dpi=300)
    print("Success! Plot saved as 'lagrange_detailed_evolution.png'")

if __name__ == "__main__":
    plot_lagrange_evolution()