import numpy as np
import math
from itertools import izip
from scipy.misc import imsave

images = [np.zeros((256, 256, 3), dtype=np.float32) for _ in xrange(3)]

lights = 2 * (np.random.random((3, 3)) - 0.5)
lights[2, :] += 5
lights[2, :] = np.abs(lights[2, :])
lights /= np.linalg.norm(lights, axis=0)[np.newaxis, :]
print lights

for i in xrange(256):
    for j in xrange(256):
        x = (j - 128.0) / 128.0
        y = -(i - 128.0) / 128.0
        if x**2 + y**2 > 1:
            continue

        z = math.sqrt(1 - x**2 - y**2)

        direction = np.array((x, y, z), dtype=np.float32).reshape((3, 1))

        dots = (lights * direction).sum(axis=0).flatten()

        for image, dot in izip(images, dots):
            image[i, j] = max(0, dot)

for i, image in enumerate(images):
    imsave('sphere%02d.png' % i, image)

np.save('sphere_lights.npy', lights)
