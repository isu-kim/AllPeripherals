import time
import Bridge


class RainbowAll:
    """
    This class is for doing all the jobs related to rainbow all.
    """
    def __init__(self, BridgeObj, speed=100):
        """
        An intializer method for class RainbowAll
        @params {Bridge} a Bridge object for server connection
        @params {int} the duration of each led transitions. Nanosec
        @returns {void}
        """
        self.speed = speed
        self.BridgeObj = BridgeObj
        print("\n[RainbowAll] Mode Initialized. Speed : " + str(speed))
        
    def rainbow_all(self):
        """
        A method for setting all the leds into one color and rainbow shfts.
        @params {void}
        @returns {void}
        """
        self.BridgeObj.send_speed(self.speed)


