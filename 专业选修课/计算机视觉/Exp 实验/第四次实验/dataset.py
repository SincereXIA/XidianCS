import numpy as np
from scipy.misc import imread
from math import cos, sin, pi
import os

from util import flip_image


def load_dataset(name):
    if name == 'tentacle':
        return TentacleDataset()
    elif name in ('cat', 'frog', 'hippo', 'lizard', 'pig', 'scholar',
                  'turtle'):
        return PSDataset(name)
    elif name in ('Adirondack', 'Backpack', 'Bicycle1', 'Cable', 'Classroom1',
                  'Couch', 'Flowers', 'Jadeplant', 'Mask', 'Motorcycle',
                  'Piano', 'Pipes', 'Playroom', 'Playtable', 'Recycle',
                  'Shelves', 'Shopvac', 'Sticks', 'Storage', 'Sword1',
                  'Sword2', 'Umbrella', 'Vintage'):
        return MiddleburyDataset(name)
    else:
        raise Exception('{0} is not a valid dataset name'.format(name))


class TentacleDataset(object):

    def __init__(self):
        num_views = 9

        self.albedo_png = 'output/tentacle_albedo.png'
        self.normals_png = 'output/tentacle_normals.png'
        self.normals_npy = 'output/tentacle_normals.npy'
        self.ncc_png = 'output/tentacle_ncc.png'
        self.depth_npy = 'output/tentacle_depth.npy'
        self.mesh_ply = 'output/tentacle_mesh_{0}.ply'

        self.ncc_temp = 'temp/tentacle_ncc-%03d.png'
        self.ncc_gif = 'output/tentacle_ncc.gif'
        self.projected_temp = 'temp/tentacle_projected-%03d.png'
        self.projected_gif = 'output/tentacle_projected.gif'

        self.stereo_downscale_factor = 3

        self.mesh_downscale_factor = 0

        self.ncc_size = 5

        self.depth_weight = 1

        self.min_depth = 24
        self.max_depth = 45
        self.depth_layers = 128

        self.chessboard_dims = (5, 5)

        self.right = map(flip_image, [
            np.float32(imread('input/right/%04d.png' % (i + 1)))
            for i in xrange(num_views)])
        self.left = map(flip_image, [
            np.float32(imread('input/left/%04d.png' % (i + 1)))
            for i in xrange(num_views)])

        self.height = 1920
        self.width = 1080

        self.left_alpha = self.left[0][:, :, 3]
        self.right_alpha = self.right[0][:, :, 3]

        for image in self.right:
            assert image.shape == (self.height, self.width, 4)
            assert (self.right_alpha == image[:, :, 3]).all()

        for image in self.left:
            assert image.shape == (self.height, self.width, 4)
            assert (self.left_alpha == image[:, :, 3]).all()

        self.left = map(lambda x: x[:, :, :3], self.left)
        self.right = map(lambda x: x[:, :, :3], self.right)

        rotations = (
            (0, 0),
            (0, 15),
            (0, -15),
            (-15, 15),
            (-15, 15),
            (15, 15),
            (15, -15),
            (15, 0),
            (-15, 0),
        )

        assert len(rotations) == num_views

        lights = []
        for rotx, roty in rotations:
            direction = np.array(((0.0, ), (0.0, ), (1.0, )))

            radians_x = rotx / 180.0 * pi
            new_x = direction[1] * cos(radians_x) - \
                direction[2] * sin(radians_x)
            new_y = direction[1] * sin(radians_x) + \
                direction[2] * cos(radians_x)
            direction[1] = new_x
            direction[2] = new_y

            radians_y = roty / 180.0 * pi
            new_z = direction[2] * cos(radians_y) - \
                direction[0] * sin(radians_y)
            new_x = direction[2] * sin(radians_y) + \
                direction[0] * cos(radians_y)
            direction[2] = new_z
            direction[0] = new_x

            lights.append(direction)

        self.lights = np.hstack(lights)

        self.K_left = np.array((
                               (2100, 0, self.width / 2),
                               (0, 2100, self.height / 2),
                               (0, 0, 1)
                               ))
        self.K_right = np.array((
                                (2100, 0, self.width / 2),
                                (0, 2100, self.height / 2),
                                (0, 0, 1)
                                ))

        calib = np.load('input/calibration.npz')
        self.Rt_right = calib['Rt_right']
        self.Rt_left = calib['Rt_left']


