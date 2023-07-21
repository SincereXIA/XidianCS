import numpy as np
import math
import sys

from scipy.misc import imsave

from dataset import load_dataset

from util import compute_photometric_stereo, rerendering_error

assert len(sys.argv) > 1
data = load_dataset(sys.argv[1])

albedo, normals = compute_photometric_stereo(data.lights, data.right)

avg_rmse = rerendering_error(data.lights, data.right, albedo, normals)

print 'Average RMSE of rerendered image is {0}'.format(avg_rmse)

print 'Saving albedo to {0}'.format(data.albedo_png)
imsave(data.albedo_png, np.uint8(np.clip(albedo, 0, 255)))
print 'Saving normals visualization to {0}'.format(data.normals_png)
imsave(data.normals_png, normals)
print 'Saving normals to {0}'.format(data.normals_npy)
np.save(data.normals_npy, normals)
