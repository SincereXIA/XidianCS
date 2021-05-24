import numpy as np
import sys
import math
from scipy.misc import imsave, imread
from scipy.sparse.linalg import lsqr
import cv2
import time
from util import pyrup, save_mesh, form_poisson_equation, pyrdown

from dataset import load_dataset

assert len(sys.argv) > 2
data = load_dataset(sys.argv[1])
mode = sys.argv[2]
assert mode in ('normals', 'depth', 'both')

alpha = data.right_alpha
depth_weight = None
depth = None
K_right = None
normals = None
albedo = None

tic = time.time()
if mode in ('normals', 'both'):
    albedo = imread(data.albedo_png)
    normals = np.load(data.normals_npy)

if mode in ('depth', 'both'):
    depth = np.load(data.depth_npy)
    K_right = data.K_right

    depth = cv2.medianBlur(depth, 5)
    depth = cv2.medianBlur(depth, 5)

    if data.mesh_downscale_factor > data.stereo_downscale_factor:
        for i in range(data.mesh_downscale_factor -
                        data.stereo_downscale_factor):
            depth = pyrdown(depth)
    elif data.stereo_downscale_factor > data.mesh_downscale_factor:
        for i in range(data.stereo_downscale_factor -
                        data.mesh_downscale_factor):
            depth = pyrup(depth)

    for i in range(data.mesh_downscale_factor):
        K_right[:2, :] /= 2

if mode == 'both':
    depth_weight = data.depth_weight

if mode == 'depth':
    albedo = data.right[0]

if alpha is not None:
    for i in range(data.mesh_downscale_factor):
        alpha = pyrdown(alpha)

if normals is not None:
    for i in range(data.mesh_downscale_factor):
        normals = pyrdown(normals)

for i in range(data.mesh_downscale_factor):
    albedo = pyrdown(albedo)
toc = time.time()

heights = []
widths = []
if depth is not None:
    height, width = depth.shape
    heights.append(height)
    widths.append(width)
if alpha is not None:
    height, width = alpha.shape
    heights.append(height)
    widths.append(width)
if normals is not None:
    height, width, _ = normals.shape
    heights.append(height)
    widths.append(width)

width = min(widths)
height = min(heights)

if mode in ('depth', 'both'):
    assert max(widths) - width <= data.stereo_downscale_factor
    assert max(heights) - height <= data.stereo_downscale_factor

if depth is not None:
    depth = depth[:height, :width]
if alpha is not None:
    alpha = alpha[:height, :width]
if normals is not None:
    normals = normals[:height, :width, :]

print( 'Initialized data in {0} seconds'.format(toc - tic))

tic = time.time()
A, b = form_poisson_equation(
    height, width, alpha, normals, depth_weight, depth)
toc = time.time()

print( 'Set up linear system in {0} seconds'.format(toc - tic))

tic = time.time()
print ('Solving...')
solution = lsqr(A, b)
x = solution[0]
depth = x.reshape(height, width)
toc = time.time()
print ('Solve complete in {0} seconds'.format(toc - tic))

print ('Save mesh to {0}'.format(data.mesh_ply.format(mode)))
save_mesh(K_right, width, height, albedo, normals,
          depth, alpha, data.mesh_ply.format(mode))
print ('done :)')
