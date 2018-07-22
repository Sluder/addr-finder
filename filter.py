#!/usr/bin/python

import sys
import os

if __name__ == "__main__":
    """
    Start process of filtering disassembled ECU code
    :param argv: array execution arguments (input.txt)
    """
    file_name = sys.argv[1]
    lines = []

    # Check for file & start filtering
    if os.path.exists(file_name):
        with open(file_name, "r+", encoding="utf8") as file:
            for file_line in file:
                if file_line.startswith('Code') or file_line.startswith('VECTOR'):
                    continue

                file_line = file_line.partition(';')[0]
                file_line = file_line.rstrip().split()

                # Filter blank lines
                if file_line:
                    lines.append(' '.join(file_line[2:]))

            # Write filtered text to file
            file.truncate(0)

            for line in lines:
                file.write(line + '\n')

        print("[success] Filtered " + file_name)
    else:
        print("[ error ] " + file_name + " doesn't exist")
        sys.exit()