class DFA_tok_rec:
    def __init__(self):
        self.states = {'q0', 'q1', 'q2', 'q3', 'q3','q4'}
        self.final_state = 'q4'
        self.transitions = {
            'q0': {'a': 'q1', 'b': 'q2'},
            'q1': {'a': 'q1', 'b': 'q3'},
            'q2': {'a': 'q1', 'b': 'q2'},
            'q3': {'a': 'q1', 'b': 'q4'},
            'q4': {'a': 'q1', 'b': 'q2'}
        }

    def is_valid_token(self, token):
        current_state = 'q0'
        for char in token:
            if char not in self.transitions[current_state]:
                return False
            current_state = self.transitions[current_state][char]
        return current_state == self.final_state

# testbench:

token_recog = DFA_tok_rec()

test_strings = [
    "abb",
    "aab",
    "babb",
    "aaabb",
    "baab",
    "abba",
    "abc",
    "bab"
]

for string in test_strings:
    if token_recog.is_valid_token(string):
        print(f"'{string}' is a valid token.")
    else:
        print(f"'{string}' is not a valid token.")
