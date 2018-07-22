import os

import Global
from Instruction import Instruction
from Feature import Feature

class EcuFile:
    """
    Container class for each ECU file to analyze
    self.is_control: if file is the control in the analyzing
    self.features: array of Feature objects
    """

    def __init__(self, file_name, is_control=False):
        """
        EcuFile constructor
        :param file_name: ECU file that contains instructions
        :param control: whether file_name is the control file
        """
        branch_opcodes = ["cmp", "jmp", "bra", "jsr", "bbc", "bbs", "bcc", "bcs", "bne", "beq", "bpl", "bmi", "bvc", "bvs"]

        if os.path.exists(file_name):
            with open(file_name, "r") as file:
                file_lines = file.readlines()

                self.is_control = is_control
                self.features = {}

                if is_control:
                    self._load_control_features(file_lines, branch_opcodes)
                else:
                    self._load_experimental_features(file_lines, branch_opcodes)
            print("[success] Loaded " + file_name + " features")
        else:
            print("[ error ] " + file_name + " doesn't exist")
            sys.exit()

    def _load_control_features(self, file_lines, branch_opcodes):
        """
        Loads control file features
        :param file_name: ECU control file name
        """
        for i in range(len(file_lines)):
            features = []
            sensor = self._config_sensor(file_lines[i][1:])

            # Found instruction with sensor address
            if sensor is not None:
                # Grab instructions that contain branch instructions
                while True:
                    instruction_line = Global.format_line(file_lines[i])
                    features.append(Instruction(instruction_line))

                    if (i + 1 < len(file_lines)) and Global.format_line(file_lines[i + 1])[0] in branch_opcodes:
                        i += 1
                    else:
                        break

                # Add sensor to dictionary, then push on features
                feature_block = Feature(features)
                if sensor not in self.features:
                    self.features[sensor] = []
                self.features[sensor].append(feature_block)

    def _load_experimental_features(self, file_lines, branch_opcodes):
        """
        Loads experimental file features
        :param file_name: ECU file containing instructions
        """
        for i in range(len(file_lines)):
            # Check if instruction contains a memory address
            for operand in Global.format_line(file_lines[i])[1:]:
                if Global.get_operand_type(operand) == "mem":
                    features = []
                    counter = 0

                    # Create feature set with load instruction, and following control instructions
                    while True:
                        instruction_line = Global.format_line(file_lines[i + counter])
                        features.append(Instruction(instruction_line))

                        if (i + counter + 1 < len(file_lines)) and Global.format_line(file_lines[i + counter + 1])[0] in branch_opcodes:
                            counter += 1
                        else:
                            break

                    # Add memory features to group
                    feature_block = Feature(features)
                    if operand not in self.features:
                        self.features[operand] = []
                    self.features[operand].append(feature_block)

    def _config_sensor(self, file_line):
        """
        Gets the sensor if instruction contains a sensor address that appears in sensor config
        :param file_line: array of split instruction line
        :return: sensor address if found (Ex: battery_voltage), None if not
        """
        for operand in Global.format_line(file_line):
            for sensor, address in Global.config.items():
                if operand == address and Global.get_operand_type(operand) == "mem":
                    return sensor
        return None

    def __str__(self):
        """
        :return: formatted string with all features
        """
        content = ""

        for address in self.features:
            content += Global.config[address] + "\n" if self.is_control else address + "\n"

            for feature_block in self.features[address]:
                for instruction in feature_block.instructions:
                    content += "\t" + instruction.gram + "\n"
                content += "\n"

        return content