import dfa.constants as c

def is_possible_float(string, i):
    if i not in range(len(string) + 1):
        return False
    
    return string[i] in ["E", "e"] and string[i-1].isnumeric() and (string[i+1] in ["-", "+"] or string[i+1].isnumeric())

def get_first_key(dictionary):
    keys = list(dictionary.keys())

    if len(keys) == 0:
        return ""
    
    return keys[0]

def normalize(token):
    normalized_token = ""

    for i in range(len(token)):
        if token[i] in c.NATURAL_NUMBERS:
            normalized_token += "N"
        elif token[i] in c.LETTERS and not is_possible_float(token, i):
            normalized_token += "A"
        else:
            normalized_token += token[i]

    return normalized_token

