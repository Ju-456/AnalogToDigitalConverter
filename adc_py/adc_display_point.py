import matplotlib.pyplot as plt
import numpy as np
import os
import tkinter as tk
from tkinter import messagebox
from read_file import read_file

class ADC:
    def __init__(self, x, y):
        self.display_signal(x, y)

    def display_signal(self, x, y):
        x = np.array(x)
        y = np.array(y)

        # Plotting
        plt.figure(figsize=(8, 3), dpi=100)
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
        # plt.show()

def adc_display_point(filepath):
    x, y = read_file(filepath) 
    # 1/2 values will be displayed to alleging the display
    x = x[::2]
    y = y[::2]

    # Conservation of the first 150 points only
    x = x[:500]
    y = y[:500]

    return x, y

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()

    base_txt_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "adc_txt"))
    wave_file = os.path.join(base_txt_path,"wave_sampled.txt") 

    if os.path.exists(wave_file):
        x, y = adc_display_point(wave_file)
        if x and y:
            ADC(x, y)
        else:
            messagebox.showerror("Error", "Unable to read values from the file.")
    else:
        messagebox.showerror("Error", f"File not found: {wave_file}")
