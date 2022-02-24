import sys

# Class used for building NFAs, starting from the base cases
class NFA:
    def __init__(self, exp):

        # Build the generic NFA for a variable
        if isinstance(exp, Var):

            self.alphabet = []
            self.alphabet.append(exp.var)

            self.initialState = 0
            self.finalState = 1

            self.states = []
            self.states.append(self.initialState)
            self.states.append(self.finalState)

            self.delta_function = {}
            self.delta_function[(0, exp.var)] = 1

        # Build the generic NFA for concatenation
        if isinstance(exp, Concat):
            nfa1 = exp.expression1
            nfa2 = exp.expression2

            self.alphabet = []
            self.states = []

            # Renumber staes for the second NFA (which will directly connect to the first one)
            nfa2StatesBackup = nfa2.states.copy()

            for i in range(len(nfa2StatesBackup)):
                nfa2StatesBackup[i] = len(nfa1.states) + i

            # Add states for new NFA in order
            for x in nfa1.states:
                self.states.append(x)

            for x in nfa2StatesBackup:
                self.states.append(x)

            # Add the alphabet for the new NFA
            for x in nfa1.alphabet:
                self.alphabet.append(x)

            for x in nfa2.alphabet:
                self.alphabet.append(x)

            # Check for any possible duplicate letters
            self.alphabet = list(dict.fromkeys(self.alphabet))

            # The initial state of the resulting NFA will automatically
            # be the initial state of the first NFA, while the final state
            # will be the final state of the second NFA
            self.initialState = nfa1.initialState
            self.finalState = nfa2StatesBackup[-1]

            # Compute the new delta function
            newNFA2Dict = {}

            count = 1
            for x in nfa2.delta_function:
                newNFA2Dict[(x[0] + len(nfa1.states), x[1])] = nfa2.delta_function[x] + len(nfa1.states)
                count = count + 1

            self.delta_function = {}
            self.delta_function.update(nfa1.delta_function)

            # Add an epsilon transition to unite both NFAs
            self.delta_function[(nfa1.finalState, "epsilon")] = nfa2StatesBackup[0]
            self.delta_function.update(newNFA2Dict)

        # Build the generic NFA for Kleene star
        if isinstance(exp, Star):

            nfa = exp.expression

            self.alphabet = []
            self.states = []

            # For Kleene star, we keep the same alpahbet
            self.alphabet = nfa.alphabet

            nfaStatesBackup = nfa.states.copy()

            # Renumber states for the new NFA
            for i in range(len(nfaStatesBackup)):
                nfaStatesBackup[i] += 1

            # Our input NFA will receive two new states that connect to
            # the initial state of the input NFA, as well as the final state
            self.initialState = nfaStatesBackup[0] - 1
            self.finalState = nfaStatesBackup[-1] + 1
            self.states.append(self.initialState)

            for x in nfaStatesBackup:
                self.states.append(x)

            self.states.append(self.finalState)

            # Compute the new delta function
            newDeltaFunction = {}

            for x in nfa.delta_function:
                newDeltaFunction[(x[0] + 1, x[1])] = nfa.delta_function[x] + 1

            self.delta_function = {}

            # We will add epsilon transitions according to the base case of a star NFA:
            # * One from the new initial state to the previous initial state
            # * One from the new initial state to the new final state
            # * One from the previous final state to the new final state
            # * One from the previous final state to the previous initial state
            self.delta_function[(self.initialState, "epsilon1")] = nfaStatesBackup[0]
            self.delta_function[(self.initialState, "epsilon2")] = self.finalState
            self.delta_function[(nfaStatesBackup[-1], "epsilon3")] = self.finalState
            self.delta_function[(nfaStatesBackup[-1], "epsilon4")] = nfaStatesBackup[0]
            self.delta_function.update(newDeltaFunction)

        # Build the generic NFA for plus
        if isinstance(exp, Plus):

            currentNFA = exp.expression

            # For plus, we just convert the input NFA to one of this form:
            # Plus(NFA) = Concat(NFA, Star(NFA))
            # There is no need to calculate plus as a standalone NFA
            newDFA = NFA(Concat(currentNFA, NFA(Star(currentNFA))))

            self.alphabet = newDFA.alphabet
            self.states = newDFA.states
            self.delta_function = newDFA.delta_function
            self.initialState = newDFA.initialState
            self.finalState = newDFA.finalState

        # Build the generic NFA for union
        if isinstance(exp, Union):
            nfa1 = exp.expression1
            nfa2 = exp.expression2

            self.alphabet = []
            self.states = []
            self.delta_function = {}

            # Compute the alphabet for the new NFA
            for x in nfa1.alphabet:
                self.alphabet.append(x)

            for x in nfa2.alphabet:
                self.alphabet.append(x)

            # Check for any possible duplicate letters
            self.alphabet = list(dict.fromkeys(self.alphabet))

            # Renumber the states of the input NFA according to this rule:

            # * The first input NFA will have its states renumbered by 1
            # (in order to connect seamlessly to the new state)

            # * The second input NFA will have its states renumbered after the first
            # input NFA and the final state will in this way become the second to last
            # state before the new final state
            nfa1StatesBackup = nfa1.states.copy()

            for i in range(len(nfa1StatesBackup)):
                nfa1StatesBackup[i] += 1

            self.initialState = nfa1StatesBackup[0] - 1

            self.states.append(self.initialState)

            for x in nfa1StatesBackup:
                self.states.append(x)

            nfa2StatesBackup = nfa2.states.copy()

            for i in range(len(nfa2StatesBackup)):
                nfa2StatesBackup[i] = len(nfa1.states) + i + 1

            for x in nfa2StatesBackup:
                self.states.append(x)

            self.finalState = nfa2StatesBackup[-1] + 1
            self.states.append(self.finalState)

            # Compute the new delta function of the NFA

            # We will add epsilon transitions according to the base case of am union NFA:
            # * One from the new initial state to the previous initial states of our input NFAS
            # * One from the previous final states of our input NFAs to the new final state
            self.delta_function[(self.initialState, "epsilon1")] = nfa1StatesBackup[0]
            self.delta_function[(self.initialState, "epsilon2")] = nfa2StatesBackup[0]
            self.delta_function[(nfa1StatesBackup[-1], "epsilon1")] = self.finalState
            self.delta_function[(nfa2StatesBackup[-1], "epsilon2")] = self.finalState

            # Compute the rest of the new delta function of the NFA
            newNFA1DeltaFunction = {}

            for x in nfa1.delta_function:
                newNFA1DeltaFunction[(x[0] + 1, x[1])] = nfa1.delta_function[x] + 1

            self.delta_function.update(newNFA1DeltaFunction)

            newNFA2DeltaFunction = {}

            for x in nfa2.delta_function:
                newNFA2DeltaFunction[(x[0] + len(nfa1.states) + 1, x[1])] = nfa2.delta_function[x] + len(nfa1.states) + 1

            self.delta_function.update(newNFA2DeltaFunction)

    def __str__(self):
        return f"alphabet: {self.alphabet} \n" \
               f"states: {self.states} \n" \
               f"initialState: {self.initialState} \n" \
               f"finalState: {self.finalState} \n" \
               f"deltafunction: {self.delta_function}"


