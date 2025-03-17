import matplotlib
matplotlib.use('Agg')

import os
import re
import matplotlib.pyplot as plt

def extract_num_cycles(file_path):
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
    num_cycles = []
    
    for folder in os.listdir(base_path):
        match = re.match(r"m5out_m64_t(\d+)", folder)
        if match:
            print(match)
            num_threads = int(match.group(1))
            stats_file = os.path.join(base_path, folder, "stats.txt")
            
            if os.path.isfile(stats_file):
                cycles = extract_num_cycles(stats_file)
                print(cycles)
                if cycles is not None:
                    thread_counts.append(num_threads)
                    num_cycles.append(cycles)
    
    # Sort data by thread count
    sorted_data = sorted(zip(thread_counts, num_cycles))
    return zip(*sorted_data) if sorted_data else ([], [])

def plot_data(thread_counts, num_cycles, base_path):
    plt.figure(figsize=(8, 5))
    
    plt.plot(thread_counts, num_cycles, marker='o', linestyle='-')
    
    plt.xlabel("Number of Threads")
    plt.ylabel("Maximal IPC")
    plt.title("Maximal IPC vs Number of Threads")
    plt.grid()
    
    save_path = os.path.join(base_path, f"q7_{thread_counts}.png")
    plt.savefig(save_path)
    plt.close()

def main():
    base_path = "./Cortex_A7"
    thread_counts, num_cycles = collect_data(base_path)
    
    if thread_counts and num_cycles:
        plot_data(thread_counts, num_cycles, base_path)
    else:
        print("No valid data found.")

if __name__ == "__main__":
    main()
