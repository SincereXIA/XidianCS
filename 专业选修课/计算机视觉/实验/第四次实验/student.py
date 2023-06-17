# Please place imports here.
# BEGIN IMPORTS
import time
from math import floor
import numpy as np
import cv2
from scipy.sparse import csr_matrix
# import util_sweep
# END IMPORTS


def compute_photometric_stereo_impl(lights, images):
    """
    Given a set of images taken from the same viewpoint and a corresponding set
    of directions for light sources, this function computes the albedo and
    normal map of a Lambertian scene.

    If the computed albedo for a pixel has an L2 norm less than 1e-7, then set
    the albedo to black and set the normal to the 0 vector.

    Normals should be unit vectors.

    Input:
        lights -- N x 3 array.  Rows are normalized and are to be interpreted
                  as lighting directions.
        images -- list of N images.  Each image is of the same scene from the
                  same viewpoint, but under the lighting condition specified in
                  lights.
    Output:
        albedo -- float32 height x width x 3 image with dimensions matching the
                  input images.
        normals -- float32 height x width x 3 image with dimensions matching
                   the input images.
"""

    L = lights  # N行3列，每行代表光的方向向量
    L_T = L.T  # 转置一下
    albedo = np.zeros((images[0].shape[0], images[0].shape[1], images[0].shape[2]), dtype=np.float32)
    normals = np.zeros((images[0].shape[0], images[0].shape[1], 3), dtype=np.float32)  # 法向量对每张图、每个通道都一样
    term1 = np.linalg.inv(L_T.dot(L))
    for channel in range(images[0].shape[2]):  # 哪个通道
        for row in range(images[0].shape[0]):
            for col in range(images[0].shape[1]):
                I = [(images[i][row][col][channel]).T for i in range(len(images))]
                term2 = L_T.dot(I)  # LT*I
                G = term1.dot(term2)  # G=(LT*L)^-1*(LT*I)
                k = np.round(np.linalg.norm(G), 5)  # k等于G的模长
                if k < 1e-7:
                    k = 0
                else:
                    normals[row][col] += G / k
                albedo[row][col][channel] = k
    normals /= images[0].shape[2]
    return albedo, normals

def pyrdown_impl(image):
    """
    Prefilters an image with a gaussian kernel and then downsamples the result
    by a factor of 2.

    The following 1D convolution kernel should be used in both the x and y
    directions.
    K = 1/16 [ 1 4 6 4 1 ]

    Functions such as cv2.GaussianBlur and
    scipy.ndimage.filters.gaussian_filter are prohibited.  You must implement
    the separable kernel.  However, you may use functions such as cv2.filter2D
    or scipy.ndimage.filters.correlate to do the actual
    correlation / convolution.

    Filtering should mirror the input image across the border.
    For scipy this is mode = mirror.
    For cv2 this is mode = BORDER_REFLECT_101.

    Downsampling should take the even-numbered coordinates with coordinates
    starting at 0.

    Input:
        image -- height x width [x channels] image of type float32.
    Output:
        down -- ceil(height/2) x ceil(width/2) [x channels] image of type
                float32.
    """
    # Creating kernel, K = 1/16 [ 1 4 6 4 1 ]
    gauss_filter = np.zeros((1, 5))
    gauss_filter[0, 0] = 1
    gauss_filter[0, 1] = 4
    gauss_filter[0, 2] = 6
    gauss_filter[0, 3] = 4
    gauss_filter[0, 4] = 1

    Ky = 1.0/16 * gauss_filter
    Kx = np.transpose(Ky)

    #Filter image in x and y directions using gaussian kernel
    filtered_img = cv2.filter2D(image, -1, Ky, borderType=cv2.BORDER_REFLECT_101)
    filtered_img = cv2.filter2D(filtered_img, -1, Kx, borderType=cv2.BORDER_REFLECT_101)

    #Downsampling filtered image
    down = filtered_img[::2, ::2]

    return down


