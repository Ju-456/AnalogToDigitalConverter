import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
import os
import tkinter as tk
from tkinter import messagebox

class ADC:
    def __init__(self, x, y):
        self.display_sampled_signal(x, y)

    def display_sampled_signal(self, x, y):
        x = np.array(x)
        y = np.array(y)

        fig, ax = plt.subplots(figsize=(10, 6))
        plt.title("Sampled and Quantized Signal Display", fontsize=16, fontweight='bold')

        # Calculate spacing and width between samples
        if len(x) > 1:
            spacing = min([x2 - x1 for x1, x2 in zip(x[:-1], x[1:])])
        else:
            spacing = 1.0
        width = spacing * 0.4  # Width of each rectangle

        # Draw rectangle for each (x, y)
        for xi, yi in zip(x, y):
            rect = Rectangle((xi - width / 2, 0), width, yi, color='purple', edgecolor='black')
            ax.add_patch(rect)

        ax.set_xlim(min(x) - spacing, max(x) + spacing)
        ax.set_ylim(min(0, min(y)), max(y) * 1.1)
        plt.xlabel("t (time)")
        plt.ylabel("v (amplitude)")
        plt.grid(True, linestyle='--', alpha=0.6)
        plt.tight_layout()

def adc_display_rectangle(filepath):
    x = []
    y = []
    try:
        with open(filepath, 'r') as f:
            for line in f:
                values = line.strip().split()
                if len(values) != 2:
                    continue
                try:
                    xi, yi = map(float, values)
                    x.append(xi)
                    y.append(yi)
                except ValueError:
                    continue
    except FileNotFoundError:
        print(f"Problem opening file: {filepath}")
    return x, y

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()

    user_home = os.path.expanduser("~")
    wave_file = os.path.join(user_home, "AnalogToDigitalConverter","adc_txt","wave_quantized.txt") 

    if os.path.exists(wave_file):
        x, y = adc_display_rectangle(wave_file)
        if x and y:
            ADC(x, y)
        else:
            messagebox.showerror("Error", "Failed to read valid x and y values.")
    else:
        messagebox.showerror("Error", f"File not found: {wave_file}")
