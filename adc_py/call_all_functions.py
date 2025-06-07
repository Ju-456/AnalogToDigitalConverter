import time
import os
import sys

import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt

from utils import read_file
from utils import adc_display

from adc_display_curve import adc_curve
from adc_display_point import adc_point
from adc_display_rectangle import adc_rectangle

# Automatically close plot after 4 seconds and fix window position
def auto_close_plot():
    manager = plt.get_current_fig_manager()
    try:
        manager.window.wm_geometry("+300+300") 
    except AttributeError:
        pass  
    plt.show(block=False)
    plt.pause(4)
    plt.close()

def run_all_versions():

    # Display 1: Raw sampled signal
    base_txt_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "adc_txt"))
    file_curve = os.path.join(base_txt_path, "wave.txt")
    if os.path.exists(file_curve):
        x, y = adc_display(file_curve)
        if x and y:
            print("Display: Raw sampled signal (with filtering)...")
            adc_curve(x, y)
            auto_close_plot()
        else:
            print(f"Invalid data in {file_curve}")
    else:
        print(f"File not found: {file_curve}")

    # Display 2: Sampled signal (points)
    file_point = os.path.join(base_txt_path, "wave_sampled.txt")
    if os.path.exists(file_point):
        x, y = adc_display(file_point)
        if x and y:
            print("Display: Sampled signal (with filtering)...")
            adc_point(x, y)
            auto_close_plot()
        else:
            print(f"Invalid data in {file_point}")
    else:
        print(f"File not found: {file_point}")

    # Display 3: Sampled + Quantized signal (rectangles)
    file_rectangle = os.path.join(base_txt_path, "wave_quantized.txt")
    if os.path.exists(file_rectangle):
        x, y = adc_display(file_rectangle)
        if x and y:
            print("Display: Sampled and quantized signal (with filtering)...")
            adc_rectangle(x, y)
            auto_close_plot()
        else:
            print(f"Invalid data in {file_rectangle}")
    else:
        print(f"File not found: {file_rectangle}")

if __name__ == "__main__":
    run_all_versions()
