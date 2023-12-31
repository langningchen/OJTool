from os import path
import numpy as np
import tensorflow as tf
from keras.models import load_model
from PIL import Image

if path.sep == "\\":
    TempFolder = "C:\\Windows\\Temp\\"
else:
    TempFolder = "/tmp/"

if __name__ == "__main__":
    print("".join(map(chr,
                      map(int, tf.math.argmax(
                          load_model(
                              path.join(path.dirname(__file__),
                                        "LuoguCaptchaModule")
                          ).predict(
                              np.array([
                                  np.array(
                                      Image.open(TempFolder + "Captcha.jpeg")
                                  ) / 255.0
                              ]),
                              verbose=0),
                          axis=-1)[0])
                      )
                  ),
          file=open(TempFolder + "Captcha.txt", mode="w"))
