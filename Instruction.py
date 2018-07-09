import sys
import os

# Import classes from different files
from OpCode import OpCode
from Operand import Operands

# Instruction Class File
# Inherits the Opcode and Operands Class

class Instruction(OpCode, Operands):

    def __init__(self, instruction, usedValues):
        self.usedValues = usedValues
        self.opCode = OpCode(instruction)
        self.operands = Operands(instruction)
        self.gram = self.getGram()



    def getGram(self):

        # Creates the gram for a single instruction
        gram = self.opCode.opCode

        # Check if the instruction has any operands
        if self.operands.operands:
            # Loop through operands and create gram based on operand type
            for operand in self.operands.operands:
                counter = 0
                # Check if operand contains arithmetic
                if '+' in operand:
                    operand = operand.replace(' ', '')
                    operand = operand.split('+')

                    # Loop through all operands in arithmetic expression
                    for value in operand:
                        # Check if operand has been seen yet
                        if value in self.usedValues:
                            variable = self.usedValues.index(value)
                        else:
                            self.usedValues.append(value)
                            variable = len(self.usedValues) - 1
                        if counter == 0:
                            gramVariable = self.getOperandType(value) + str(variable)
                        else:
                            gramVariable = gramVariable +  " + " + self.getOperandType(value) + str(variable)
                        counter = counter + 1
                # Operand does NOT contain arithmetic
                else:
                    # Check if operand has been seen yet
                    if operand in self.usedValues:
                        # Operand has been seen
                        variable = self.usedValues.index(operand)

                    else:
                        # Operand has NOT been seen
                        self.usedValues.append(operand)
                        variable = len(self.usedValues) - 1
                    gramVariable = str(self.getOperandType(operand)) + str(variable)


                # Concatenation for gram variables
                gram = gram + '.' + gramVariable


        return gram

    # NOT FINISHED
    def getVariable(self, operand, usedValues):
        pass


    # Determine type of operand
    def getOperandType(self, operand):
        if operand[:2] == "0x":
            return "mem"
        elif operand[:2] == "#0":
            return "con"

        return "reg"

    # Print the Instruction's gram
    def printGram(self):
        print(self.gram)



