import sys
import os

class Config():
    # Configuration object
    def __init__(self,):
        self.configDict = self.makeConfigDict()

    # Make the configuration file
    def makeConfigDict(self):

        # Empty dictionary
        dict = {}
        with open("config.txt") as cFile:
            for line in cFile:
                line = line.strip()
                line = line.split(' ')
                dict[line[0]] = line[1]

        return dict

    # Prints the configuration dictionary
    def printConfigDict(self):
        print(self.configDict)