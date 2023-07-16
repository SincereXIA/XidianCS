from scipy.misc import imsave
import cv2
import numpy as np
import sys
import time

from util import preprocess_ncc, pyrdown, get_depths, \
    unproject_corners, compute_ncc, project

from dataset import load_dataset

from gifwriter import GifWriter

assert len(sys.argv) > 1
data = load_dataset(sys.argv[1])

K_right = data.K_right
K_left = data.K_left
Rt_right = data.Rt_right
Rt_left = data.Rt_left

ncc_size = data.ncc_size
width = data.width
height = data.height

ncc_gif_writer = GifWriter(data.ncc_temp, data.ncc_gif)
projected_gif_writer = GifWriter(data.projected_temp, data.projected_gif)

"""
Images are pretty large, so we're going to reduce their size
in each dimension.
"""
right = data.right[0]
left = data.left[0]
for i in xrange(data.stereo_downscale_factor):
    right = pyrdown(right)
    left = pyrdown(left)
    height, width, _ = right.shape
    K_left[:2, :] /= 2
    K_right[:2, :] /= 2

"""
We'll give you the depth labels for this problem.
"""
depths = get_depths(data)

tic = time.time()

"""
The planes will be swept fronto-parallel to the right camera, so no
reprojection needs to be done for this image.  Simply compute the normalized
patches across the entire image.
"""
right_normalized = preprocess_ncc(right[:, :, :3], ncc_size)

"""
We'll sweep a series of planes that are fronto-parallel to the right camera.
The image from the left camera is to be projected onto each of these planes,
normalized, and then compared to the normalized right image.
"""
volume = []
for pos, depth in enumerate(depths):
    """
    Unproject the pixel coordinates from the right camera onto the virtual
    plane.
    """
    points = unproject_corners(K_right, width, height, depth, Rt_right)

    """
    Project those points onto the two cameras to generate correspondences.
    """
    points_left = project(K_left, Rt_left, points)
    points_right = project(K_right, Rt_right, points)

    points_left = np.float32(points_left.reshape(-1, 2))
    points_right = np.float32(points_right.reshape(-1, 2))

    H, mask = cv2.findHomography(points_left, points_right)
    assert (mask == 1).all()

    projected_left = cv2.warpPerspective(left, H, (width, height))

    """
    Normalize this projected left image.
    """
    left_normalized = preprocess_ncc(projected_left, ncc_size)

    """
    Compute the NCC score between the right and left images.
    """
    ncc = compute_ncc(right_normalized, left_normalized)

    volume.append(ncc)

    projected_gif_writer.append(np.uint8(projected_left))
    ncc_gif_writer.append(np.uint8(255 * np.clip(ncc / 2 + 0.5, 0, 1)))

    sys.stdout.write('Progress: {0}\r'.format(int(100 * pos / len(depths))))
    sys.stdout.flush()
print ''

toc = time.time()

print 'Plane sweep took {0} seconds'.format(toc - tic)

ncc_gif_writer.close()
projected_gif_writer.close()

"""
All of these separate NCC layers get stacked together into a volume.
"""
volume = np.dstack(volume)

"""
We're going to use the simplest algorithm to select a depth layer per pixel --
the argmax across depth labels.
"""
solution = volume.argmax(axis=2)

print 'Saving NCC to {0}'.format(data.ncc_png)
imsave(data.ncc_png, solution * 2)

"""
Remap the label IDs back to their associated depth values.
"""
solution = depths[solution]

print 'Saving depth to {0}'.format(data.depth_npy)
np.save(data.depth_npy, solution)
