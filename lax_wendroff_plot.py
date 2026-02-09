import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# --- 1. Scientific Plot Styling ---
plt.rcParams.update({
    "text.usetex": False,       
    "font.family": "serif",
    "mathtext.fontset": "cm",   # Standard LaTeX font
    "axes.labelsize": 12,
    "font.size": 12,
    "legend.fontsize": 10,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
    "figure.figsize": [8, 12]
})

def plot_lax_wendroff():
    # 2. Load Data
    try:
        df = pd.read_csv('burgers_lax_wendroff.csv')
    except FileNotFoundError:
        print("Error: 'burgers_lax_wendroff.csv' not found. Run the C++ code first!")
        return

    # 3. Setup Layout
    plot_times = sorted(df['t'].unique())
    fig, axes = plt.subplots(len(plot_times), 1, sharex=True)
    # Using raw strings r"" for LaTeX math to avoid escape sequence warnings
    fig.suptitle(r"$\mathrm{Eulerian\ Evolution:\ Lax-Wendroff\ Method}$", fontsize=16)

    for i, t in enumerate(plot_times):
        ax = axes[i]
        subset = df[df['t'] == t]
        
        # FIXED: Using a raw f-string rf"" and double-bracing the LaTeX \mathrm
        # This prevents the NameError for 's' and the SyntaxWarning
        label_text = rf"$t = {t:.1f}\ \mathrm{{s}}$"
        ax.plot(subset['x'], subset['u'], color='#1f77b4', lw=1.8, label=label_text)
        
        # Aesthetics
        ax.set_ylabel(r"$u(x,t)$")
        ax.set_ylim(0.4, 1.8)
        ax.set_xlim(0, 10)
        ax.grid(True, linestyle=':', alpha=0.5)
        ax.legend(loc='upper right')

        # Annotations
        if t == 2.0:
            ax.axvline(np.pi + 2, color='red', linestyle='--', alpha=0.4)
            ax.text(np.pi + 2.2, 0.6, r"$\mathrm{Theoretical\ Shock\ Location}$", color='red', fontsize=9)
        if t > 3.0:
            # Dynamic placement for the text label
            idx = np.argmax(np.abs(np.diff(subset['u'])))
            shock_x = subset['x'].iloc[idx]
            ax.text(shock_x - 3.5, 1.6, r"$\mathrm{Gibbs\ Oscillations}$", color='black', fontsize=9, fontweight='bold')

    axes[-1].set_xlabel(r"$\mathrm{Position}\ (x)$")
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    # 4. Save
    plt.savefig('lax_wendroff_final.png', dpi=300)
    print("Success! Final plot saved as 'lax_wendroff_final.png'")

if __name__ == "__main__":
    plot_lax_wendroff()