"""
OJTool: Get problem and submit code for OJ just from your CLI!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

from os import path
import numpy as np
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
