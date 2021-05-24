import sys
sys.path.append('/Users/kb/bin/opencv-3.1.0/build/lib/')

import cv2
import numpy as np

def cross_correlation_2d(img, kernel):
    '''Given a kernel of arbitrary m x n dimensions, with both m and n being
    odd, compute the cross correlation of the given image with the given
    kernel, such that the output is of the same dimensions as the image and that
    you assume the pixels out of the bounds of the image to be zero. Note that
    you need to apply the kernel to each channel separately, if the given image
    is an RGB image.

    Inputs:
        img:    Either an RGB image (height x width x 3) or a grayscale image
                (height x width) as a numpy array.
        kernel: A 2D numpy array (m x n), with m and n both odd (but may not be
                equal).

    Output:
        Return an image of the same dimensions as the input image (same width,
        height and the number of color channels)
    '''

    def cross_correlation_2d_channel(channel, kernel):
        G = np.array(channel)
        size = channel.shape
        for i in range(size[0]):
            for j in range(size[1]):
                sum = 0.0
                ksize = kernel.shape
                for u in range(ksize[0]):
                    for v in range(ksize[1]):
                        try:
                            assert (i + u - ksize[0] // 2)>=0 and (j + v - ksize[1] // 2)>=0
                            sum += kernel[u][v] * channel[i + u - ksize[0] // 2][j + v - ksize[1] // 2]
                        except Exception:
                            sum+=0
                G[i][j] = sum
        return G

    if img.ndim is 3:
        newimg = np.array(img)
        for channel in range(img.ndim):
            newimg[:,:,channel] = cross_correlation_2d_channel(img[:,:,channel],kernel)
    else :
        newimg = cross_correlation_2d_channel(img,kernel)
    return newimg



def convolve_2d(img, kernel):
    '''Use cross_correlation_2d() to carry out a 2D convolution.

    Inputs:
        img:    Either an RGB image (height x width x 3) or a grayscale image
                (height x width) as a numpy array.
        kernel: A 2D numpy array (m x n), with m and n both odd (but may not be
                equal).

    Output:
        Return an image of the same dimensions as the input image (same width,
        height and the number of color channels)
    '''

    def cross_correlation_2d_channel(channel, kernel):
        G = np.array(channel)
        size = channel.shape
        for i in range(size[0]):
            for j in range(size[1]):
                sum = 0.0
                ksize = kernel.shape
                for u in range(ksize[0]):
                    for v in range(ksize[1]):
                        try:
                            assert (i - u + ksize[0] // 2)>=0 and (j - v + ksize[1] // 2)>=0
                            sum += kernel[u][v] * channel[i - u + ksize[0] // 2][j - v + ksize[1] // 2]
                        except Exception:
                            sum+=0
                G[i][j] = sum
        return G

    if img.ndim is 3:
        newimg = np.array(img)
        for channel in range(img.ndim):
            newimg[:,:,channel] = cross_correlation_2d_channel(img[:,:,channel],kernel)
    else :
        newimg = cross_correlation_2d_channel(img,kernel)
    return newimg

def gaussian_blur_kernel_2d(sigma, height, width):
    '''Return a Gaussian blur kernel of the given dimensions and with the given
    sigma. Note that width and height are different.

    Input:
        sigma:  The parameter that controls the radius of the Gaussian blur.
                Note that, in our case, it is a circular Gaussian (symmetric
                across height and width).
        width:  The width of the kernel.
        height: The height of the kernel.

    Output:
        Return a kernel of dimensions height x width such that convolving it
        with an image results in a Gaussian-blurred image.
    '''
    height_center = height//2.0
    width_center = width//2.0
    def gaussian(x,y):
        x = x- height_center
        y = y - width_center
        rs = np.exp(-(x ** 2 + y ** 2) / (2 * (sigma ** 2)))
        return  rs
    gaussian = np.fromfunction(gaussian,(height,width))
    sum_matrix = np.sum(np.reshape(gaussian, (gaussian.size,)))
    return gaussian/sum_matrix


def low_pass(img, sigma, size):
    '''Filter the image as if its filtered with a low pass filter of the given
    sigma and a square kernel of the given size. A low pass filter supresses
    the higher frequency components (finer details) of the image.

    Output:
        Return an image of the same dimensions as the input image (same width,
        height and the number of color channels)
    '''
    return convolve_2d(img,gaussian_blur_kernel_2d(sigma,size,size))

def high_pass(img, sigma, size):
    '''Filter the image as if its filtered with a high pass filter of the given
    sigma and a square kernel of the given size. A high pass filter suppresses
    the lower frequency components (coarse details) of the image.

    Output:
        Return an image of the same dimensions as the input image (same width,
        height and the number of color channels)
    '''
    return img - low_pass(img,sigma,size)

def create_hybrid_image(img1, img2, sigma1, size1, high_low1, sigma2, size2,
        high_low2, mixin_ratio):
    '''This function adds two images to create a hybrid image, based on
    parameters specified by the user.'''
    high_low1 = high_low1.lower()
    high_low2 = high_low2.lower()

    if img1.dtype == np.uint8:
        img1 = img1.astype(np.float32) / 255.0
        img2 = img2.astype(np.float32) / 255.0

    if high_low1 == 'low':
        img1 = low_pass(img1, sigma1, size1)
    else:
        img1 = high_pass(img1, sigma1, size1)

    if high_low2 == 'low':
        img2 = low_pass(img2, sigma2, size2)
    else:
        img2 = high_pass(img2, sigma2, size2)

    img1 *= 2 * (1 - mixin_ratio)
    img2 *= 2 * mixin_ratio
    hybrid_img = (img1 + img2)
    return (hybrid_img * 255).clip(0, 255).astype(np.uint8)