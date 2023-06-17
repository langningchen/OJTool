import re
import subprocess
import threading
from io import BytesIO
from math import ceil
from os import listdir, path
from sys import argv

import pandas as pd
from numpy import array
from PIL import Image

DATA_DIR = "data"


def run(num, wid, ims):
    p = subprocess.Popen(
        "php gen.php {}".format(num),
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        shell=True,
    )
    for i in range(num):
        if i % 1024 == 0:
            print(f"Worker{wid}: Generated{i}")
        s = p.stdout.read(2)
        ph = str(p.stdout.read(4), encoding="utf-8")
        l = s[0] * 256 + s[1]
        d = array(Image.open(BytesIO(p.stdout.read(l))))
        ims.append((ph, d))


def generate(num, workers, batch_size):
    each = num // workers
    ims = [[] for i in range(workers)]
    tasks = []
    for i in range(workers - 1):
        tasks.append(threading.Thread(target=run, args=(each, i, ims[i])))
    tasks.append(
        threading.Thread(
            target=run, args=(num - each * (workers - 1), workers - 1, ims[-1])
        )
    )

    for thread in tasks:
        thread.start()
    for thread in tasks:
        thread.join()

    df = pd.DataFrame([j for i in ims for j in i], columns=["label", "image"])
    offset = max(
        [
            int((re.match(r"data-([0-9]+)\.pkl", f) or [None, -1])[1])
            for f in listdir(DATA_DIR)
        ]
        or [-1]
    )
    for i in range(ceil(len(df) / batch_size)):
        df.iloc[i * batch_size : (i + 1) * batch_size].to_pickle(
            path.join(DATA_DIR, f"data-{i + offset + 1}.pkl")
        )


if __name__ == "__main__":
    generate(*map(int, argv[1:]))
