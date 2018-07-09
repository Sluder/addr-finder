import sys
import os

# Import Instruction class from different file
from Instruction import Instruction

class ControlBlock(Instruction):

    # Control block constructor
    def __init__(self, sensorAddress, instructionList, startIndex, branchOpcodes):
        self.controlSensorAddress = sensorAddress
        self.controlSearchStart = startIndex
        self.controlBlockStart = self.getControlBlockStart(instructionList)
        self.controlBlockEnd = self.getControlBlockEnd(instructionList, branchOpcodes)
        self.controlBlockInstructions = self.getControlBlockInstructions(instructionList)
        self.controlBlockOpCodes = self.getControlBlockOpCodes()


        # Variables for later semantic analysis
        #self.jmpList
        #self.callList
        #self.blockJmpList

    # Find the start index in instructionList for this particular block
    def getControlBlockStart(self, instructionList):
        index = self.controlSearchStart
        # Loop through every instruction
        while index < len(instructionList):
            instruction = instructionList[index]
            # Loop through operands in instruction
            instructionOperands = instruction.operands.operands
            if instructionOperands is not None:
                for operand in instructionOperands:
                    if operand == self.controlSensorAddress:
                        return index
            index = index + 1

        return len(instructionList)

    # Find the end index for this particular block
    def getControlBlockEnd(self, instructionList, branchOpcodes):
        index = self.controlBlockStart
        if index == len(instructionList):
            return len(instructionList)
        #instructionOpCode = instructionList[index].opCode.opCode

        while index and index < len(instructionList) and instructionList[index].opCode.opCode not in branchOpcodes:
            #print(index)
            index = index + 1

        return index

    # Find the instructions for this particular block
    def getControlBlockInstructions(self, instructionList):
        if self.controlBlockEnd == len(instructionList):
            return
        index = self.controlBlockStart
        blockInstructions = []

        while index <= self.controlBlockEnd:
            blockInstructions.append(instructionList[index])
            index = index + 1

        return blockInstructions

    def getControlBlockOpCodes(self):
        opCodeList = []
        # Loop through every instruction in the Ecu Block
        if self.controlBlockInstructions is None:
            return
        for instruction in self.controlBlockInstructions:
            opCode = instruction.opCode.opCode
            opCodeList.append(opCode)

        return opCodeList

    # Print control block opCodes
    def printControlBlockFeature(self):
        if self.controlBlockStart == self.controlBlockEnd:
            return
        feature = self.controlBlockInstructions[0].opCode.opCode
        index = 1
        while index < len(self.controlBlockInstructions):
            featureOpCode = self.controlBlockInstructions[index].opCode.opCode
            feature = feature + "." + featureOpCode
            index = index + 1

        print(self.controlSensorAddress + ": " + feature)


