import sys
import os

# Import Instruction class from different file
from Instruction import Instruction

#KEY: Create a block for every potential memory address

class EcuBlock(Instruction):

    # ECU Block Constructor
    def __init__(self, instructionList, startIndex, branchOpcodes):
        self.ecuSearchStart = startIndex
        self.ecuNoOperands = startIndex
        self.ecuBlockStart = self.getEcuBlockStart(instructionList)
        self.ecuAddress = self.getEcuAddress(instructionList)
        self.ecuBlockEnd = self.getEcuBlockEnd(instructionList, branchOpcodes)
        self.ecuBlockInstructions = self.getEcuBlockInstructions(instructionList)
        self.ecuBlockOpCodes = self.getEcuBlockOpCodes()
        self.noOperandsCheck()


    # Find the location of the potential sensor address to make a block
    def getEcuBlockStart(self, instructionList):
        index = self.ecuSearchStart

        # Loop through every instruction until a memory address is found
        while index < len(instructionList):
            instruction = instructionList[index]
            instructionOperands = instruction.operands.operands
            if instructionOperands == None:
                return
            for operand in instructionOperands:
                # Check if operand is a memory address
                if operand[:2] == "0x":
                    return index
            index = index + 1

        return len(instructionList)


    # Retrieve the actual potential memory address for the block
    def getEcuAddress(self, instructionList):
        #print(self.ecuBlockStart)
        index = self.ecuBlockStart
        if index is not None:
            instructionOperands = instructionList[index].operands.operands
            for operand in instructionOperands:
                # Check if operand is a memory address
                if operand[:2] == "0x":
                    return operand

        return


    # Find the end index for this particular block (same as ControlBlock class)
    def getEcuBlockEnd(self, instructionList, branchOpcodes):
        #print(self.ecuBlockStart)
        index = self.ecuBlockStart
        if index == len(instructionList):
            return len(instructionList)
        if index is not None:
            while index < len(instructionList):
                if instructionList[index].opCode.opCode in branchOpcodes:
                    return index
                index = index + 1

        return index

    # Find the instructions for this particular block
    def getEcuBlockInstructions(self, instructionList):
        if self.ecuBlockEnd == len(instructionList):
            return
        index = self.ecuBlockStart
        blockInstructions = []
        if index is None:
            return
        while index <= self.ecuBlockEnd:
            blockInstructions.append(instructionList[index])
            index = index + 1
        self.ecuBlockEnd = self.ecuBlockEnd + 1
        return blockInstructions

    # Get the opCodes for this particular block
    def getEcuBlockOpCodes(self):
        opCodeList = []
        # Loop through every instruction in the Ecu Block
        if self.ecuBlockInstructions is None:
            return
        for instruction in self.ecuBlockInstructions:
            opCode = instruction.opCode.opCode
            opCodeList.append(opCode)

        return opCodeList

    # print ECU block opCodes
    def printEcuBlockFeature(self):
        if self.ecuBlockInstructions is None:
            return
        if self.ecuBlockStart == self.ecuBlockEnd:
            return
        feature = self.ecuBlockInstructions[0].opCode.opCode
        index = 1
        while index < len(self.ecuBlockInstructions):
            featureOpCode = self.ecuBlockInstructions[index].opCode.opCode
            feature = feature + "." + featureOpCode
            index = index + 1

        print(self.ecuAddress + ": " + feature)

    def noOperandsCheck(self):
        if self.ecuBlockEnd is None:
            self.ecuBlockEnd = self.ecuNoOperands + 1