# Class used for parsing a generic prenex expresssion into regex form
class Expr:
    def __init__(self, string):
        self.expression = string

# Class used for parsing the prenex form of a variable into regex form
class Var(Expr):
    def __init__(self, string):
        self.var = string

    def __str__(self):
        return self.var

# Class used for parsing the prenex form of Kleene star into regex form
class Star(Expr):
    def __init__(self, string):
        super().__init__(string)

    def __str__(self):
        return f"Star({self.expression})"

# Class used for parsing the prenex form of plus into regex form
class Plus(Expr):
    def __init__(self, string):
        super().__init__(string)

    def __str__(self):
        return f"Plus({self.expression})"

# Class used for parsing the prenex form of concatenation into regex form
class Concat(Expr):
    def __init__(self, string1, string2):
        self.expression1 = string1
        self.expression2 = string2

    def __str__(self):
        return f"Concat({self.expression1}, {self.expression2})"

# Class used for parsing the prenex form of union into regex form
class Union(Expr):
    def __init__(self, string1, string2):
        self.expression1 = string1
        self.expression2 = string2

    def __str__(self):
        return f"Union({self.expression1}, {self.expression2})"

# Function used when parsing prenex to regex form
def checkExpression(expr):

    # If current operator has both of its members filled
    if isinstance(expr, Concat) or isinstance(expr, Union):
        if expr.expression1 != "?" and expr.expression2 != "?":
            return True

        else:
            return False

    # If current operator has its member filled
    if isinstance(expr, Star) or isinstance(expr, Plus):
        if expr.expression != "?":
            return True

        else:
            return False

