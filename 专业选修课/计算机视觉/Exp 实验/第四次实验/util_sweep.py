import time
from math import floor
import numpy as np
import cv2

def pyrdown_impl(image):
    kernel = np.array(((1.0, 4.0, 6.0, 4.0, 1.0), ))
    kernel /= kernel.sum()
    image = cv2.filter2D(image, -1, kernel.T,
                         borderType=cv2.BORDER_REFLECT_101)
    image = cv2.filter2D(image, -1, kernel, borderType=cv2.BORDER_REFLECT_101)
    return image[::2, ::2]


def pyrup_impl(image):
    upscaled_shape = list(image.shape)
    upscaled_shape[0] *= 2
    upscaled_shape[1] *= 2

    kernel = np.array(((1.0, 4.0, 6.0, 4.0, 1.0), ))
    kernel /= kernel.sum()
    kernel *= 2
    upscaled_image = np.zeros(upscaled_shape, dtype=np.float32)
    upscaled_image[::2, ::2] = image
    upscaled_image = cv2.filter2D(
        upscaled_image, -1, kernel.T, borderType=cv2.BORDER_REFLECT_101)
    upscaled_image = cv2.filter2D(
        upscaled_image, -1, kernel, borderType=cv2.BORDER_REFLECT_101)
    return upscaled_image

def unproject_corners_impl(K, width, height, depth, Rt):
    invK = np.linalg.inv(K)

    points = np.array((
        (0, 0, 1),
        (width, 0, 1),
        (0, height, 1),
        (width, height, 1),
    ), dtype=np.float32).reshape(2, 2, 3)

    points = np.tensordot(points, invK.T, axes=1)
    points *= depth
    points = np.tensordot(points, Rt[:3, :3], axes=1)
    points += -Rt[:3, :3].T.dot(Rt[:3, 3])
    return points