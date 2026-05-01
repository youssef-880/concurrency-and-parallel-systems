import time
import os
from multiprocessing import Pool

# --- 1. The Computation Task ---
# We are counting prime numbers in a range. 
# This is "CPU-bound," meaning it requires heavy math.
def count_primes(limit):
    count = 0
    for num in range(2, limit):
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                break
        else:
            count += 1
    return count

def run_benchmark():
    # Setup parameters
    total_range = 500000  # Total numbers to check
    cores = os.cpu_count()
    # We split the work into equal chunks based on the number of cores
    work_chunks = [total_range // cores] * cores

    print(f"--- Performance Benchmark ---")
    print(f"System Cores: {cores}")
    print(f"Task: Counting primes up to {total_range // cores} (repeated {cores} times)")
    print("-" * 30)

    # --- 2. Sequential Execution ---
    print("Running Sequentially...")
    start_seq = time.time()
    results_seq = []
    for chunk in work_chunks:
        results_seq.append(count_primes(chunk))
    end_seq = time.time()
    seq_time = end_seq - start_seq
    print(f"Sequential Time: {seq_time:.4f} seconds")

    # --- 3. Parallel Execution ---
    print("Running Parallely...")
    start_par = time.time()
    # Using Pool(os.cpu_count()) as suggested in your hint
    with Pool(processes=cores) as p:
        results_par = p.map(count_primes, work_chunks)
    end_par = time.time()
    par_time = end_par - start_par
    print(f"Parallel Time:   {par_time:.4f} seconds")

    # --- 4. Calculations ---
    speedup = seq_time / par_time
    efficiency = speedup / cores

    print("-" * 30)
    print(f"RESULTS")
    print(f"Speedup: {speedup:.2f}x faster")
    print(f"Efficiency: {efficiency:.2f} ({efficiency*100:.1f}%)")
    print("-" * 30)

if __name__ == "__main__":
    run_benchmark()