import numpy as np  # linear algebra
import tensorflow as tf
from keras.models import load_model
from PIL import Image

if __name__ == "__main__":
    Model = load_model("LuoguCaptcha.keras")
    Model.summary()

    Image = Image.open("./CaptchaTest.jpg")
    ImageArray = np.array(Image) / 255.0

    Prediction = Model.predict(np.array([ImageArray]))
    Prediction = tf.math.argmax(Prediction, axis=-1)

    print("".join(map(chr, map(int, Prediction[0]))))
    # print(Prediction[0])