# Function used for converting the input to a regex
def parse(string):
    stack = []
    alphabet = []

    # Will be used to determine the order in which we build our NFA
    stackOrder = []

    # Append to a stack all the operations that occur in order (important for later)
    while string:

        # If we encounter a new Concat, add it to stack with no members (no members = ?)
        if string.startswith('CONCAT '):
            string = string[len('CONCAT '):]
            stack.append(Concat("?", "?"))

        # If we encounter a new Kleene Star, add it to stack with no members (no members = ?)
        elif string.startswith('STAR '):
            string = string[len('STAR '):]
            stack.append(Star("?"))

        # If we encounter a new Plus, add it to stack with no members (no members = ?)
        elif string.startswith('PLUS '):
            string = string[len('PLUS '):]
            stack.append(Plus("?"))

        # If we encounter a new Union, add it to stack with no members (no members = ?)
        elif string.startswith('UNION '):
            string = string[len('UNION '):]
            stack.append(Union("?", "?"))

        # If we encounter something else, it is a variable
        else:
            alphabet.append(string[0])

            variable = Var(string[0])
            ok = 0
            stack.append(variable)

            # Check if before this variable we had operators, in order to add this variable as a member
            # to one of the operators
            if len(stack) > 1:

                # If we had an Union or a Concat check if we should add the variable
                # as left or right member
                if isinstance(stack[-2], Union) or isinstance(stack[-2], Concat):
                    if stack[-2].expression1 == "?":
                        stack[-2].expression1 = variable

                        # Add variable to the order of steps for building NFA
                        stackOrder.append(stack[-2].expression1)
                        ok = 1

                    elif stack[-2].expression2 == "?":
                        stack[-2].expression2 = variable

                        # Add variable to the order of steps for building NFA
                        stackOrder.append(stack[-2].expression2)
                        ok = 1

                # If we had a Kleene star or a Plus, just check if its available member slot is free
                if isinstance(stack[-2], Star) or isinstance(stack[-2], Plus):

                    if stack[-2].expression == "?":
                        stack[-2].expression = variable

                        # Add variable to the order of steps for building NFA
                        stackOrder.append(stack[-2].expression)
                        ok = 1

            # If we successfully added the variable to an operator, remove it from the stack
            if ok == 1:
                stack.pop()

            # After inserting the current variable, check if an operator has been filled
            # and the member/members are in place (there are no "?" marks around)
            while len(stack) > 1 and checkExpression(stack[-1]) == True:

                # If our filled operator is an Union or a Concat
                if isinstance(stack[-1], Union) or isinstance(stack[-1], Concat):

                    # If the operator before it is a Star or a Plus and hasn't been filled
                    # add current operator to it
                    if isinstance(stack[-2], Star) or isinstance(stack[-2], Plus):
                        stack[-2].expression = stack[-1]

                        # Add operator to the order of steps for building NFA
                        stackOrder.append(stack[-2].expression)
                        stack.pop()
                        if len(stack) == 1:
                            break

                    # If the operator before it is an Union or a Concat and hasn't been filled
                    # add current operator to it
                    if isinstance(stack[-2], Union) or isinstance(stack[-2], Concat):

                        # Check if we should add operator as either left or right member
                        if stack[-2].expression1 == "?":
                            stack[-2].expression1 = stack[-1]

                            # Add operator to the order of steps for building NFA
                            stackOrder.append(stack[-2].expression1)
                            stack.pop()
                            if len(stack) == 1:
                                break

                        else:
                            stack[-2].expression2 = stack[-1]

                            # Add operator to the order of steps for building NFA
                            stackOrder.append(stack[-2].expression2)
                            stack.pop()
                            if len(stack) == 1:
                                break

                # If our filled operator is a Kleene star or a Plus
                if isinstance(stack[-1], Star) or isinstance(stack[-1], Plus):

                    # If the operator before it is a Star or a Plus and hasn't been filled
                    # add current operator to it
                    if isinstance(stack[-2], Star) or isinstance(stack[-2], Plus):
                        stack[-2].expression = stack[-1]

                        # Add operator to the order of steps for building NFA
                        stackOrder.append(stack[-2].expression)
                        stack.pop()
                        if len(stack) == 1:
                            break

                    # If the operator before it is an Union or a Concat and hasn't been filled
                    # add current operator to it
                    if isinstance(stack[-2], Union) or isinstance(stack[-2], Concat):

                        # Check if we should add operator as either left or right member
                        if stack[-2].expression1 == "?":
                            stack[-2].expression1 = stack[-1]

                            # Add operator to the order of steps for building NFA
                            stackOrder.append(stack[-2].expression1)
                            stack.pop()
                            if len(stack) == 1:
                                break

                        else:
                            stack[-2].expression2 = stack[-1]

                            # Add operator to the order of steps for building NFA
                            stackOrder.append(stack[-2].expression2)
                            stack.pop()
                            if len(stack) == 1:
                                break

            # Cut currently parsed element from the main string
            if len(string) > 1:
                string = string[len(variable.var) + 1:]

            else:
                string = ""

    # Now we have the order of steps (or order of NFAs we should build) to reach
    # the fully converted NFA in a stack
    stackOrder.append(stack[0])

    return stackOrder

