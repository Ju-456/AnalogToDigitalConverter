import matplotlib.pyplot as plt
import numpy as np
import os
import tkinter as tk
from tkinter import messagebox

class ADC:
    def __init__(self, x, y):
        self.display_signal(x, y)

    def display_signal(self, x, y):
        x = np.array(x)
        y = np.array(y)

        # Plotting
        plt.figure(figsize=(10, 6))
        plt.axhline(0, color='black', linewidth=2)
        plt.axvline(0, color='black', linewidth=2)
        plt.xticks([])  # Optional: hide x-axis ticks for clarity

        for xi, yi in zip(x, y):
            plt.plot([xi, xi], [0, yi], color='purple')     # Vertical line
            plt.plot(xi, yi, 'o', color='purple')            # Top dot

        plt.xlabel("t (time)")
        plt.ylabel("A (amplitude)")
        plt.title("Sampled Signal Display", fontweight='bold')
        plt.grid(True, linestyle=':')
        plt.tight_layout()

def adc_display_point(filepath):
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
        print(f"Problem when opening file: {filepath}")
    return x, y

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()

    user_home = os.path.expanduser("~")
    wave_file = os.path.join(user_home, "AnalogToDigitalConverter","adc_txt","wave_sampled.txt") 

    if os.path.exists(wave_file):
        x, y = adc_display_point(wave_file)
        if x and y:
            ADC(x, y)
        else:
            messagebox.showerror("Error", "Unable to read values from the file.")
    else:
        messagebox.showerror("Error", f"File not found: {wave_file}")
