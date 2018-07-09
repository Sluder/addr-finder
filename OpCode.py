import sys
import os



# Opcode Class File

class OpCode:

    def __init__(self, instruction):
        self.opCode = self.getOpCode(instruction)




    def getOpCode(self,instruction):

        # Obtain the OpCode for a single instruction
        # Returns an opCode string
        opCode = instruction.strip()
        opCode = opCode.split(' ')[0]


        return opCode