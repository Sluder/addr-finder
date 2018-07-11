import sys
import os

from EcuBlockDict import EcuBlockDict


class Jaccard():

    # Jaccard Object Constructor
    def __init__(self, controlBlockDict, ecuBlockDict):
        self.jaccardTuples = self.makeJaccardTuples(controlBlockDict, ecuBlockDict)
        self.foundSensors = self.findSensors()


    # Make a dictionary that pairs sensor addresses from the control and ecu files
    # THIS IS WHERE WE SYNTACTICALLY FIND THE SENSOR ADDRESS FROM THE ECU FILE
    def makeJaccardTuples(self, controlBlockDict, ecuBlockDict):
        ecuDict = ecuBlockDict.ecuDict
        controlDict = controlBlockDict
        jaccardDict = {}


        # Loop through both dictionaries (MIGHT HAVE RUNTIME PROBLEM)
        # ControlKey = Sensor Address from control file
        # ControlValue = controlBlockList for particular sensor
        # ecuKey = Potential Sensor Address from ECU file
        # ecuValue = ecuBlockList for particular potential sensor address
        for controlKey, controlValue in controlDict.items():
            jaccardList = []
            for ecuKey, ecuValue in ecuDict.items():
                jaccardList = []
                for ecuBlock in ecuValue:
                    for controlBlock in controlValue:
                        ecuOpcodeList = ecuBlock.ecuBlockOpCodes
                        controlOpcodeList = controlBlock.controlBlockOpCodes
                        jaccardDistance = self.calculateJaccard(controlOpcodeList, ecuOpcodeList)
                        jaccardTuple = (ecuBlock.ecuAddress, jaccardDistance)
                        jaccardList.append(jaccardTuple)

                # THIS IS THE PROBLEM
                if controlKey not in jaccardDict:
                    jaccardDict[controlKey] = [jaccardList]
                else:
                    jaccardDict[controlKey].append(jaccardList)
        finalJaccardDict = {}
        for key, value in jaccardDict.items():
            finalJaccardList = []
            for tupleList in value:
                jaccardTotal = 0
                for tuple in tupleList:
                    tupleAddress = tuple[0]
                    jaccardTotal = jaccardTotal + tuple[1]
                jaccardAverage = jaccardTotal / len(tupleList)
                averageTuple = (tupleAddress, jaccardAverage)
                finalJaccardList.append(averageTuple)

            if key not in finalJaccardDict:
                finalJaccardDict[key] = finalJaccardList
            else:
                finalJaccardDict[key].append(finalJaccardList)


        return finalJaccardDict

    # Calculate the Jaccard distance for two OpCode list
    def calculateJaccard(self, controlOpcodeList, ecuOpcodeList):
        controlSet = set(controlOpcodeList)
        if ecuOpcodeList is None:
            return 0
        ecuSet = set(ecuOpcodeList)
        intersectionSet = controlSet & ecuSet
        unionSet = controlSet | ecuSet
        jaccardDistance = len(intersectionSet) / len(unionSet)
        return jaccardDistance

    # Update the list of Jaccard tuples
    def updatedJaccardTuples(self):
        oldTupleList = self.jaccardTuples

    # Print final Jaccard dictionary
    def printJaccardTuples(self):
            for key, value in self.jaccardTuples.items():
                for tuple in value:
                    print(key + ": " + str(tuple))

    # Find the sensor by comparing jaccard distances
    def findSensors(self):
        foundSensorDict = {}
        for key, value in self.jaccardTuples.items():
            counter = 0
            foundSensor = []
            for tuple in value:
                # Only for first iteration
                if counter == 0:
                    foundSensor.append(tuple)
                else:
                    currentMaxTuple = foundSensor[0]
                    tmp1 = currentMaxTuple[1]
                    tmp2 = tuple[1]
                    if tmp2 > tmp1:
                        foundSensor[0] = tuple
                    # NEED CHECK TO SEE IF JACCARD DISTANCES ARE THE SAME
                counter = counter + 1
            foundSensorDict[key] = foundSensor

        return foundSensorDict









