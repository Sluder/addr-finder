import sys
import os

#import classes from different files
from Instruction import Instruction
from Config import Config
from ControlBlock import ControlBlock
from EcuBlock import EcuBlock
from EcuBlockDict import EcuBlockDict
from Jaccard import Jaccard
from prettytable import PrettyTable


def test():

    # Create instances (USED FOR BOTH PORTIONS)
    config = Config()
    branchOpcodes = ["jmp", "bra", "jsr", "bbc", "bbs", "bcc", "bcs", "bne", "beq", "bpl", "bmi", "bvc", "bvs"]

    # THIS PORTION IS FOR THE CONTROL FILE

    #Global Variables
    controlUsedValues = []
    controlInstructionList = []
    controlBlockDict = {}

    # Go through each line of the control file and make a list of instructions
    with open("control.txt") as controlFile:
        for line in controlFile:
            tmpControlInstruction = Instruction(line, controlUsedValues)
            controlInstructionList.append(tmpControlInstruction)

    # Create blocks for addresses from config (MAYBE TURN THIS INTO CLASS LIKE ECUBLOCKDICT)
    for key, value in config.configDict.items():
        startIndex = 0
        controlBlockList = []
        while startIndex < len(controlInstructionList) and startIndex != None:
            tmpControlBlock = ControlBlock(value, controlInstructionList, startIndex, branchOpcodes)
            #tmpControlBlock.printControlBlockFeature()
            controlBlockList.append(tmpControlBlock)
            startIndex = tmpControlBlock.controlBlockEnd

        # Adds unecessary block at the end: NEED TO FIX AT SOMEPOINT
        controlBlockList.pop()


        # Fill dictionary with features for each control sensor address
        # VALUE: sensorAddress
        # BLOCK LIST: list of features for each control sensor address
        controlBlockDict[value] = controlBlockList
    for key, value in controlBlockDict.items():
        for block in value:
            print(key)
            print(block.controlBlockOpCodes)



    # THIS PORTION IS FOR THE ECU FILE

    # Global Variables
    ecuUsedValues = []
    ecuInstructionList = []

    # Go through each line of the ECU file and make a list of instructions
    with open("test.txt") as ecuFile:
        for line in ecuFile:
            tmpEcuInstruction = Instruction(line, ecuUsedValues)
            ecuInstructionList.append(tmpEcuInstruction)
            #tmpEcuInstruction.printGram()

    #Create ECU blocks for each memory address in ECU file
    startIndex = 0
    ecuBlockList = []
    while startIndex < len(ecuInstructionList) and startIndex != None:
        tmpEcuBlock = EcuBlock(ecuInstructionList, startIndex, branchOpcodes)
        if startIndex < 1799:
            print(startIndex)
            print(tmpEcuBlock.ecuAddress)
            print(tmpEcuBlock.ecuBlockOpCodes)
        if tmpEcuBlock.ecuAddress is not None:
            ecuBlockList.append(tmpEcuBlock)
            #if tmpEcuBlock.ecuAddress == "0x102f":
                #print(tmpEcuBlock.ecuBlockOpCodes)
        startIndex = tmpEcuBlock.ecuBlockEnd

    ecuBlockDict = EcuBlockDict(ecuBlockList)

    # Create Jaccard Object
    jaccard = Jaccard(controlBlockDict, ecuBlockDict)
    #print(jaccard.foundSenors)

    # Make Table

    table = PrettyTable()
    # UPDATE THIS TO ADD SENSOR ADDRESSES AUTOMATICALLY
    table.field_names = ["Memory Address", "0x102f", "0x1071", "0x106f", "0x1185", "0x10a2", "0x1283"]
    tableDict = {}
    for key, value in jaccard.jaccardTuples.items():
        for tuple in value:
            address = tuple[0]
            if address not in tableDict:
                tableDict[address] = [tuple[1]]
            else:
                tableDict[address].append(tuple[1])
    for key, value in tableDict.items():
        tableList = value
        tableList = [key] + tableList
        table.add_row(tableList)

    #print(table)





if __name__ == '__main__':
    test()
