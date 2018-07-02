#!/usr/bin/python

import sys
import os

# Global
config = {}

class EcuFile:
    branch_opcodes = ["jmp", "bra", "jsr", "bbc", "bbs", "bcc", "bcs", "bne", "beq", "bpl", "bmi", "bvc", "bvs"]

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
        self.features = {}

        with open(file_name, "r") as file:
            for file_line in file:
                file_line = file_line.strip()
                file_line = [i.replace(",", "") for i in file_line.split()]

                if not file_line:
                    continue

                # Find instructions that contain the config sensor addresses
                for operand in file_line[1:]:
                    sensor = self._config_sensor(file_line[1:])

                    if sensor is not None:
                        while True:
                            instruction = Instruction(file_line)

                            file_line = file.next()
                            sensor = self._config_sensor(file_line[1:])

                            if sensor is None:
                                break

    def _config_sensor(self, file_line):
        """
        Gets the sensor if instruction contains a sensor address that appears in sensor config
        :param file_line: array of split instruction line
        :return: sensor address if found (Ex: battery_voltage), None if not
        """
        for operand in file_line:
            for sensor, address in config.items():
                if operand == address and get_operand_type(operand) == "mem":
                    return sensor
        return None

    def _load_experimental_features(self, file_name):
        """
        Loads experimental file features
        :param file_name: ECU file containing instructions
        """
        pass

class Instruction:
    def __init__(self, file_line):
        """
        Instruction constructor
        :param file_line: array of split instruction line
        """
        self.opcode = file_line[0]
        self.gram = self.opcode

        for i in range(len(file_line[1:])):
            operand = file_line[i + 1]

            if operand in ["+", "-"]:
                print(operand)
            else:
                self.gram += "." + get_operand_type(operand)

    def __str__(self):
        pass

def get_operand_type(operand):
    """
    Gets the operand type for an instruction
    :param operand: operand string (Ex: 0x102f, al)
    :return: type of operand (Ex. 0x102f => mem)
    """
    if operand.startswith("#0"):
        return "con"
    elif operand.startswith("0x"):
        return "mem"
    return "reg"

def load_config(file_name):
    """
    Loads sensor labels
    :param file_name: file name for config file
    """
    if os.path.exists(file_name):
        with open(file_name, "r") as file:
            for file_line in file:
                file_line = file_line.strip()
                file_line = file_line.split()

                if not file_line:
                    continue

                # Format sensor addresses
                if not file_line[1].startswith("0x"):
                    file_line[1] = "0x" + file_line[1]

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

if __name__ == "__main__":
    main(sys.argv[1:])
