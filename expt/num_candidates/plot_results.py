import sys
import json

import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) < 2:
  print("Usage: plot_results.py results_file_path [plot_save_path]")
  exit()

results_file_path = sys.argv[1]

save_plot = len(sys.argv) >= 3
if save_plot:
  plot_save_path = sys.argv[2]

with open(results_file_path, 'r') as fd:
  data = json.loads(fd.read())

for algo, algo_data in data["series"].items():
  x_vals = []
  y_vals = []
  for num_candidates_str, run_info in algo_data.items():
    x = int(num_candidates_str)
    y = np.mean([trial["results"]["elapsed_time"] for trial in run_info["trials"]])
    x_vals.append(x)
    y_vals.append(y)

  plt.plot(x_vals, y_vals, 'o-', label=algo)

plt.legend()
plt.title("Elapsed time vs. number of candidates")
plt.xlabel("Number of candidates")
plt.ylabel("Elapsed time (s)")

if save_plot:
  plt.savefig(plot_save_path)
  
plt.show()