# Function that receives the stack with the steps required to
# build the full NFA of our regex
def regexToNFA(stackOrder):

    # For each step in the stack we build a NFA that will be used to build
    # the next NFA in the stack and so on, till we get the final NFA of our regex
    currentNFAs = []

    # We will process all steps individually till our stack is empty
    while len(stackOrder) > 0:

        for i in range(len(stackOrder)):

            # If the current step is a variable, build the NFA for it
            if isinstance(stackOrder[i], Var):

                currentNFAs.append(NFA(stackOrder[i]))

                # If our regex is just a letter, that's all we have to do
                if len(stackOrder) == 1:
                    del stackOrder[i]

            # If our current step is concatenation, we build its NFA based on the
            # previously two computed NFAs, which will become its members
            elif isinstance(stackOrder[i], Concat):
                currentNFAs.append(NFA(Concat(currentNFAs[-2], currentNFAs[-1])))

                # After the computation, we no longer need the NFAs for the members
                # (a better NFA has taken their place)
                del currentNFAs[-2]
                del currentNFAs[-2]

                # Also delete all steps from stack from beginning to this one
                # to avoid unwanted results
                stackOrder = stackOrder[i + 1:]
                break

            # If our current step is union, we build its NFA based on the
            # previously two computed NFAs, which will become its members
            elif isinstance(stackOrder[i], Union):
                currentNFAs.append(NFA(Union(currentNFAs[-2], currentNFAs[-1])))

                # After the computation, we no longer need the NFAs for the members
                # (a better NFA has taken their place)
                del currentNFAs[-2]
                del currentNFAs[-2]

                # Also delete all steps from stack from beginning to this one
                # to avoid unwanted results
                stackOrder = stackOrder[i + 1:]
                break

            # If our current step is Kleene star, we build its NFA based on the
            # previously computed NFA, which will become its member
            elif isinstance(stackOrder[i], Star):
                currentNFAs.append(NFA(Star(currentNFAs[-1])))

                # After the computation, we no longer need the NFA for the member
                # (a better NFA has taken its place)
                del currentNFAs[-2]

                # Also delete all steps from stack from beginning to this one
                # to avoid unwanted results
                stackOrder = stackOrder[i + 1:]
                break

            # If our current step is plus, we build its NFA based on the
            # previously computed NFA, which will become its member
            elif isinstance(stackOrder[i], Plus):
                currentNFAs.append(NFA(Plus(currentNFAs[-1])))

                # After the computation, we no longer need the NFA for the member
                # (a better NFA has taken its place)
                del currentNFAs[-2]

                # Also delete all steps from stack from beginning to this one
                # to avoid unwanted results
                stackOrder = stackOrder[i + 1:]
                break

    # At the end, our list of processed NFAs will only contain the final, desirable NFA
    return currentNFAs[0]


