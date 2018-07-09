#!/usr/bin/python

import sys
import os

def main(argv):
    """
    Start of program
    :param argv: array execution arguments (input.txt)
    """
    file_name = argv[0]
    lines = []

    # Check for file & start filtering
    if os.path.exists(file_name):
        with open(file_name, "r+", encoding="utf8") as file:
            for file_line in file:
                if file_line.startswith('Code') or file_line.startswith('VECTOR'):
                    continue

                file_line = file_line.partition(';')[0]
                file_line = file_line.rstrip().split()

                if file_line:
                    lines.append(' '.join(file_line[2:]))

            file.truncate(0)

            for line in lines:
                file.write(line + '\n')

        print("[success] Filtered " + file_name)
    else:
        print("[ error ] " + file_name + " doesn't exist")
        sys.exit()

if __name__ == "__main__":
    main(sys.argv[1:])
