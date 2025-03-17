import matplotlib
matplotlib.use('Agg')

import os
import re
from mpl_toolkits.mplot3d import Axes3D
from tabulate import tabulate
import matplotlib.pyplot as plt

def extract_num_cycles(file_path):
    sum = 0
    with open(file_path, 'r') as file:
        for line in file:
            if re.match(r"system\.cpu\d*\.numCycles", line):
                parts = line.split()
                print(f"Found {parts[0]}: ", parts[1], " in ", file_path)
                return int(parts[1])
                # sum += int(parts[1])  # Extract the value
    return sum

def collect_data(base_path):
    thread_counts = []
    width_counts = []
    num_cycles = []
    
    for folder in os.listdir(base_path):
        match = re.match(r"m5out_m64_t(\d+)_w(\d+)", folder)
        if match:
            print(match)
            num_threads = int(match.group(1))
            width = int(match.group(2))
            stats_file = os.path.join(base_path, folder, "stats.txt")
            
            if os.path.isfile(stats_file):
                cycles = extract_num_cycles(stats_file)
                print(cycles)
                if cycles is not None:
                    thread_counts.append(num_threads)
                    width_counts.append(width)
                    num_cycles.append(cycles)
    
    # Sort data by thread count
    sorted_data = sorted(zip(thread_counts, width_counts, num_cycles))
    return zip(*sorted_data) if sorted_data else ([], [])

def plot_data(thread_counts, width_counts, num_cycles, base_path):
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    speedup = [num_cycles[0] / cycles for cycles in num_cycles]
    ax.scatter(thread_counts, width_counts, speedup, c='r', marker='o')

    ax.set_xlabel("Number of Threads")
    ax.set_ylabel("Width")
    ax.set_zlabel("Estimated Speedup")
    ax.set_title("3D Plot of Speedup vs Threads and Width")

    save_path = os.path.join(base_path, "q10_3d_plot.png")
    plt.savefig(save_path)
    plt.close()
    
    # Prepare data for tabular representation
    headers = ["Number of Threads", "Width", "Estimated Speedup"]
    table_data = list(zip(thread_counts, width_counts, speedup))
    
    # Generate LaTeX table
    latex_table = tabulate(table_data, headers=headers, tablefmt="latex")
    
    # Save LaTeX table to a file
    latex_file_path = os.path.join(base_path, "q10_table.tex")
    with open(latex_file_path, "w") as latex_file:
        latex_file.write(latex_table)
    
    print(f"LaTeX table saved to {latex_file_path}")

def main():
    base_path = "./Cortex_A15"
    thread_counts, width_counts, num_cycles = collect_data(base_path)
    print(thread_counts, width_counts, num_cycles)
    
    if thread_counts and width_counts and num_cycles:
        plot_data(thread_counts, width_counts, num_cycles, base_path)
    else:
        print("No valid data found.")

if __name__ == "__main__":
    main()
