class Dfa:
    def __init__(self, input):
        self.alphabet = []

        self.initial_state = input[0].strip()

        self.final_states = input[-1]

        transitions = []
        for i in range(1, len(input) - 1):
            transition = input[i].replace(" ", "")
            transitions.append(transition)
            if transition[1] not in self.alphabet:
                self.alphabet.append(transition[1])

        self.delta_function = {}
        for currentTrans in transitions:
            if (int(currentTrans[0]), currentTrans[1]) not in self.delta_function:
                self.delta_function[(int(currentTrans[0]), currentTrans[1])] = int(currentTrans[2])

    def __str__(self):
        return f"Alfabetul este: {self.alphabet}\n" \
               f"Starea initiala este: {self.initial_state}\n" \
               f"Starile finale sunt: {self.final_states}\n" \
               f"Functia delta este: {self.delta_function}\n"


def read_file():
    file = open("input.txt", "r")
    input_as_strings = file.readlines()
    file.close()
    return input_as_strings


if __name__ == '__main__':
    print("Test main")
    input = read_file()
    print(input[1].strip())
    dfa = Dfa(input)
    print(dfa)
