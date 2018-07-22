import Global

class Instruction:
    """
    self.text: original instruction text (Ex: lda al 0x1070)
    self.mnemonic: operation done in instruction
    self.operands: array of instruction operands
    self.gram: mnemonic.operands with operand type (Ex: lda.reg.mem)
    """

    def __init__(self, file_line):
        """
        Instruction constructor
        :param file_line: array of split instruction line
        """
        self.text = ' '.join(file_line)
        self.mnemonic = file_line[0]
        self.operands = file_line[1:]
        self.gram = self.mnemonic

        for i in range(len(file_line[1:])):
            operand = file_line[i + 1]

            # Handle operand arithmetic
            if operand == "+":
                self.gram += "+"
            else:
                if file_line[i] == "+":
                    self.gram += Global.get_operand_type(operand)
                else:
                    self.gram += "." + Global.get_operand_type(operand)

    def __str__(self):
        """
        :return: formatted string with all instance variables
        """
        return ("Text :     " + self.text + "\n" +
                "Mnemonic : " + self.mnemonic + "\n" +
                "Gram :     " + self.gram + "\n")
