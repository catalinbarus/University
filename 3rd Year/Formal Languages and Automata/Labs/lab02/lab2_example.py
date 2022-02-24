class Dfa:
    def __init__(self, input_strings):
        self.alphabet = []

        self.initial_state = input_strings[0].strip()

        self.final_states = input_strings[-1]

        transitions = []
        for i in range(1, len(input_strings) - 1):
            transition = input_strings[i].strip()
            transitions.append(transition)
            if transition[2] not in self.alphabet:
                self.alphabet.append(transition[2])

        self.delta_function = {}
        for x in transitions:
            if (int(x[0]), x[2]) not in self.delta_function:
                self.delta_function[(int(x[0]), x[2])] = int(x[4])

    def one_step(self, configuration):
        state = configuration[0]
        word = configuration[1]
        if (state, word[0]) in self.delta_function:
            return self.delta_function[(state, word[0])], word[1::]
        else:
            return f"Cuvantul {word} nu este o configuratie corecta!"

    def is_word_accepted(self, word):
        keys = list(self.delta_function.keys())

        if word[0] != keys[0][1]:
            return f"Cuvantul {word} nu este un cuvant acceptat de acest dfa!"
        for x in word:
            if x not in self.alphabet:
                return f"Cuvantul {word} nu este un cuvant acceptat de acest dfa!"

        configuration = (0, word)
        for i in range(len(word)):
            configuration = self.one_step(configuration)

        if configuration[0] == 0:
            return f"Cuvantul {word} este acceptat de acest dfa!"
        else:
            return f"Cuvantul {word} nu este un cuvant acceptat de acest dfa!"

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
    input_strings = read_file()
    dfa = Dfa(input_strings)
    print(dfa)
    #print(dfa.is_word_accepted('abaaba'))