class PSDataset(object):

    def __init__(self, name):
        num_views = 20

        self.albedo_png = 'output/{0}_albedo.png'.format(name)
        self.normals_png = 'output/{0}_normals.png'.format(name)
        self.normals_npy = 'output/{0}_normals.npy'.format(name)
        self.mesh_ply = 'output/' + name + '_mesh_{0}.ply'

        self.mesh_downscale_factor = 1

        self.right = [
            np.dstack(3 * [
                np.float32(
                    imread(
                        os.path.join('data', 'PSData', name, 'Objects',
                                     'Image_%02d.png' % (i + 1))
                    ))[:, :, np.newaxis]])
            for i in xrange(num_views)
        ]

        self.height = self.right[0].shape[0]
        self.width = self.right[0].shape[1]

        self.right_alpha = np.ones((self.height, self.width), dtype=np.float32)

        for image in self.right:
            assert image.shape == (self.height, self.width, 3)

        self.lights = np.loadtxt(
            os.path.join('data', 'PSData', name, 'light_directions.txt'))


class MiddleburyDataset(object):

    def __init__(self, name):
        num_views = 1

        self.ncc_png = 'output/{0}_ncc.png'.format(name)
        self.depth_npy = 'output/{0}_depth.npy'.format(name)

        self.ncc_temp = 'temp/{0}_ncc-%03d.png'.format(name)
        self.ncc_gif = 'output/{0}_ncc.gif'.format(name)
        self.projected_temp = 'temp/{0}_projected-%03d.png'.format(name)
        self.projected_gif = 'output/{0}_projected.gif'.format(name)
        self.mesh_ply = 'output/' + name + '_mesh_{0}.ply'

        self.stereo_downscale_factor = 4

        self.mesh_downscale_factor = 1

        self.ncc_size = 5

        base = os.path.join('data', '{0}-perfect'.format(name))

        self.right = [np.float32(imread(os.path.join(base, 'im0.png')))]
        self.left = [np.float32(imread(os.path.join(base, 'im1.png')))]

        calib = {}
        calib_filename = os.path.join(base, 'calib.txt')
        with open(calib_filename, 'r') as f:
            for line in f:
                name, value = line.strip().split('=')
                calib[name] = value

        baseline = float(calib['baseline'])
        doffs = float(calib['doffs'])
        vmin = float(calib['vmin'])
        vmax = float(calib['vmax'])

        self.K_left = self._parse_K(calib['cam1'])
        self.K_right = self._parse_K(calib['cam0'])

        self.min_depth = baseline * self.K_left[0, 0] / (vmax + doffs)
        self.max_depth = baseline * self.K_left[0, 0] / (vmin + doffs)
        self.depth_layers = 128

        self.height = int(calib['height'])
        self.width = int(calib['width'])

        self.Rt_left = np.zeros((3, 4), dtype=np.float32)
        self.Rt_left[:, :3] = np.identity(3)
        self.Rt_right = np.zeros((3, 4), dtype=np.float32)
        self.Rt_right[:, :3] = np.identity(3)
        self.Rt_right[0, 3] = float(calib['baseline'])

        self.left_alpha = np.ones((self.height, self.width), dtype=np.float32)
        self.right_alpha = np.ones((self.height, self.width), dtype=np.float32)

        for image in self.right:
            assert image.shape == (self.height, self.width, 3)

        for image in self.left:
            assert image.shape == (self.height, self.width, 3)

    def _parse_K(self, string):
        assert string[0] == '['
        assert string[-1] == ']'
        string = string[1:-1]
        lines = string.split(';')
        assert len(lines) == 3
        lines = map(lambda x: map(float, x.strip().split()), lines)
        return np.array(lines)
