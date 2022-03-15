class File:
    def __init__(self, lines):
        self.lines = lines

    def read(filename):
        lines = []
        
        with open(filename, "r") as f:
            lines = f.readlines()

        return File(lines)

