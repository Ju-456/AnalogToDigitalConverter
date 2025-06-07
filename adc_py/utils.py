# Read x and y data from a text file
def read_file(filepath):
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

def adc_display(filepath):
    x, y = read_file(filepath)
    return x, y