import matplotlib
matplotlib.use('Agg')

import os
import re
from mpl_toolkits.mplot3d import Axes3D
from tabulate import tabulate
import matplotlib.pyplot as plt

def extract_max_ipc(file_path):
    max_ipc = 0
    with open(file_path, 'r') as file:
        for line in file:
            if re.match(r"system\.cpu\d*\.ipc", line):
                parts = line.split()
                print(f"Found {parts[0]}: ", parts[1], " in ", file_path)
                # return int(parts[1])
                max_ipc = max(max_ipc, float(parts[1]))  # Extract the value
    return max_ipc

def collect_data(base_path):
    thread_counts = []
    width_counts = []
    num_max_ipc = []
    
    for folder in os.listdir(base_path):
        match = re.match(r"m5out_m64_t(\d+)_w(\d+)", folder)
        if match:
            print(match)
            num_threads = int(match.group(1))
            width = int(match.group(2))
            stats_file = os.path.join(base_path, folder, "stats.txt")
            
            if os.path.isfile(stats_file):
                max_ipc = extract_max_ipc(stats_file)
                print(max_ipc)
                if max_ipc is not None:
                    thread_counts.append(num_threads)
                    width_counts.append(width)
                    num_max_ipc.append(max_ipc)
    
    # Sort data by thread count
    sorted_data = sorted(zip(thread_counts, width_counts, num_max_ipc))
    return zip(*sorted_data) if sorted_data else ([], [])

def plot_data(thread_counts, width_counts, num_max_ipc, base_path):
    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(thread_counts, width_counts, num_max_ipc, c='r', marker='o')

    ax.set_xlabel("Number of Threads")
    ax.set_ylabel("Width")
    ax.set_zlabel("Maximal IPC")
    ax.set_title("3D Plot of Maximal IPC vs Threads and Width")

    save_path = os.path.join(base_path, "q11_3d_plot.png")
    plt.savefig(save_path)
    plt.close()
    
    # Prepare data for tabular representation
    headers = ["Number of Threads", "Width", "Estimated Speedup"]
    table_data = list(zip(thread_counts, width_counts, num_max_ipc))
    
    # Generate LaTeX table
    latex_table = tabulate(table_data, headers=headers, tablefmt="latex")
    
    # Save LaTeX table to a file
    latex_file_path = os.path.join(base_path, "q11_table.tex")
    with open(latex_file_path, "w") as latex_file:
        latex_file.write(latex_table)
    
    print(f"LaTeX table saved to {latex_file_path}")

def main():
    base_path = "./Cortex_A15"
    thread_counts, width_counts, num_max_ipc = collect_data(base_path)
    print(thread_counts, width_counts, num_max_ipc)
    
    if thread_counts and width_counts and num_max_ipc:
        plot_data(thread_counts, width_counts, num_max_ipc, base_path)
    else:
        print("No valid data found.")

if __name__ == "__main__":
    main()
