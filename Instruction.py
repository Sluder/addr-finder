import Global

class Instruction:
    """
    text: original instruction text (Ex: lda al 0x1070)
    mnemonic: operation done in instruction
    gram: mnemonic.operands with operand type (Ex: lda.reg.mem)
    """

    def __init__(self, file_line):
        """
        Instruction constructor
        :param file_line: array of split instruction line
        """
        self.text = ' '.join(file_line)
        self.mnemonic = file_line[0]
        self.gram = self.mnemonic

        for i in range(len(file_line[1:])):
            operand = file_line[i + 1]

            if operand == "+":
                self.gram += "+"
            else:
                if file_line[i] == "+":
                    self.gram += Global.get_operand_type(operand)
                else:
                    self.gram += "." + Global.get_operand_type(operand)

    def __str__(self):
        """
        :return: formatted string
        """
        return ("mnemonic: " + self.mnemonic + "\n" +
                "gram: " + self.gram)
