leftImage = imread('label/stereo_ntu_cafe/left000635_img.jpg');
rightImage = imread('label/stereo_ntu_cafe/right000635_img.jpg');
D = disparity(leftImage, rightImage);
imshow(D);