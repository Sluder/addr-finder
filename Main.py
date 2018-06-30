#!/usr/bin/python

import sys
import os

# Global
config = {}

class EcuFile:
    branch_opcodes = []

    def __init__(self, file_name, is_control=False):
        """
        EcuFile constructor
        :param file_name: ECU file that contains instructions
        :param control: whether file_name is the control file
        """
        if os.path.exists(file_name):
            if is_control:
                self._load_control_features(file_name)
            else:
                self._load_experimental_features(file_name)
        else:
            print("[ error ] " + file_name + " doesn't exist")
            sys.exit()

    def _load_control_features(self, file_name):
        """
        Loads control file features
        :param file_name: ECU control file name
        """
        with open(file_name, "r") as file:
            for file_line in file:
                file_line = file_line.strip()

                if not file_line:
                    continue

                file_line = file_line.split()

    def _load_experimental_features(self, file_name):
        print("exp")

class Instruction:
    def __init__(self, file_line):
        print(file_line)

    def __str__(self):
        pass

def load_config(file_name):
    """
    Loads sensor labels
    :param file_name: file name for config file
    """
    if os.path.exists(file_name):
        with open(file_name, "r") as file:
            for file_line in file:
                file_line = file_line.strip()

                if not file_line:
                    continue

                config[file_line[0]] = file_line[1]
        print("[success] Loaded config")
    else:
        print("[ error ] " + file_name + " doesn't exist")
        sys.exit()

def main(argv):
    """
    Start of program
    :param argv: execution arguments (config.txt control.txt ecu.txt)
    """
    load_config(argv[0])

    control_file = EcuFile(argv[1], True)
    exp_file = EcuFile(argv[2])

if __name__ == "__main__":
    main(sys.argv[1:])