def pyrup_impl(image):
    """
    Upsamples an image by a factor of 2 and then uses a gaussian kernel as a
    reconstruction filter.

    The following 1D convolution kernel should be used in both the x and y
    directions.
    K = 1/8 [ 1 4 6 4 1 ]
    Note: 1/8 is not a mistake.  The additional factor of 4 (applying this 1D
    kernel twice) scales the solution according to the 2x2 upsampling factor.

    Filtering should mirror the input image across the border.
    For scipy this is mode = mirror.
    For cv2 this is mode = BORDER_REFLECT_101.

    Upsampling should produce samples at even-numbered coordinates with
    coordinates starting at 0.

    Input:
        image -- height x width [x channels] image of type float32.
    Output:
        up -- 2 height x 2 width [x channels] image of type float32.
    """
    #Upsampling given image
    up_height = image.shape[0] * 2
    up_width = image.shape[1] * 2
    if (len(image.shape) == 3):
        up_channels = image.shape[2]
        unfiltered_up = np.zeros((up_height, up_width, up_channels))
    else:
        unfiltered_up = np.zeros((up_height, up_width))

    unfiltered_up[::2, ::2] = image

    #Creating gaussian kernel, K = 1/8 [ 1 4 6 4 1 ]
    gauss_filter = np.zeros((1, 5))
    gauss_filter[0, 0] = 1
    gauss_filter[0, 1] = 4
    gauss_filter[0, 2] = 6
    gauss_filter[0, 3] = 4
    gauss_filter[0, 4] = 1

    Ky = 1.0/8 * gauss_filter
    Kx = np.transpose(Ky)

    #Filter image in x and y directions using gaussian kernel
    up = cv2.filter2D(unfiltered_up, -1, Ky, borderType=cv2.BORDER_REFLECT_101)
    up = cv2.filter2D(up, -1, Kx, borderType=cv2.BORDER_REFLECT_101)

    return up


def unproject_corners_impl(K, width, height, depth, Rt):
    """
    Undo camera projection given a calibrated camera and the depth for each
    corner of an image.

    The output points array is a 2x2x3 array arranged for these image
    coordinates in this order:

     (0, 0)      |  (width, 0)
    -------------+------------------
     (0, height) |  (width, height)

    Each of these contains the 3 vector for the corner's corresponding
    point in 3D.

    Tutorial:
      Say you would like to unproject the pixel at coordinate (x, y)
      onto a plane at depth z with camera intrinsics K and camera
      extrinsics Rt.

      (1) Convert the coordinates from homogeneous image space pixel
          coordinates (2D) to a local camera direction (3D):
          (x', y', 1) = K^-1 * (x, y, 1)
          the camera center.  Multiply it by z to get the point at depth z
          from the camera center.
          (z * x', z * y', z) = z * (x', y', 1)
      (3) Use the inverse of the extrinsics matrix, Rt, to move this point
          from the local camera coordinate system to a world space
          coordinate.
          Note:
            | R t |^-1 = | R' -R't |
            | 0 1 |      | 0   1   |

          p = R' * (z * x', z * y', z, 1) - R't

    Input:
        K -- camera intrinsics calibration matrix
        width -- camera width
        height -- camera height
        depth -- depth of plane with respect to camera
        Rt -- 3 x 4 camera extrinsics calibration matrix
    Output:
        points -- 2 x 2 x 3 array of 3D points
    """
    # (1) 2D -> 3D, (x', y', 1) = K^-1 * (x, y, 1)
    corners = np.ones((3, 4))
    corners[:2, 0] = 0
    corners[0, 1] = width
    corners[1, 1] = 0
    corners[0, 2] = 0
    corners[1, 2] = height
    corners[0, 3] = width
    corners[1, 3] = height

    K_inv = np.linalg.inv(K)
    cam_dir = np.dot(K_inv, corners)

    # (2) Include depth, (z * x', z * y', z) = z * (x', y', 1)
    cam_dir = depth * cam_dir

    # (3) Camera coord. system -> world space coord., p = R' * (z * x', z * y', z, 1) - R't
    Rt_matrix = np.zeros((4, 4))
    Rt_matrix[:3, :] = Rt
    Rt_matrix[3, 3] = 1
    Rt_inv = np.linalg.inv(Rt_matrix)

    cam_pts = np.ones((4, 4))
    cam_pts[:3, :] = cam_dir
    p = np.dot(Rt_inv, cam_pts)

    points = np.zeros((2, 2, 3))
    points[0, 0] = p[:3, 0]
    points[0, 1] = p[:3, 1]
    points[1, 0] = p[:3, 2]
    points[1, 1] = p[:3, 3]

    return points

