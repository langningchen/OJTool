from glob import glob

import matplotlib
import matplotlib.pyplot as plt
import numpy as np  # linear algebra
import pandas as pd  # data processing, CSV file I/O (e.g. pd.read_csv)
import tensorflow as tf
from keras import layers, models
from keras.utils import to_categorical

matplotlib.use("QtAgg")

CharSize = 128
CharsPerLabel = 4  # num_of_chars_per_image
EPOCHS = 8

# create a pandas data frame of images and labels
TrainFiles = glob("Data/Data_*.pkl")

ImageIDs = np.random.permutation(len(TrainFiles))
TotalSize = int(len(TrainFiles) * 0.8)
TrainImageIDs = ImageIDs[:TotalSize]
TestImageIDs = ImageIDs[TotalSize:]

# split train_idx further into training and validation set
TotalSize = int(TotalSize * 0.8)
TrainImageIDs, ValidationImageIDs = TrainImageIDs[:TotalSize], TrainImageIDs[TotalSize:]

print(
    "Train: %d, Validation: %d, Test: %d"
    % (len(TrainImageIDs), len(ValidationImageIDs), len(TestImageIDs))
)

def GetDataGenerator(Files, indices, repeat=1):
    for _ in range(repeat):
        for i in indices:
            DataFrame = pd.read_pickle(Files[i])
            Images = np.array([Image for Image in DataFrame["Image"]]) / 255.0
            Labels = np.array(
                [
                    [
                        np.array(to_categorical(ord(LabelChar), CharSize))
                        for LabelChar in Label.lower()
                    ]
                    for Label in DataFrame["Label"]
                ]
            )
            yield Images, Labels

InputLayer = tf.keras.Input(shape=(35, 90, 3), name="InputLayer")
FirstConvolution = layers.Conv2D(32, 3, activation="relu", name="FirstConvolution")(InputLayer)
FirstPooling = layers.MaxPooling2D((2, 2), name="FirstPooling")(FirstConvolution)
SecondConvolution = layers.Conv2D(64, 3, activation="relu", name="SecondConvolution")(FirstPooling)
SecondPooling = layers.MaxPooling2D((2, 2), name="SecondPooling")(SecondConvolution)
ThirdConvolution = layers.Conv2D(64, 3, activation="relu", name="ThirdConvolution")(SecondPooling)
ThirdPooling = layers.MaxPooling2D((2, 2), name="ThirdPooling")(ThirdConvolution)
Flatten = layers.Flatten(name="Flatten")(ThirdPooling)
Dense = layers.Dense(1024, activation="relu", name="Dense")(Flatten)
Output = layers.Dense(CharsPerLabel * CharSize, activation="softmax", name="Output")(Dense)
Reshape = layers.Reshape((CharsPerLabel, CharSize), name="Reshape")(Output)

Model = models.Model(inputs=InputLayer, outputs=Reshape, name="LuoguCaptcha")
Model.compile(
    optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"]
)
Model.summary()

TrainingHistory = Model.fit(
    GetDataGenerator(TrainFiles, TrainImageIDs, EPOCHS),
    steps_per_epoch=len(TrainImageIDs),
    epochs=EPOCHS,
    validation_data=GetDataGenerator(TrainFiles, ValidationImageIDs, EPOCHS),
    validation_steps=len(ValidationImageIDs),
    callbacks=[
        tf.keras.callbacks.TensorBoard(histogram_freq=1, log_dir="Logs"),   
    ],
)

_, Axes = plt.subplots(1, 2, figsize=(15, 5))

Axes[0].plot(TrainingHistory.history["accuracy"], label="Training accuracy")
Axes[0].plot(TrainingHistory.history["val_accuracy"], label="Validation accuracy")
Axes[0].set_xlabel("Epochs")
Axes[0].legend()

Axes[1].plot(TrainingHistory.history["loss"], label="Training loss")
Axes[1].plot(TrainingHistory.history["val_loss"], label="Validation loss")
Axes[1].set_xlabel("Epochs")
Axes[1].legend()

print(pd.DataFrame(TrainingHistory.history))
plt.savefig("TrainingHistory.png")
plt.show()

# evaluate loss and accuracy in test dataset
TestDataGenerator = GetDataGenerator(TrainFiles, TestImageIDs)
Loss, Accuracy = Model.evaluate(TestDataGenerator, steps=len(TestImageIDs))
print("Test loss: %.4f, accuracy: %.2f%%" % (Loss, Accuracy * 100))

Model.save("LuoguCaptcha.keras")
