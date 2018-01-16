import numpy as np
import json
import subprocess
import os.path as path

PROJECT_DIR = '/media/paul/Data/Education/ubc/courses/ms_term1/cpsc534l/project'

EXECUTABLE = path.join(PROJECT_DIR, 'code/build/run_headhunter')
INPUT_FILE = path.join(PROJECT_DIR, 'data/dblp/dblp_smaller.tf')

OUTPUT_FILE = path.join(PROJECT_DIR, 'expt/budget/brute.txt')

NUM_GROUND_SET_SAMPLES = 5
GROUND_SET_SIZE = 10

# Candidate numbers to try
NUM_CANDIDATES = 16

BUDGETS = [1, 3, 7, 12, 15]

# Number of times to run an experiment 
NUM_TRIALS = 5
# NUM_TRIALS = 3

# Total number of nodes in the instance file
NUM_NODES = 50

# ALGOS = ["greedy_rs", "mc_rs", "mc_mc", "greedy_mc"]
ALGOS = ["brute_force"]


RESULT_TAG = '[RESULT]'

def parse_output(output):
  for line in output.split('\n'):
    if line.startswith(RESULT_TAG):
      toks = line.strip(RESULT_TAG).split(':')
      if toks[0].strip().startswith('Elapsed time'):
        elapsed_time = float(toks[1].strip())
      elif toks[0].strip().startswith('Top candidates'):
        hires = [int(c) for c in toks[1].strip().split(' ')]
      elif toks[0].strip().startswith('Value'):
        value = float(toks[1].strip())
  return elapsed_time, hires, value

"""
Solution quality vs size of candidate set
"""

# Maybe we'll want to keep track of something else later?
data = {"series": {a: {} for a in ALGOS}}

for budget in BUDGETS:

  num_candidates = NUM_CANDIDATES

  for algo in ALGOS:
    param_set = {"ground_set_size": GROUND_SET_SIZE, "num_candidates" : num_candidates, "budget": budget, "trials": []}
    data["series"][algo][budget] = param_set

  for _ in range(NUM_GROUND_SET_SAMPLES):
    ground_set = np.random.choice(range(NUM_NODES), size=GROUND_SET_SIZE, replace=False).tolist()
    non_ground_set = list(set(range(NUM_NODES)) - set(ground_set))
    ground_set_str = ' '.join(map(str, ground_set))

    for i in range(NUM_TRIALS):
      candidates = np.random.choice(non_ground_set, size=num_candidates, replace=False).tolist()
      candidate_str = ' '.join(map(str, candidates))

      for algo in ALGOS:
        # This gets a reference directly into our large data structure for keeping track of results
        trials = data["series"][algo][budget]["trials"]
        arg_list = [EXECUTABLE, "--algorithm", algo, "--instance-file", INPUT_FILE, "--budget", str(budget), "--ground-set", *map(str, ground_set), "--candidates", *map(str, candidates)]
        print("Now running: ", arg_list)

        result = subprocess.run(arg_list, stdout=subprocess.PIPE)
        output = result.stdout.decode()
        print(output)
        elapsed_time, hires, value = parse_output(output)
        results = {"elapsed_time": elapsed_time, "hires": ' '.join(map(str, hires)), "value": value}
        trial = {"ground_set": ground_set_str, "candidates": candidate_str, "results": results}
        trials.append(trial)

    with open(OUTPUT_FILE, 'w') as fd:
      fd.write(json.dumps(data, sort_keys=True, indent=2))

