from dfa import DFA, OneCharacterDFA
from constants import SYMBOLS, TRANSITION_TABLES as tt, VALID_STATES as vs

def generate_dfas():
    dfas = []

    dfas.append(DFA("Entero", tt["INTEGERS"], vs["INTEGERS"]))
    dfas.append(DFA("Variable", tt["VARIABLES"], vs["VARIABLES"])) 
    dfas.append(DFA("Real", tt["REAL_NUMBERS"], vs["REAL_NUMBERS"]))

    for character, name in SYMBOLS.items():
        dfas.append(OneCharacterDFA(name, character))

    return dfas

def print_token_type(token, dfas):
    for dfa in dfas:
        if dfa.test(token) == True:
            print(token, "-->", dfa.token_type)

def space_symbols(string):
    spaced_string = string

    replace_queue = []

    i = j = 0
    while i < len(spaced_string):
        character = spaced_string[i]

        if character in SYMBOLS and character not in ["-", "+"]:
                spaced_string = spaced_string[:i] + "#" + spaced_string[i+1:]
                replace_queue.append(f" {character} ")

        i += 1

    flexible_length = len(spaced_string)
    while j < flexible_length:
        if spaced_string[j] == "#":
            spaced_string = spaced_string.replace(spaced_string[j], replace_queue.pop(0), 1)
            flexible_length += 2

        j += 1

    return spaced_string