# Function used for computing the epsilon closures of our NFA
def getEpsilonClosures(epsilonClosures, myNFA):

    # Add the current state as a member of its epsilon closure
    for x in myNFA.states:
        epsilonClosures[x] = []
        epsilonClosures[x].append(x)

    # Add the epsilon transitions that are directly connected to the current state
    for x in myNFA.states:
        for y in myNFA.delta_function:
            if x == y[0] and y[1].startswith("epsilon"):
                epsilonClosures[x].append(myNFA.delta_function[y])

    # Check if the state at the end of an epsilon transition has further
    # epsilon transitions
    for x in epsilonClosures:

        # If the list of epsilon closures for the current state is greater
        # than one, then for sure it has multiple epsilon transitions
        if len(epsilonClosures[x]) > 1:
            visited = []
            for i in range(len(myNFA.states)):
                visited.append(0)

            # We will keep looking for all epsilon closures for the current state
            searchFurtherClosures = epsilonClosures[x][1:]

            while len(searchFurtherClosures) > 0:

                # If we find additional lists of closures greater than one
                # we continue to search for more epsilon closures
                for i in range(len(searchFurtherClosures)):
                    if len(epsilonClosures[searchFurtherClosures[i]]) > 1:

                        # Add currently found closure to the total of closures of current state
                        epsilonClosures[x] = epsilonClosures[x] + epsilonClosures[searchFurtherClosures[i]]

                        # Mark current closure for this state as visited in case we will reach
                        # a loop later on
                        visited[searchFurtherClosures[i]] = 1
                        epsilonClosures[x] = list(dict.fromkeys(epsilonClosures[x]))

                        # Sort closures so we won't get duplicate states when trying to
                        # build the DFA
                        epsilonClosures[x] = sorted(epsilonClosures[x])
                        checkClosure = epsilonClosures[searchFurtherClosures[i]].copy()
                        checkClosure = checkClosure[1:]
                        nextClosure = []

                        # Only check the closures for the newly found state if they weren't
                        # already visited (to avoid loops)
                        for j in range(len(checkClosure)):
                            if visited[checkClosure[j]] == 1:
                                continue
                            else:
                                nextClosure.append(checkClosure[j])

                        # Keep on finding closures till our stack is empty
                        del searchFurtherClosures[i]
                        searchFurtherClosures = searchFurtherClosures + nextClosure
                        break
                    else:
                        del searchFurtherClosures[i]
                        break

    return epsilonClosures

# Function used for converting one list of epsilon closures
# to a DFA state
def convertListToString(list):

    word = ""
    for x in list:
        word = word + str(x)

    return word

# Function used for reading the inputs
def read_file(filename):
    file = open(filename, "r")
    input_as_strings = file.read()
    file.close()
    return input_as_strings

# Function used for writing final results
def write_file(filename, string):
    file = open(filename, "w")
    file.write(string)
    file.close()

