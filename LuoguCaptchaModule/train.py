"""
captcha-tensorflow
Copyright (c) 2017 Jackon Yang
https://github.com/JackonYang/captcha-tensorflow/blob/master/captcha-solver-tf2-4digits-AlexNet-98.8.ipynb
"""

from glob import glob
from os import path
from datetime import datetime

import matplotlib.pyplot as plt
import numpy as np  # linear algebra
import pandas as pd  # data processing, CSV file I/O (e.g. pd.read_csv)
import tensorflow as tf
from keras import layers, models
from keras.utils.np_utils import to_categorical

# from PIL import Image


DATA_DIR = "data"
LOG_DIR = "logs/fit/" + datetime.now().strftime("%Y%m%d-%H%M%S")
H, W, C = 35, 90, 3  # height, width, 3 (RGB channels)
N_LABELS = 128
D = 4  # num_of_chars_per_image
EPOCHS = 4


# create a pandas data frame of images and labels
files = glob(path.join(DATA_DIR, "data-*.pkl"))


p = np.random.permutation(len(files))
train_up_to = int(len(files) * 0.9375)
train_idx = p[:train_up_to]
test_idx = p[train_up_to:]

# split train_idx further into training and validation set
train_up_to = int(train_up_to * 0.9375)
train_idx, valid_idx = train_idx[:train_up_to], train_idx[train_up_to:]

print(
    "train count: %s, valid count: %s, test count: %s"
    % (len(train_idx), len(valid_idx), len(test_idx))
)


def get_data_generator(files, indices, repeat=1):
    for _ in range(repeat):
        for i in indices:
            df = pd.read_pickle(files[i])
            images = np.array([a for a in df["image"]]) / 255.0
            labels = np.array(
                [
                    [
                        np.array(to_categorical(ord(i), N_LABELS))
                        for i in lable.lower()
                    ]
                    for lable in df["label"]
                ]
            )
            # print(images.shape, labels.shape)
            yield images, labels


input_layer = tf.keras.Input(shape=(H, W, C))
x = layers.Conv2D(32, 3, activation="relu")(input_layer)
x = layers.MaxPooling2D((2, 2))(x)
x = layers.Conv2D(64, 3, activation="relu")(x)
x = layers.MaxPooling2D((2, 2))(x)
x = layers.Conv2D(64, 3, activation="relu")(x)
x = layers.MaxPooling2D((2, 2))(x)

x = layers.Flatten()(x)
x = layers.Dense(1024, activation="relu")(x)
# x = layers.Dropout(0.5)(x)

x = layers.Dense(D * N_LABELS, activation="softmax")(x)
x = layers.Reshape((D, N_LABELS))(x)

model = models.Model(inputs=input_layer, outputs=x)

model.compile(
    optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"]
)
model.summary()


history = model.fit(
    get_data_generator(files, train_idx, EPOCHS),
    steps_per_epoch=len(train_idx),
    epochs=EPOCHS,
    validation_data=get_data_generator(files, valid_idx, EPOCHS),
    validation_steps=len(valid_idx),
    callbacks=[
        tf.keras.callbacks.TensorBoard(log_dir=LOG_DIR, histogram_freq=1)
    ],
)


def plot_train_history(history):
    fig, axes = plt.subplots(1, 2, figsize=(20, 5))

    axes[0].plot(history.history["accuracy"], label="Train accuracy")
    axes[0].plot(history.history["val_accuracy"], label="Val accuracy")
    axes[0].set_xlabel("Epochs")
    axes[0].legend()

    axes[1].plot(history.history["loss"], label="Training loss")
    axes[1].plot(history.history["val_loss"], label="Validation loss")
    axes[1].set_xlabel("Epochs")
    axes[1].legend()


plot_train_history(history)
plt.show()


# evaluate loss and accuracy in test dataset
test_gen = get_data_generator(files, test_idx)
print(
    dict(
        zip(
            model.metrics_names,
            model.evaluate(test_gen, steps=len(test_idx)),
        )
    )
)


model.save("saved_model/luogu_captcha")
