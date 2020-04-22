import time
import Bridge


class RainbowAll:
    """
    This class is for doing all the jobs related to rainbow all.
    """
    def __init__(self, BridgeObj, speed=0.005):
        """
        An intializer method for class RainbowAll
        @params {Bridge} a Bridge object for server connection
        @params {float} the duration of each led transitions.
        @returns {void}
        """
        self.speed = speed
        self.BridgeObj = BridgeObj
        print("[RainbowAll] Mode Initialized. Speed : " + str(speed))

    def rainbow_all(self):
        """
        A method for setting all the leds into one color and rainbow shfts.
        @params {void}
        @returns {void}
        """
        while True:
            for g in range(0, 255, 1):
                self.BridgeObj.send_rgb_value(255, g, 0)
                time.sleep(self.speed)

            for r in range(255, 0, -1):
                self.BridgeObj.send_rgb_value(r, 255, 0)
                time.sleep(self.speed)

            for b in range(0, 255, 1):
                self.BridgeObj.send_rgb_value(0, 255, b)
                time.sleep(self.speed)

            for g in range(255, 0, -1):
                self.BridgeObj.send_rgb_value(0, g, 255)
                time.sleep(self.speed)

            for r in range(0, 255, 1):
                self.BridgeObj.send_rgb_value(r, 0, 255)
                time.sleep(self.speed)

            for b in range(255, 0, -1):
                self.BridgeObj.send_rgb_value(255, 0, b)
                time.sleep(self.speed)

