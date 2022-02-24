class Expr:
    def __init__(self, string):
        self.expression = string


class Var(Expr):
    def __init__(self, string):
        super().__init__(string)
        self.var = string

    def __str__(self):
        return self.var


class Star(Expr):
    def __init__(self, string):
        super().__init__(string)
        pass

    def __str__(self):
        return f"Star({self.expression})"


class Concat(Expr):
    def __init__(self, string1, string2):
        self.expression1 = string1
        self.expression2 = string2

    def __str__(self):
        return f"Concat({self.expression1}, {self.expression2})"


class Union(Expr):
    def __init__(self, string1, string2):
        self.expression1 = string1
        self.expression2 = string2

    def __str__(self):
        return f"Union({self.expression1}, {self.expression2})"


def classToString(Expr):
    if isinstance(Expr, Concat):
        return f"Concat({Expr.expression1}, {Expr.expression2})"

    elif isinstance(Expr, Union):
        return f"Union({Expr.expression1}, {Expr.expression2})"

    elif isinstance(Expr, Star):
        return f"Star({Expr.expression})"


def parse(string):
    stack = []
    while string:
        if string.startswith('CONCAT '):
            string = string[len('CONCAT '):]
            stack.append(('Concat', string))

        elif string.startswith('STAR '):
            string = string[len('STAR '):]
            stack.append(('Star', string))

        elif string.startswith('UNION '):
            string = string[len('UNION '):]
            stack.append(('Union', string))

        else:
            elems = string.split(' ')
            string = string[len(elems[0]) + 1:]
            backup = stack[-1]
            expr = stack.pop(-1)
            if expr.__len__() < 3:
                stack.append((expr[0], elems[0], string))

            else:
                stack.append((expr[0], backup[1], elems[0], string))

    variables = ''
    rev_stack = reversed(stack)
    final_expressions = []
    for i in rev_stack:
        if i[0] == 'Star':
            for j in i[1::]:
                if j != '':
                    variables = variables + j

            lexem = Star(variables)
            variables = ''
            final_expressions.append(lexem)

        elif i[0] == 'Union':
            lexem = Union(i[1], i[2])
            final_expressions.append(lexem)

        elif i[0] == 'Concat':
            for j in i[1::]:
                if j != '':
                    variables = variables + j

            lexem = Concat(variables, '')
            variables = ''
            final_expressions.append(lexem)

    rev_final_backup = reversed(final_expressions)
    return rev_final_backup


def read_file():
    file = open("input.txt", "r")
    input_as_strings = file.read()
    file.close()
    return input_as_strings


def convertTostring(mylist):
    final_str = ''
    for i in mylist:
        final_str = final_str + str(i)

    return  final_str


if __name__ == '__main__':
    regular_expr = read_file()
    operators = parse(regular_expr)
    for i in operators:
        print(i)
    list = ['Test', 1, 3]
    print(convertTostring(list))