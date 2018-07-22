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

    def set_jaccard_index(self, value):
        """
        Setter for features Jaccard Index, defaulted to 0.0 in constructor
        :param value: calculated Jaccard Index to set
        """
        self.jaccard_index = value

    def __str__(self):
        """
        :return: formatted string for instance variables
        """
        return "Jaccard Index: " + self.jaccard_index
