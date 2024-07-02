from os import path
import numpy as np  # linear algebra
import tensorflow as tf
from keras.models import load_model
from PIL import Image

if __name__ == "__main__":
    Model = load_model(
        path.join(path.dirname(__file__), "LuoguCaptchaModule", "LuoguCaptcha.keras")
    )

    Image = Image.open("/OJTool/Captcha.jpg")
    ImageArray = np.array(Image) / 255.0

    Prediction = Model.predict(np.array([ImageArray]), verbose=0)
    Prediction = tf.math.argmax(Prediction, axis=-1)

    print(
        "".join(map(chr, map(int, Prediction[0]))),
        file=open("/OJTool/Captcha.txt", mode="w"),
    )
