import mss
from PIL import Image
import numpy as np
import scipy.cluster
import time


class ScreenReactive:
    """
    A class that manages all actions related to Screen Reactive Script
    """
    def __init__(self, period=0):
        """
        An initializer method for class Screen Reactive.
        @params {float} the peroid for each screen detection
        @returns {void}
        """
        self.period = period
        print("\n[ScreenReactive] Mode Initialized. Delay : " + str(period))

    def return_rgb(self):
        """
        A method that gets screen data and returns most dominant color
        @params {void}
        @returns {list} a list that includes R, G, B value of dominant color
        """
        with mss.mss() as sct:
            # Get rid of the first, as it represents the "All in One" monitor:
            for num, monitor in enumerate(sct.monitors[1:], 1):
                # Get raw pixels from the screen
                sct_img = sct.grab(monitor)

                # Create the Image
                im = Image.frombytes("RGB", sct_img.size, sct_img.bgra, "raw", "BGRX")
            im = im.resize((150, 150))      # optional, to reduce time

            num_clusters = 1

            ar = np.asarray(im)
            shape = ar.shape
            ar = ar.reshape(np.product(shape[:2]), shape[2]).astype(float)

            codes, dist = scipy.cluster.vq.kmeans(ar, num_clusters)
            # Codes are stored as a matrix
            # 0 : R , 1 : G , 2 : B

            for i in range(len(codes)):
                lst = list()
                lst.append(int(codes[i][0]))
                lst.append(int(codes[i][1]))
                lst.append(int(codes[i][2]))
            time.sleep(self.period)
            return lst
