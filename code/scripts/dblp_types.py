def name_match(name1, name2):
  if len(name1) == 1 or len(name2) == 1:
      return name1[0] == name2[0]
  return name1 == name2

AUTH_ID = 0
def get_next_author_id():
  global AUTH_ID
  tmp = AUTH_ID
  AUTH_ID += 1
  return tmp

AUTHOR_ARRAY = []
def get_author_by_id(id_num):
  return AUTHOR_ARRAY[id_num]

class author:

  def __init__(self, name):
    tokenized = name.split()
    self.full = name
    self.id_num = get_next_author_id()
    self.skills = set()
    self.pubs = set()
    self.collabs = {}
    
    if len(tokenized) >= 2:
      self.first = name.split()[0]
    else:
      self.first = ""
    
    self.last = name.split()[-1]

    global AUTHOR_ARRAY
    AUTHOR_ARRAY.append(self)

  def set_num_collabs(self, other, num):
    self.collabs[other] = num

  def same_first_name(self, other):
    return name_match(self.first, other.first)

  def same_last_name(self, other):
    return name_match(self.last, other.last)

  def __eq__(self, other):
    return self.same_first_name(other) and self.same_last_name(other)

  def __hash__(self):
    hash_str = self.last
    if len(self.first) >= 1:
      hash_str = self.first[0] + hash_str
    return hash(hash_str)

  def __repr__(self):
    return self.full