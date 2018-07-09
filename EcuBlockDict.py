import sys
import os

from EcuBlock import EcuBlock

class EcuBlockDict():

    # ECU dictionary Constructor
    def __init__(self, ecuBlockList):
        self.ecuDict = self.makeEcuDict(ecuBlockList)

    # Make a dictionary for the potential sensor addresses
    def makeEcuDict(self, ecuBlockList):

        dict = {}
        for block in ecuBlockList:
            memAddress = block.ecuAddress
            if memAddress not in dict:
                dict[memAddress] = [block]
            else:
                dict[memAddress].append(block)

        return dict