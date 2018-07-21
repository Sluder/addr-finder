"""
File for global variables & functions
"""

# Contains configuration for sensors
config = {}

def format_line(file_line):
    """
    :param file_line: string to format
    :return: split string with removed end spaces/tabs
    """
    return [i.replace(",", "") for i in file_line.strip().split()]

def get_operand_type(operand):
    """
    Gets the operand type for an instruction
    :param operand: operand string (Ex: 0x102f, al)
    :return: type of operand (Ex. 0x102f => mem)
    """
    if operand.startswith("#0"):
        return "con"
    elif operand.startswith("0x"):
        return "mem"
    return "reg"
