# Class used for parsing DFA information
class Dfa:
    def __init__(self, input):

        # Initialize alphabet
        self.alphabet = []
        initial_alphabet = input[0].strip("\n")

        checkForNewline = str(initial_alphabet)

        # Treat the case where we parse \n into the alphabet
        if checkForNewline == "\\n":
            self.alphabet.append("\n")

        else:
            for x in initial_alphabet:
                self.alphabet.append(x)

        # Initialize token
        self.token = input[1].strip()

        # Initialize initial and final states
        self.initial_state = int(input[2].strip())
        self.final_states = []
        final_states = str(input[-1].strip())

        # Append final states to list
        if final_states.__len__() == 1:
            self.final_states.append(int(final_states))

        # Check if the final states, are states >= 10
        else:
            state = ""
            step = 0
            for x in range(final_states.__len__()):
                if final_states[x] == " ":
                    self.final_states.append(int(state))
                    state = ""
                    step = x

                else:
                    state = state + final_states[x]

            self.final_states.append(int(final_states[step::]))

        self.sink_states = []

        # Configure the delta function
        states = []
        for i in range(3, len(input) - 1):
            current_state = str(input[i].strip())
            noComma = current_state.split(',')

            # Once again, check if we have \n, in order to parse it
            # correctly
            if self.token == "NEWLINE":
                noComma[1] = "\n"

            states.append(noComma)

        self.delta_function = {}

        # Check if a current state is already in delta function
        for x in states:
            if self.token == "NEWLINE":

                # If it's not, add it (parse \n correctly)
                if (int(x[0]), x[1]) not in self.delta_function:
                    self.delta_function[(int(x[0]), x[1])] = int(x[2])
            else:
                # If it's not, add it
                if (int(x[0]), x[1]) not in self.delta_function:
                    self.delta_function[(int(x[0]), x[1][1])] = int(x[2])

        # Compute the inverted states for the current DFA
        inverted_states = states
        for x in inverted_states:
            backup = x[0]
            x[0] = x[2]
            x[2] = backup

        # Compute the inverted delta function in order to determine
        # the sink states
        inverted_delta_function = {}
        for x in inverted_states:
            if (int(x[0]), x[1]) not in inverted_delta_function:
                inverted_delta_function[(int(x[0]), x[1])] = [int(x[2])]

            if (int(x[0]), x[1]) in inverted_delta_function:
                inverted_delta_function[(int(x[0]), x[1])].append(int(x[2]))

        for x in inverted_states:
            inverted_delta_function[(int(x[0]), x[1])] \
                = list(dict.fromkeys(inverted_delta_function[(int(x[0]), x[1])]))

        # Compute all the states of the DFA
        allStates = []
        for x in states:
            allStates.append(int(x[0]))
            allStates.append(int(x[2]))

        allStates = list(dict.fromkeys(allStates))

        # Compute all the non sink states of thr DFA
        nonSinkStates = []
        nonSinkStatesDict = inverted_delta_function.items()
        for x in nonSinkStatesDict:
            for y in x[1]:
                nonSinkStates.append(y)

        nonSinkStates = list(dict.fromkeys(nonSinkStates))

        # If a state is not a non sink state, then add it to the
        # sink state list
        for x in allStates:
            if x not in nonSinkStates:
                self.sink_states.append(x)

    # Function that takes and a configuration and goes to the
    # next step in a DFA, if it can consume a letter
    def step(self, configuration):
        state = configuration[0]
        word = configuration[1]
        if (state, word[0]) in self.delta_function:
            return self.delta_function[(state, word[0])], word[1::]

        # If not, return same configuration as provided on input
        else:
            return configuration

    # Check if a word is accepted by a DFA or not
    def accept(self, word):

        # If a letter is not in the alphabet, then that word is rejected
        for x in word:
            if x not in self.alphabet:
                return False

        configuration = (0, word)
        for i in range(len(word)):
            configuration = self.step(configuration)

        # If a configuration reaches a final state and our word is consumed
        # it is accepted
        if configuration[0] in self.final_states:
            return True
        else:
            return False

    def __str__(self):
        return f"DFA's token is: {self.token}\n" \
               f"The alphabet is: {self.alphabet}\n" \
               f"The initial state is: {self.initial_state}\n" \
               f"The final states are: {self.final_states}\n" \
               f"The sink states are: {self.sink_states}\n" \
               f"The delta function for this DFA is: {self.delta_function}\n"


