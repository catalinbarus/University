class Dfa:
    def __init__(self, input):
        self.alphabet = []

        self.initial_state = int(input[0].strip())
        self.final_state = int(input[-3].strip())

        self.priority = int(input[-2])
        self.token = input[-1]
        self.sink_states = []
        sink_state_candidates = []

        states = []
        for i in range(1, len(input) - 3):
            current_state = input[i].strip()
            states.append(current_state)
            if current_state[2] not in self.alphabet:
                self.alphabet.append(current_state[2])

        self.delta_function = {}
        for x in states:
            if (int(x[0]), x[2]) not in self.delta_function:
                self.delta_function[(int(x[0]), x[2])] = int(x[4])

        for x in states:
            if x[0] == x[4]:
                sink_state_candidates.append(int(x[0]))

        for x in sink_state_candidates:
            if sink_state_candidates.count(x) == self.alphabet.__len__():
                self.sink_states.append(x)

        self.sink_states = list(dict.fromkeys(self.sink_states))

    def step(self, configuration):
        state = configuration[0]
        word = configuration[1]
        if (state, word[0]) in self.delta_function:
            return self.delta_function[(state, word[0])], word[1::]
        else:
            return f"The word {word} is not a valid configuration!"

    def accept(self, word):
        keys = list(self.delta_function.keys())

        if word[0] != keys[0][1]:
            return False
        for x in word:
            if x not in self.alphabet:
                return False

        configuration = (0, word)
        for i in range(len(word)):
            configuration = self.step(configuration)

        if configuration[0] == self.final_state:
            return True
        else:
            return False

    def __str__(self):
        return f"DFA's token is: {self.token}\n" \
               f"The alphabet is: {self.alphabet}\n" \
               f"This DFA has a priotiry of: {self.priority}\n" \
               f"The initial state is: {self.initial_state}\n" \
               f"The final state is: {self.final_state}\n" \
               f"The sink states are: {self.sink_states}\n" \
               f"The delta function for this DFA is: {self.delta_function}\n"


def highestPriority(priorityList):

    acc = 0
    processed = ()
    noDuplicates = filter(lambda x: x[1] != '', priorityList)
    for x in noDuplicates:
        if x[0] > acc:
            acc = x[0]
            processed = x

    return processed


def read_file(filename):
    file = open(filename, "r")
    extracted = file.readlines()
    file.close()
    return extracted


class Lexer:
    def __init__(self, dfas):
        self.dfas = dfas

    def parse(self, word):
        initial_lexemes = []
        final_lexemes = []

        while word != '':
            for x in self.dfas:
                lexeme = ''

                for y in word:
                    if x.accept(y):
                        lexeme = lexeme + y
                        if word[1::] == '':
                            initial_lexemes.append((x.priority, lexeme))
                    else:
                        initial_lexemes.append((x.priority, lexeme))
                        break

                if initial_lexemes.__len__() == self.dfas.__len__():
                    final_lexemes.append(highestPriority(initial_lexemes))
                    initial_lexemes = []

            word = word[len(final_lexemes[-1][1])::]

        lexemes_with_tokens = []
        for x in final_lexemes:
            for y in self.dfas:
                if x[0] == y.priority:
                    lexemes_with_tokens.append((y.token, x[1]))

        return lexemes_with_tokens


if __name__ == '__main__':
    input_A3 = read_file("A3.txt")
    A3 = Dfa(input_A3)
    print(A3)

    input_A4 = read_file("A4.txt")
    A4 = Dfa(input_A4)
    print(A4)

    input_A5 = read_file("A5.txt")
    A5 = Dfa(input_A5)
    print(A5)

    dfas_list = [A3, A4, A5]

    lexer = Lexer(dfas_list)
    lexemes = lexer.parse('abaaabbabaaaab')
    print(lexemes)
