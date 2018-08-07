imgNum = 0;

while(1)

path = 'Data/';
filename = sprintf([path '%04d.mat'],imgNum);
load(filename);

filename = sprintf([path 'rgb%04d.jpg'],imgNum);
imwrite(kinect_info.I,filename, 'jpg');
 filename = sprintf([path 'D%04d.mat'],imgNum);
 tmp = kinect_info.D;
save(filename, 'tmp');
 filename = sprintf([path 'X%04d.mat'],imgNum);
tmp = kinect_info.X;
save(filename, 'tmp');
 filename = sprintf([path 'Y%04d.mat'],imgNum);
tmp = kinect_info.Y;
save(filename, 'tmp');
 filename = sprintf([path 'Z%04d.mat'],imgNum);
tmp = kinect_info.Z;
save(filename, 'tmp');

imgNum = imgNum + 1;

end