# Main implementation of getting the desired DFA using the functions described above
if __name__ == '__main__':

    # Get required parameters for the checker
    args = sys.argv[1:]
    finput = args[0]
    foutput = args[1]

    # Read prenex form expression
    regular_expr = read_file(finput)

    # Convert it to an oop regex
    operators = parse(regular_expr)

    # Convert that regex to a NFA
    myNFA = regexToNFA(operators)

    # Determine epsilon closures for our NFA
    epsilonClosures = {}
    epsilonClosures = getEpsilonClosures(epsilonClosures, myNFA)

    dfaDelta = {}

    # The order in which we encounter new states will determine
    # how we number the states for our DFA
    dfaIndexes = []
    finalStates = []

    # The initial state of our DFA will be the concatenation
    # of states from the epsilon closure of the initial state of the NFA
    initialState = epsilonClosures[0]
    initialDFAStates = []
    initialDFAStates.append(initialState)

    state = ""
    processed = []

    # Process all possible linking states till all of them have a connection
    # to other states and we no longer have to analyse any of them
    while len(initialDFAStates) > 0:

        # Mark newly found state and add it in order
        # as a new state for our DFA
        for x in initialDFAStates[0]:
            state = state + str(x)

        if state not in dfaIndexes:
            dfaIndexes.append(state)

        state = ""

        # A new DFA state will be built upon the concatenation
        # of multiple NFA states

        # Check if those concatenated states go somewhere else when receiving
        # a letter from our alphabet
        for x in myNFA.alphabet:
            count = 0
            for y in initialDFAStates[0]:

                # If a final state from our NFA is found in the concatenation of states
                # then it means we found a new final state for our DFA
                if y == myNFA.finalState:
                    finalStates.append(convertListToString(initialDFAStates[0]))

                # If we find a path from one of our states when receiving a letter
                # add the connection in the delta function of our DFA
                if (y, x) in myNFA.delta_function:

                    # Check if we hadn't processed this state already (to avoid loops)
                    if epsilonClosures[myNFA.delta_function[(y, x)]] not in processed:
                        initialDFAStates.append(epsilonClosures[myNFA.delta_function[(y, x)]])
                    dfaDelta[(convertListToString(initialDFAStates[0]), x)] = convertListToString(epsilonClosures[myNFA.delta_function[(y, x)]])

                # If we haven't found a path, remember how many states didn't accept that letter
                else:
                    count += 1

            # If all states from our concatenation didn't accept that letter
            # mark this state as a sink one
            if count == len(initialDFAStates[0]):
                dfaDelta[(convertListToString(initialDFAStates[0]), x)] = "sink"

        # Mark recently processed state to avoid duplicate analysis
        processed.append(initialDFAStates[0])

        # Continue to process other remaining states
        initialDFAStates = initialDFAStates[1:]

    # Add all sink to sink transitions to our delta function
    for x in myNFA.alphabet:
        dfaDelta[("sink", x)] = "sink"
    dfaIndexes.append("sink")

    # Get final states for the new DFA
    finalStates = list(dict.fromkeys(finalStates))

    for i in range(len(finalStates)):
        finalStates[i] = dfaIndexes.index(finalStates[i])

    # Renumber states in delta function so that they are in order
    newDFADelta = {}

    for x in dfaDelta:
        newDFADelta[(dfaIndexes.index(x[0]), x[1])] = dfaIndexes.index(dfaDelta[x])

    dfaDelta = newDFADelta

    # Write final results according to ref files
    finalResult = ""
    for x in myNFA.alphabet:
        finalResult = finalResult + x
    finalResult = finalResult + "\n"
    finalResult = finalResult + str(len(dfaIndexes))
    finalResult = finalResult + "\n"
    finalResult = finalResult + str(dfaIndexes.index(dfaIndexes[0]))
    finalResult = finalResult + "\n"
    for i in range(len(finalStates)):
        if i == len(finalStates) - 1:
            finalResult = finalResult + str(finalStates[i]) + "\n"
        else:
            finalResult = finalResult + str(finalStates[i]) + " "

    idx = 0
    for x in dfaDelta:
        if idx == len(dfaDelta) - 1:
            finalResult = finalResult + str(x[0]) + "," + "'" + x[1] + "'" + "," + str(dfaDelta[x])
        else:
            finalResult = finalResult + str(x[0]) + "," + "'" + x[1] + "'" + "," + str(dfaDelta[x]) + "\n"
            idx += 1

    write_file(foutput, finalResult)
