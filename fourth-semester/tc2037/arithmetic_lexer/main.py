import sys
from file import File
from helpers import *

def arithmetic_lexer(file):
    input_file = File.read(file)
    dfas = generate_dfas()

    for line in input_file.lines:
        line = line.strip()

        comment = ""
        comment_index = line.find("//")
        if comment_index != -1:
            comment = line[comment_index:]
            line = line[:comment_index]

        tokens = space_symbols(line)
        tokens = tokens.split()

        for token in tokens:
            print_token_type(token.strip(), dfas)

        if comment != "":
            print(comment, "-->", "Comentario")

if __name__ == "__main__":
    arithmetic_lexer(sys.argv[1])
