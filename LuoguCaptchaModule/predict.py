"""
captcha-tensorflow
Copyright (c) 2017 Jackon Yang
https://github.com/JackonYang/captcha-tensorflow/blob/master/captcha-solver-model-restore.ipynb
"""

from os import path

# import matplotlib.pyplot as plt
import numpy as np  # linear algebra
import tensorflow as tf
from keras.models import load_model
from PIL import Image

MODEL_PATH = "saved_model/luogu_captcha"


model = load_model(path.join(path.dirname(__file__), MODEL_PATH))


def predict(image):
    im = Image.open(image)
    # im = im.resize((H, W))
    ima = np.array(im) / 255.0

    prediction = model.predict(np.array([ima]), verbose=0)
    prediction = tf.math.argmax(prediction, axis=-1)

    return "".join(map(chr, map(int, prediction[0])))
    # plt.imshow(ima)


if __name__ == "__main__":
    # Check its architecture
    # model.summary()

    print(predict("./captcha.jpg"))
