import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
import os
import tkinter as tk
from tkinter import messagebox

from utils import read_file
from utils import adc_display

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np

class adc_rectangle:
    def __init__(self, x, y):
        self.fig, self.ax = plt.subplots(figsize=(8, 3), dpi=100)
        self.display_quantized_signal(x, y)

    def display_quantized_signal(self, x, y):
        x = np.array(x)
        y = np.array(y)
        self.ax.set_title("Sampled and Quantized Signal Display", fontsize=16, fontweight='bold')

        widths = np.diff(x)
        last_width = widths[-1] if len(widths) > 0 else 1.0
        widths = np.append(widths, last_width)

        for xi, yi, w in zip(x, y, widths):
            rect = Rectangle((xi, 0), w, yi, facecolor='purple', edgecolor='black', alpha=0.6)
            self.ax.add_patch(rect)

        self.ax.set_xlim(min(x), max(x) + last_width)
        self.ax.set_ylim(min(0, min(y)) - 0.1 * abs(min(y)), max(y) + 0.1 * abs(max(y)))
        self.ax.set_xlabel("t (time)")
        self.ax.set_ylabel("v (amplitude)")
        self.ax.grid(True, linestyle='--', alpha=0.6)
        plt.tight_layout()
        # plt.show()

def adc_display_rectangle(filepath):
    from call_all_functions import read_file
    x, y = read_file(filepath)

    return x, y

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()

    base_txt_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "adc_txt"))
    wave_file = os.path.join(base_txt_path,"wave_quantized.txt") 
    
    if os.path.exists(wave_file):
        x, y = adc_display_rectangle(wave_file)
        if x and y:
            adc_rectangle(x, y)
        else:
            messagebox.showerror("Error", "Failed to read valid x and y values.")
    else:
        messagebox.showerror("Error", f"File not found: {wave_file}")
