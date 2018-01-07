filler_words = set(["and", "the", "of", "about", "amongst", "for", "it", "but", "a", "an", "by", "from", "in", "as", "with", "is", "are", "+", "=", "to", "von", "der", "1", "2014", "versus", "their", "-", "best", "between", "without", "with", "across", "on", "above", "below", "within", "within", "towards"])

def sanitize(word):
  word = word.strip('.').strip(':').strip('?').strip('-').strip(',')
  word = word.lower()
  word = word.strip('"')

  return word

db_venues = set(["journal/sigmod", "conf/vldb", "conf/icde", "conf/icdt", "conf/edbt", "conf/pods"])
dm_venues = set(["conf/kdd", "conf/www", "conf/sdm", "conf/pkdd", "conf/icdm"])
ai_venues = set(["conf/icml", "conf/ecml", "conf/colt", "conf/uai"])
theory_venues = set(["conf/soda", "conf/focs", "conf/stoc", "conf/stacs"])

venues = db_venues.union(dm_venues).union(ai_venues).union(theory_venues)

def in_venues(elt):
  k = elt.get("key")
  for v in venues:
    if k.startswith(v):
      return True
  return False

class tf_file_writer:

  def __init__(self, out_file_name):
    self.fname = out_file_name

  def write_comment(self, comment):
    self.open_file.write('# ' + str(comment) + '\n')

  def write(self, s):
    self.open_file.write(str(s) + '\n')

  def __enter__(self):
    self.open_file =  open(self.fname, 'w')
    return self

  def __exit__(self, exc_type, exc_value, traceback):
    self.open_file.close()
    if exc_type is not None:
      print(exc_type, exc_value, traceback)
