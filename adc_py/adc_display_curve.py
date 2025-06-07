import matplotlib.pyplot as plt
import tkinter as tk
from tkinter import messagebox
import numpy as np
import os

from utils import read_file
from utils import adc_display

class adc_curve:
    def __init__(self, x, y):
        plt.figure(figsize=(8, 3), dpi=100)
        plt.plot(x, y, color='purple') 
        plt.title("Original Signal Display", fontsize=16, fontweight='bold')  
        plt.xlabel("t")
        plt.ylabel("amplitude")
        plt.grid(True)
        # plt.show()

def moving_average(y, window_size=5):
    window = np.ones(window_size) / window_size
    return np.convolve(y, window, mode='valid')

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()  

    base_txt_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "adc_txt"))
    wave_file = os.path.join(base_txt_path,"wave.txt") 

    if os.path.exists(wave_file):
        x, y = adc_display(wave_file)
        if x and y:
            adc_curve(x, y)
        else:
            messagebox.showerror("Error", "Can't read values properly")
    else:
        messagebox.showerror("Error", f"Can't find : {wave_file}")
