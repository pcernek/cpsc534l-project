import sys
import argparse

from lxml import etree

import dblp_utils as du
import dblp_types as dt


MIN_PUBS_PER_AUTHOR = 3


def parse_dblp(dblp_fname):
  parser = etree.XMLParser(dtd_validation=True)
  tree = etree.parse(dblp_fname, parser)
  dblp = tree.getroot()

  authors = {}
  skill_ids = {} # A mapping of skill name to id number
  skill_hist = [] # skill_hist[i] gives the number of occurrences of skill i
  pub_id = 0

  for child in dblp.getchildren():
    # Filter to the most important venues
    if not du.in_venues(child):
      continue

    # Expect only a single title element per entry
    title = child.find("title")

    # Parse & process the skills for the entry
    cur_skills = set()
    for word in title.text.split():
      word = du.sanitize(word)
      if word and word not in du.filler_words:
        cur_skills.add(word)
        if word not in skill_ids:
          skill_ids[word] = len(skill_ids)
          skill_hist.append(0)
        skill_hist[skill_ids[word]] += 1

    # Parse & process the authors for the entry
    for elem in child.findall("author"):
      key = elem.text
      if not key in authors:
        author = dt.author(elem.text)
        authors[key] = author
      authors[key].skills.update(cur_skills)
      authors[key].pubs.add(pub_id)

    pub_id += 1

  return authors, skill_ids, skill_hist


def populate_collabs(auth_list):
  for a1 in auth_list:
    s = []
    for a2 in auth_list:
      if a1 == a2:
        num_collabs = 0
      else:
        num_collabs = len(a1.pubs.intersection(a2.pubs))
      a1.set_num_collabs(a2, num_collabs)
      a2.set_num_collabs(a1, num_collabs)
      s.append(num_collabs)

  return auth_list

def generate_problem_instance(dblp_fname, out_fname, candidate_ids, k):

  authors, skill_ids, skill_hist = parse_dblp(dblp_fname)

  print("Initially found {0} skills".format(len(skill_hist)))
  print("Skill dist: ", {w: skill_hist[i] for i, w in enumerate(skill_ids.keys())})
  print("Initially found {0} authors, now filtering".format(len(authors)))

  auth_list = [a for k, a in authors.items() if len(a.pubs) >= MIN_PUBS_PER_AUTHOR]
  auth_list.sort(key=lambda a: a.id_num)
  print("Num authors after filtering: ", len(auth_list))

  with du.tf_file_writer(out_fname) as tfw:
    tfw.write_comment("Number of nodes")
    tfw.write(len(auth_list))
    tfw.write_comment("Number of skills")
    tfw.write(len(skill_ids))

    for author in auth_list:
      print(author, author.pubs, author.skills)

    populate_collabs(auth_list)

    tfw.write_comment("Matrix of pairwise edge costs")
    for a1 in auth_list:
      s = []
      for a2 in auth_list:
        intersection = len(a1.pubs.intersection(a2.pubs))
        union = len(a1.pubs.union(a2.pubs))
        comm_cost = 1 - float(intersection) / union
        s.append(comm_cost)
      tfw.write(' '.join([str(f) for f in s]))

    tfw.write_comment("Skill allocation per node")
    for a in auth_list:
      tfw.write(len(a.skills))
      tfw.write(' '.join([str(f) for f in sorted([skill_ids[s] for s in a.skills])]))

    tfw.write_comment("Skill probabilities")
    pf = sum(skill_hist)
    tfw.write(' '.join([str(s / pf) for s in skill_hist]))

    tfw.write_comment("Number of candidates")
    tfw.write(str(len(candidate_ids)))
    tfw.write_comment("Indices of the candidates")
    tfw.write(' '.join([str(i) for i in candidate_ids]))
    tfw.write_comment("Budget")
    tfw.write(str(k))


def main():
  parser = argparse.ArgumentParser(description='Parse an xml file containing a dblp element to create an output file constituting an instance of the hiring problem')
  parser.add_argument('--input', required=True, help='xml file containing a dblp element')
  parser.add_argument('--output', required=True, help='file to which to write the instance of hiring problem')
  parser.add_argument('--candidate-ids', required=True, type=int, nargs='+', help='the ids of candidates to consider')
  parser.add_argument('--budget', type=float, default=1)

  args = parser.parse_args()
  generate_problem_instance(args.input, args.output, args.candidate_ids, args.k)

if __name__ == "__main__":
  main()
