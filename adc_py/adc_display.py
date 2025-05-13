import matplotlib.pyplot as plt
import tkinter as tk
from tkinter import messagebox
import numpy as np
import os

class ADC:
    def __init__(self, x, y):
        plt.title("ADC Graph", fontsize=16, fontweight='bold')  
        plt.plot(x, y,"r-") 
        #plt.plot(x, y, marker='o')
        plt.xlabel("t")
        plt.ylabel("amplitude")
        plt.grid(True)
        plt.show()

def read_wave_file(filepath):
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
        print(f"Problem when opening file : {filepath}")
    return x, y

if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()  

    user_home = os.path.expanduser("~")
    wave_file = os.path.join(user_home, "AnalogToDigitalConverter", "adc_txt","adc.txt") 

    if os.path.exists(wave_file):
        x, y = read_wave_file(wave_file)
        if x and y:
            ADC(x, y)
        else:
            messagebox.showerror("Error", "Can't read values proprely")
    else:
        messagebox.showerror("Error", f"Can't find : {wave_file}")
