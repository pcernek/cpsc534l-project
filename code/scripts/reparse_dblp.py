
def get_next_line(fd):
  line = '#'
  while line.startswith('#'):
    line = fd.readline()
  return line.strip()

def write_line(line, fd):
  fd.write(str(line) + '\n')

fname = "/home/paul/ubc/courses/ms_term1/cpsc534l/project/data/dblp/dblp.tf"
outname = "/home/paul/ubc/courses/ms_term1/cpsc534l/project/data/dblp/dblp_smaller.tf"
NEW_NUM_AUTH = 50

author_costs = []
author_skills = []
skill_dist = []

with open(fname) as fd:
  num_nodes = int(get_next_line(fd))
  num_skills = int(get_next_line(fd))

  # Read edge weights
  for i in range(num_nodes):
    edge_weights = [float(n) for n in get_next_line(fd).split(' ')]
    author_costs.append(edge_weights)
    
  # Read author skills
  for i in range(num_nodes):
    num_auth_skills = int(get_next_line(fd))
    auth_skills = set([int(n) for n in get_next_line(fd).split(' ')])
    author_skills.append(auth_skills)

  # Read skill dist
  skill_dist = [float(n) for n in get_next_line(fd).split(' ')]
  
  # Read candidates
  num_candidates = int(get_next_line(fd))
  candidates = [int(n) for n in get_next_line(fd).split(' ')]

  budget = int(get_next_line(fd))

authors_sorted = sorted(range(len(author_costs)), key=lambda i: sum(author_costs[i]))
new_authors = authors_sorted[:NEW_NUM_AUTH]
new_skills = set()
for a in new_authors:
  new_skills.update(author_skills[a])
new_skill_ids = {}
# Mapping of <old skill id> to <new skill id>
for i, s in enumerate(new_skills):
  new_skill_ids[s] = i
print("Num skills after filtering: ", len(new_skills))

with open(outname, 'w') as fd:
  write_line('# Number of nodes', fd)
  write_line(NEW_NUM_AUTH, fd)
  write_line('# Number of skills', fd)
  write_line(len(new_skills), fd)

  write_line('# Matrix of pairwise edge costs', fd)
  for a1 in new_authors:
    s = []
    for a2 in new_authors:
      s.append(author_costs[a1][a2])
    write_line(' '.join([str(f) for f in s]), fd)

  write_line('# Skill allocation per node', fd)
  for a in new_authors:
    write_line(len(author_skills[a]), fd)
    new_auth_skills = sorted([new_skill_ids[s] for s in author_skills[a]])
    write_line(' '.join([str(f) for f in new_auth_skills]), fd)

  write_line('# Skill probabilities', fd)
  write_line(' '.join([str(skill_dist[s]) for s in sorted(new_skills)]), fd)

  write_line('# Number of candidates', fd)
  write_line(num_candidates, fd)
  write_line('# Indices of teh candidates', fd)
  write_line(' '.join([str(i) for i in candidates]), fd)
  write_line('# Budget', fd)
  write_line(str(budget), fd)
