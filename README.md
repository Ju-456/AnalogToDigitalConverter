
# 📡 Analog-to-Digital Conversion Project

This project demonstrates a practical implementation of signal digitization — from analog generation to sampling, quantization, and visualization. The project is written in **C** for signal processing and **Python** for graphical display.

---

## 📁 Project Structure

```
AnalogToDigitalConverter/
├── adc_c/
│   ├── generation.c                # Signal generation and processing
│   ├── generation.h                # Function declarations
│   └── main.c                     # Main execution logic
│
├── adc_py/
│   ├── adc_display_curve.py       # Displays original analog signal
│   ├── adc_display_point.py       # Displays sampled signal
│   ├── adc_display_rectangle.py   # Displays quantized signal
│   └── call_all_functions.py      # Automates all displays
│
├── adc_txt/
│   ├── wave.txt                   # Original analog signal data
│   ├── wave_sampled.txt           # Sampled data
│   └── wave_quantized.txt         # Quantized data
```

---

## ⚙️ How It Works

### 🔧 C Module (`adc_c`)
- **Signal generation** based on user-defined amplitudes and frequencies.
- **Sampling** using Nyquist-Shannon theorem.
- **Quantization** and binary output.
- Outputs stored in `.txt` files in `adc_txt/`.

### 📊 Python Module (`adc_py`)
- Uses `matplotlib` to visualize:
  - Analog signal (`wave.txt`)
  - Sampled signal (`wave_sampled.txt`)
  - Quantized signal (`wave_quantized.txt`)
- `call_all_functions.py` automates the full visualization process.

---

## 🚀 How to Run

### Step 1 – Compile the C Code

```bash
cd adc_c
gcc -o main main.c generation.c -lm
./main
```

Sample input:
```
Please enter the first amplitude (A): 5
Please enter the second amplitude (B): 4
Please enter the 1st frequency (f): 30
Please enter the 2nd frequency (g): 33
```

### Step 2 – Visualize with Python

```bash
cd adc_py
python3 call_all_functions.py
```

📌 Each figure is displayed for 4 seconds. Modify `plt.pause(4)` in `call_all_functions.py` to change the duration.

---

## 🖼️ Visual Outputs

### 📈 Original Signal
![image](https://github.com/user-attachments/assets/acac05e3-226e-40de-8e83-518942dce7e4)

### 🔘 Sampled Signal
![image](https://github.com/user-attachments/assets/aafa45be-bccb-4de3-b5b8-bfa32bee7b8e)

### ▓ Quantized Signal
![image](https://github.com/user-attachments/assets/250e5143-4070-4e7b-bf2e-ae809ca8890e)

---

## 🧠 Implementation Details

### ➤ Core C Functions (in `generation.h`)
- `getWaveInfo()` – Gets signal parameters from user
- `generateWave()` – Combines sine and cosine for signal
- `bestSamplingRate()` – Calculates optimal sampling rate
- `generateSamplingWave()` – Applies sampling
- `generateQuantizedWave()` – Applies quantization
- `generateQuantizedWaveBinary()` – Binary output version

---

## 🧪 Issues and Fixes

### 1. Dense Visualization
- Problem: Displaying all points led to unreadable plots.
- Fix: Limit display to first 500 values for clarity.

### 2. Long Signal Duration
- Problem: `#define DUREE 10` caused heavy files.
- Fix: Optimized to `DUREE = 1.5`.

### 3. Quantized Plot Rendering
- Problem: Overlapping rectangles.
- Fix: Adaptive widths using `np.diff(x)` in Python.

### 4. Misleading Displays
- Problem: C output correct but misleading in plots.
- Fix: Rewrote Python scripts for adaptive, scaled, clean rendering.

---

## 🧾 Example Output

```
Estimated maximum frequency: 29.822 Hz
Nyquist minimum sampling rate: 0.017 Hz
Best sampling rate: 0.016766 Hz
```

---

## ✅ Conclusion

This project offers a practical guide to:
- Analog signal digitization
- Sampling theory
- Quantization techniques
- Adaptive graphical interpretation

It also showcases how proper visual representation bridges the gap between raw numeric output and human interpretation in digital signal processing.

---