def project_impl(K, Rt, points):# 把3D点根据相机内参数矩阵K和外参数旋转、平移矩阵投影到像素平面
    """
    Project 3D points into a calibrated camera.
    Input:
        K -- camera intrinsics calibration matrix
        Rt -- 3 x 4 camera extrinsics calibration matrix
        points -- height x width x 3 array of 3D points
    Output:
        projections -- height x width x 2 array of 2D projections
    """
    projection_matrix = K.dot(Rt)
    height, width = points.shape[:2]
    projections = np.zeros((height, width, 2))
    curr_point = np.zeros(3)

    for row_i, row in enumerate(points):
        for col_j, column in enumerate(row):
            curr_point = np.array(points[row_i, col_j])
            fourvec = np.array([curr_point[0], curr_point[1], curr_point[2], 1.0])
            homogenous_pt = projection_matrix.dot(fourvec)
            projections[row_i, col_j] = np.array(
                [homogenous_pt[0] / homogenous_pt[2], homogenous_pt[1] / homogenous_pt[2]])

    return projections



def preprocess_ncc_impl(image, ncc_size):
    '''  所谓预处理就是图片中每个像素点附近nccsize范围内的像素值
    减去这个区域的均值并归一化变成一行再存入一个图像大小的矩阵'''
    """
    Prepare normalized patch vectors according to normalized cross
    correlation.

    This is a preprocessing step for the NCC pipeline.  It is expected that
    'preprocess_ncc' is called on every input image to preprocess the NCC
    vectors and then 'compute_ncc' is called to compute the dot product
    between these vectors in two images.

    NCC preprocessing has two steps.
    (1) Compute and subtract the mean.
    (2) Normalize the vector.

    The mean is per channel.  i.e. For an RGB image, over the ncc_size**2
    patch, compute the R, G, and B means separately.  The normalization
    is over all channels.  i.e. For an RGB image, after subtracting out the
    RGB mean, compute the norm over the entire (ncc_size**2 * channels)
    vector and divide.

    If the norm of the vector is < 1e-6, then set the entire vector for that
    patch to zero.

    Patches that extend past the boundary of the input image at all should be
    considered zero.  Their entire vector should be set to 0.

    Patches are to be flattened into vectors with the default numpy row
    major order.  For example, given the following
    2 (height) x 2 (width) x 2 (channels) patch, here is how the output
    vector should be arranged.

    channel1         channel2
    +------+------+  +------+------+ height
    | x111 | x121 |  | x112 | x122 |  |
    +------+------+  +------+------+  |
    | x211 | x221 |  | x212 | x222 |  |
    +------+------+  +------+------+  v
    width ------->

    v = [ x111, x121, x211, x221, x112, x122, x212, x222 ]

    see order argument in np.reshape

    Input:
        image -- height x width x channels image of type float32
        ncc_size -- integer width and height of NCC patch region.
    Output:
        normalized -- heigth x width x (channels * ncc_size**2) array
    """
    height, width, channels = image.shape
    window_offset = int(ncc_size / 2)
    normalized = np.zeros((height, width, (channels * (ncc_size ** 2))))# 每个ncc_size内的像素之间都要算一次ZNCC，故ncc_size**2，一共channel遍
    for row_i in range(window_offset, height - window_offset):
        for col_k in range(window_offset, width - window_offset):
            patch_vector = image[row_i - window_offset:row_i + window_offset + 1,     #取[i,j]点周围NCCSIZE范围的所有像素值
                           col_k - window_offset:col_k + window_offset + 1, :]
            mean_vec = np.mean(np.mean(patch_vector, axis=0), axis=0)#  RGB三通道的平均值组成的向量
            patch_vector = patch_vector - mean_vec

            temp_vec = np.zeros((channels * (ncc_size ** 2)))#  展开成要求格式的减去平均值的各点像素值

            big_index = 0

            for channel in range(channels):
                for row in range(patch_vector.shape[0]):
                    for col in range(patch_vector.shape[1]):
                        temp_vec[big_index] = patch_vector[row, col, channel]
                        big_index += 1

            patch_vector = temp_vec
            if (np.linalg.norm(patch_vector) >= 1e-6):# 归一化
                patch_vector /= np.linalg.norm(patch_vector)
            else:# 丢掉太小的像素值
                patch_vector = np.zeros((channels * ncc_size ** 2))

            normalized[row_i, col_k] = patch_vector

    return normalized


