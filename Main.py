#!/usr/bin/python

import sys
import os

# Global
config = {}

class EcuFile:
    # todo: is this correct?
    global branch_opcodes
    branch_opcodes = ["cmp", "jmp", "bra", "jsr", "bbc", "bbs", "bcc", "bcs", "bne", "beq", "bpl", "bmi", "bvc", "bvs"]

    def __init__(self, file_name, is_control=False):
        """
        EcuFile constructor
        :param file_name: ECU file that contains instructions
        :param control: whether file_name is the control file
        """
        self.is_control = is_control

        if os.path.exists(file_name):
            if is_control:
                self._load_control_features(file_name)
            else:
                self._load_experimental_features(file_name)
            print("[success] Loaded " + file_name + " features")
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
            file_lines = file.readlines()

            for i in range(len(file_lines)):
                features = []
                sensor = self._config_sensor(file_lines[i][1:])

                # Found instruction with sensor address
                if sensor is not None:
                    file_lines[i] = format_line(file_lines[i])
                    features.append(Instruction(file_lines[i]))

                    # Grab instructions that contain branch instructions
                    while file_lines[i + 1][0] in branch_opcodes:
                        features.append(Instruction(file_lines[i]))
                        i += 1

                    # Add sensor to dictionary, then push on features
                    if sensor not in self.features:
                        self.features[sensor] = []
                    self.features[sensor].append(features)

    def _load_experimental_features(self, file_name):
        """
        Loads experimental file features
        :param file_name: ECU file containing instructions
        """
        pass

    def _config_sensor(self, file_line):
        """
        Gets the sensor if instruction contains a sensor address that appears in sensor config
        :param file_line: array of split instruction line
        :return: sensor address if found (Ex: battery_voltage), None if not
        """
        for operand in format_line(file_line):
            for sensor, address in config.items():
                if operand == address and get_operand_type(operand) == "mem":
                    return sensor
        return None

    def __str__(self):
        # todo: not finished
        content = ""

        if self.is_control:
            for sensor in self.features:
                content += sensor + "\n"

                for feature_set in self.features[sensor]:
                    for instruction in feature_set:
                        print(instruction)
        return content

class Instruction:
    """
    mnemonic: operation done in instruction
    gram: mnemonic.operands with operand type (Ex: lda.reg.mem)
    """

    def __init__(self, file_line):
        """
        Instruction constructor
        :param file_line: array of split instruction line
        """
        self.mnemonic = file_line[0]
        self.gram = self.mnemonic

        for i in range(len(file_line[1:])):
            operand = file_line[i + 1]

            if operand == "+":
                self.gram += "+"
            else:
                self.gram += "." + get_operand_type(operand)

    def __str__(self):
        return ("mnemonic: " + self.mnemonic + "\n" +
                "gram: " + self.gram)

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
                file_line = format_line(file_line)

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

def format_line(file_line):
    """
    :param file_line: string to format
    :return: split string with removed end spaces/tabs
    """
    file_line = file_line.strip()

    return [i.replace(",", "") for i in file_line.split()]

def main(argv):
    """
    Start of program
    :param argv: array execution arguments (config.txt control.txt ecu.txt)
    """
    load_config(argv[0])

    control_file = EcuFile(argv[1], True)

if __name__ == "__main__":
    main(sys.argv[1:])