def read_file(filename):
    file = open(filename, "r")
    extracted = file.readlines()
    file.close()
    return extracted

def read_input(filename):
    file = open(filename, "r")
    extracted = file.read()
    file.close()
    return extracted

class Lexer:

    # Get the list of all DFAs
    def __init__(self, dfas):
        self.dfas = dfas

    # Receive a word and split it into lexemes
    def parse(self, word):

        final_lexemes = []

        # Check if we still have letters in our word
        while word != '':
            lexemDict = {}

            # Check all our DFAs for a possible lexeme
            for x in range(len(self.dfas)):
                lexem = ""

                # Attempt to check current word for current DFA
                configuration = (0, word)

                # Try and get the largest lexeme possbile
                while configuration[1] != '':

                    # If the current configuration is not a valid one for current DFA
                    # go to the next DFA
                    if (configuration[0], configuration[1][0]) not in self.dfas[x].delta_function:
                        break

                    # Increase potential lexeme in size
                    lexem = lexem + configuration[1][0]

                    # Get the next step in the current DFA
                    configuration = self.dfas[x].step(configuration)

                    # If we reached a final state, we remember this lexeme
                    if configuration[0] in self.dfas[x].final_states:
                        lexemDict[self.dfas[x].token] = lexem

                    # If we reached a sink state, go to the next DFA
                    if configuration[0] in self.dfas[x].sink_states:
                        break
            lenmax = 0
            lexemID = -1
            lexemDictValues = list(lexemDict.values())
            lexemDictKeys = list(lexemDict.keys())

            # For the current "round", iterate over all lexeme candidates
            # and get the longest one. This will be the lexeme for this "round"
            if len(lexemDict) > 0:
                for x in range(len(lexemDictValues)):
                    if len(lexemDictValues[x]) > lenmax:
                        lenmax = len(lexemDictValues[x])
                        lexemID = x

                newLexem = (lexemDictKeys[lexemID], lexemDictValues[lexemID])
                final_lexemes.append(newLexem)
                word = word[len(newLexem[1])::]
            else:
                break

        # Parse will return a list of pairs in this form [(TOKEN, lexeme)]
        return final_lexemes

# Function used for writing final results
def write_file(filename, string):
    file = open(filename, "w")
    file.write(string)
    file.close()

# Function used for parsing data
def runlexer(lexer, finput, foutput):

    # Read our DFAs
    input = read_file(lexer)
    wordInput = read_input(finput)

    # Determine total number of DFAs
    numOfDFAS = 1
    for x in input:
        if x == "\n":
            numOfDFAS = numOfDFAS + 1


    # For ease of use, create a dictionary for knowing which DFA
    # has which list of data
    myDFASDict = {}
    input2 = input
    delete = False
    step = 0
    for x in range(numOfDFAS):
        currentDFA = []

        if delete == True:
            del input[0:step + 1]
            step = 0
            delete = False

        for y in range(input2.__len__()):
            if input2[y] == "\n":
                myDFASDict[x] = currentDFA
                delete = True
                step = y
                break

            elif y == input2.__len__() - 1:
                input2[y] = input2[y] + "\n"
                currentDFA.append(input2[y])
                myDFASDict[x] = currentDFA
                break

            else:
                currentDFA.append(input2[y])

    # Create a list with Dfa objects
    Dfas_List = []
    for x in range(myDFASDict.__len__()):
        Dfas_List.append(Dfa(myDFASDict[x]))

    # Give that list to the lexer
    lexer = Lexer(Dfas_List)

    # Check if a given word can be split into lexemes
    # according to the DFAs in our list
    lexemes = lexer.parse(wordInput)

    # Write results in a file
    output = ""
    for x in range(len(lexemes)):
        if x < len(lexemes) - 1:
            output = output + lexemes[x][0]
            output = output + ' '
            if lexemes[x][0] == "NEWLINE":
                output = output + "\\n"
            else:
                output = output + lexemes[x][1]
            output = output + '\n'
        else:
            output = output + lexemes[x][0]
            output = output + ' '
            if lexemes[x][0] == "NEWLINE":
                output = output + "\\n"
            else:
                output = output + lexemes[x][1]

    write_file(foutput, output)