def compute_ncc_impl(image1, image2):
    """
    就是把图像1，2对应点处的patch向量做内积
    Compute normalized cross correlation between two images that already have
    normalized vectors computed for each pixel with preprocess_ncc.

    Input:
        image1 -- height x width x (channels * ncc_size**2) array
        image2 -- height x width x (channels * ncc_size**2) array
    Output:
        ncc -- height x width normalized cross correlation between image1 and
               image2.
    """
    height, width = image1.shape[:2]
    ncc = np.zeros((height, width))

    for row_i in range(height):
        for col_k in range(width):
            ncc[row_i, col_k] = np.correlate(image1[row_i, col_k], image2[row_i, col_k])

    return ncc


def form_poisson_equation_impl(height, width, alpha, normals, depth_weight, depth):
    """
    Creates a Poisson equation given the normals and depth at every pixel in image.
    The solution to Poisson equation is the estimated depth. 
    When the mode, is 'depth' in 'combine.py', the equation should return the actual depth.
    When it is 'normals', the equation should integrate the normals to estimate depth.
    When it is 'both', the equation should weight the contribution from normals and actual depth,
    using  parameter 'depth_weight'.

    Input:
        height -- height of input depth,normal array
        width -- width of input depth,normal array
        alpha -- stores alpha value of at each pixel of image. 
            If alpha = 0, then the pixel normal/depth should not be 
            taken into consideration for depth estimation
        normals -- stores the normals(nx,ny,nz) at each pixel of image
            None if mode is 'depth' in combine.py
        depth_weight -- parameter to tradeoff between normals and depth when estimation mode is 'both'
            High weight to normals mean low depth_weight.
            Giving high weightage to normals will result in smoother surface, but surface may be very different from
            what the input depthmap shows.
        depth -- stores the depth at each pixel of image
            None if mode is 'normals' in combine.py
    Output:
        constants for equation of type Ax = b
        A -- left-hand side coefficient of the Poisson equation 
            note that A can be a very large but sparse matrix so csr_matrix is used to represent it.
        b -- right-hand side constant of the the Poisson equation
    """

    assert alpha.shape == (height, width)
    assert normals is None or normals.shape == (height, width, 3)
    assert depth is None or depth.shape == (height, width)

    '''
    Since A matrix is sparse, instead of filling matrix, we assign values to a non-zero elements only.
    For each non-zero element in matrix A, if A[i,j] = v, there should be some index k such that, 
        row_ind[k] = i
        col_ind[k] = j
        data_arr[k] = v
    Fill these values accordingly
    '''
    row_ind = []
    col_ind = []
    data_arr = []
    '''
    For each row in the system of equation fill the appropriate value for vector b in that row
    '''
    b = []
    if depth_weight is None:
        depth_weight = 1

    '''
    TODO
    Create a system of linear equation to estimate depth using normals and crude depth Ax = b

    x is a vector of depths at each pixel in the image and will have shape (height*width)
    A: ( k, height)
    x: ( height, width, 3)
    b: ( k, width)

    If mode is 'depth':
        > Each row in A and b corresponds to an equation at a single pixel
        > For each pixel k, 
            if pixel k has alpha value zero do not add any new equation.
            else, fill row in b with depth_weight*depth[k] and fill column k of the corresponding
                row in A with depth_weight.

        Justification: 
            Since all the elements except k in a row is zero, this reduces to 
                depth_weight*x[k] = depth_weight*depth[k]
            you may see that, solving this will give x with values exactly same as the depths, 
            at pixels where alpha is non-zero, then why do we need 'depth_weight' in A and b?
            The answer to this will become clear when this will be reused in 'both' mode

    Note: The normals in image are +ve when they are along an +x,+y,-z axes, if seen from camera's viewpoint.
    If mode is 'normals':
        > Each row in A and b corresponds to an equation of relationship between adjacent pixels
        > For each pixel k and its immideate neighbour along x-axis l
            if any of the pixel k or pixel l has alpha value zero do not add any new equation.
            else, fill row in b with nx[k] (nx is x-component of normal), fill column k of the corresponding
                row in A with -nz[k] and column k+1 with value nz[k]
        > Repeat the above along the y-axis as well, except nx[k] should be -ny[k].

        Justification: Assuming the depth to be smooth and almost planar within one pixel width.
        The normal projected in xz-plane at pixel k is perpendicular to tangent of surface in xz-plane.
        In other word if n = (nx,ny,-nz), its projection in xz-plane is (nx,nz) and if tangent t = (tx,0,tz),
            then n.t = 0, therefore nx/-nz = -tz/tx
        Therefore the depth change with change of one pixel width along x axis should be proporational to tz/tx = -nx/nz
        In other words (depth[k+1]-depth[k])*nz[k] = nx[k]
        This is exactly what the equation above represents.
        The negative sign in ny[k] is because the indexing along the y-axis is opposite of +y direction.

    If mode is 'both':
        > Do both of the above steps.

        Justification: The depth will provide a crude estimate of the actual depth. The normals do the smoothing of depth map
        This is why 'depth_weight' was used above in 'depth' mode. 
            If the 'depth_weight' is very large, we are going to give preference to input depth map.
            If the 'depth_weight' is close to zero, we are going to give preference normals.
    '''
    #TODO Block Begin
    #fill row_ind,col_ind,data_arr,b
    rn = 0
    for row_i in range(height):
        for col_j in range(width):
            k = row_i * width + col_j
            if alpha[row_i, col_j] != 0:
                if depth is not None:
                    b.append(depth_weight * depth[row_i, col_j])  # depth
                    row_ind.append(rn)  # depth
                    col_ind.append(k)  # depth
                    data_arr.append(depth_weight)  # depth
                    rn += 1

                if normals is not None:
                    if col_j + 1 <= width - 1 and alpha[row_i, col_j + 1] != 0:
                        # normals x-axis
                        b.append(normals[row_i, col_j, 0])
                        row_ind.append(rn)
                        col_ind.append(k)
                        data_arr.append(-normals[row_i, col_j, 2])
                        row_ind.append(rn)
                        col_ind.append(k + 1)
                        data_arr.append(normals[row_i, col_j, 2])
                        rn += 1
                    if row_i + 1 <= height - 1 and alpha[row_i + 1, col_j] != 0:
                        # normals mode y-axis
                        b.append(-normals[row_i, col_j, 1])
                        row_ind.append(rn)
                        col_ind.append(k)
                        data_arr.append(-normals[row_i, col_j, 2])
                        row_ind.append(rn)
                        col_ind.append(k + width)
                        data_arr.append(normals[row_i, col_j, 2])
                        rn += 1
    row = rn

    #TODO Block end
    # Convert all the lists to numpy array
    row_ind = np.array(row_ind, dtype=np.int32)
    col_ind = np.array(col_ind, dtype=np.int32)
    data_arr = np.array(data_arr, dtype=np.float32)
    b = np.array(b, dtype=np.float32)

    # Create a compressed sparse matrix from indices and values
    A = csr_matrix((data_arr, (row_ind, col_ind)), shape=(row, width * height))

    return A, b
