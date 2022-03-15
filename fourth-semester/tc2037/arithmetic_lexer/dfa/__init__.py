from dfa.helpers import *

class DFA:
    def __init__(self, token_type, transition_table, final_states):
        self.token_type = token_type
        self.transition_table = transition_table
        self.final_states = final_states

    def test(self, token):
        normalized_token = normalize(token)
        state = get_first_key(self.transition_table)

        for character in normalized_token:
            try:
                state = self.transition_table[state][character]
            except KeyError:
                return False

        return state in self.final_states

class OneCharacterDFA(DFA):
    def __init__(self, token_type, character):
        self.token_type = token_type
        self.character = character

    def test(self, token):
        return token == self.character

