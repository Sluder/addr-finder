class FeatureSet:
    """
    self.features: array of Feature objects
    self.jaccard_index: average Jaccard Index of all self.features
    """

    def __init__(self, feature):
        """
        FeatureSet constructor
        :param features: list of Feature objects
        """
        self.features = [feature]
        self.jaccard_index = 0.0

    def set_jaccard_index(self, value):
        """
        Setter for features Jaccard Index, defaulted to 0.0 in constructor
        :param value: calculated Jaccard Index to set
        """
        self.jaccard_index = value
