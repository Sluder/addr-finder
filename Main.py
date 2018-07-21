#!/usr/bin/python

import sys
import os

import Global
from EcuFile import EcuFile
from Instruction import Instruction

def _load_config(file_name):
    """
    Loads sensor labels & memory addresses (Ex: battery_voltage 0x102f)
    :param file_name: file name for config file
    """
    if os.path.exists(file_name):
        with open(file_name, "r") as file:
            for file_line in file:
                file_line = Global.format_line(file_line)

                # Format sensor addresses
                if not file_line[1].startswith("0x"):
                    file_line[1] = "0x" + file_line[1]

                Global.config[file_line[0]] = file_line[1]
        print("[success] Loaded config")
    else:
        print("[ error ] " + file_name + " doesn't exist")
        sys.exit()

if __name__ == "__main__":
    """
    Start of program
    :param argv: array execution arguments (config.txt control.txt ecu.txt)
    """
    _load_config(sys.argv[1])

    control_file = EcuFile(sys.argv[2], True)
    experimental_file = EcuFile(sys.argv[3], False)

    #print(experimental_file)
