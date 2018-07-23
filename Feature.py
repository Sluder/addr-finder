class Feature:
    """
    self.jaccard_index: Jaccard index value, used for similarity checking
    self.instructions: array of Instruction objects that complete a feature
    """

    def __init__(self, instructions):
        """
        Feature constructor
        :param instructions: array of Instruction objects
        """
        self.jaccard_index = 0.0
        self.instructions = instructions

    def get_instruction_set(self):
        """
        Formats a list containing self.instructions grams
        :return: list with just feature instruction grams
        """
        gram_list = []

        for instruction in self.instructions:
            gram_list.append(instruction.gram)

        return gram_list

    def set_jaccard_index(self, value):
        """
        Setter for features Jaccard Index, defaulted to 0.0 in constructor
        :param value: calculated Jaccard Index to set
        """
        self.jaccard_index = value

