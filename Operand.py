import sys
import os

# Operand Class File

class Operands:

    def __init__(self, instruction):
        self.operands = self.getOperands(instruction)




    def getOperands(self, instruction):

        # Obtain the Operands for a single instruction
        # Returns a list of Operands
        operands = instruction[3:]
        operands = operands.strip()
        operands = operands.replace(" ", "")
        operands = operands.split(',')

        # Check to see if there are no operands
        if len(operands) == 1 and operands[0] == '':
            return None

        return operands