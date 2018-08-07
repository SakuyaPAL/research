
%writerObj = VideoWriter('newfile.avi','Uncompressed AVI');
writerObj = VideoWriter('newfile.avi','Motion JPEG AVI');
writerObj.FrameRate = 10;
writerObj.Quality = 100;
open(writerObj);


hh=figure;

start = 1;
stop = 1500;

%filepath = '/home/pal/Projects/Data/cars_ppl_ppm/result_good/';
%filepath = 'D:/Hank/Ubuntu12.04 - PCL/Projects/Data/cars_ppl_ppm/result_good/';
%filepath = 'D:/Hank/Ubuntu12.04 - PCL/Projects/Data/cars_ppl_ppm/input2Results/';
%fileformat = 'D:/Hank/VTD_CODE_V7.0/VTD/VTD/video/data/towncenter/frame1/frame_%04d.jpg';
filepath = 'D:/Hank/CNN/myRNN_temporal/output/result/motorbike2-stereo-seq4/';

filepath = 'D:/Hank/movingObjectDetectionLibViso/libviso2_tracking_opencv/libviso2_stereo/resultNTU/';
fileformat = [filepath 'disparity_%03d.png'];

%filepath = '/home/pal/workspace/libviso2_tracking/Result/';
%fileformat = [ filepath 'img_%06d.jpg'];
% fileformat = [ filepath 'imgLabels%03d.png'];
% fileformat2 = [ filepath 'motion_img_%04d.ppm'];
% fileformat3 = [ filepath  'img_%06d.ppm'];
%fileformat = [ filepath 'clustered_viso_dense%04d.png'];
%fileformat = [ filepath 'potential%04d.jpg'];

filename = sprintf(fileformat, 899);
im = imread(filename);%reading the 4 images named 

%filename2 = sprintf(fileformat2, start);
%im2 = imread(filename2);%reading the 4 images named 

%filename3 = sprintf(fileformat3, start);
%im3 = imread(filename3);%reading the 4 images named 

b = uicontrol('style','push','string','quit','callback','g=g+1');
g=0;

%im = [im2 im im3];

%subplot(1,2,1); 
h=imshow(im);
%subplot(1,2,2); 
%h2=imshow(im2);

for i= [899+1:899+100 899+300:899+400]%start:1:stop
filename = sprintf(fileformat, i);
im = imread(filename);%reading the 4 images named 
%1.bmp, 2.bmp, %3.bmp, 4.bmp
im =  imadjust(im, [0 0.8], [0 1]);
% 
% filename2 = sprintf(fileformat2, i);
% %im2 = imread(filename2);%reading the 4 images named 
% 
% filename3 = sprintf(fileformat3, i);
% %im3 = imread(filename3);%reading the 4 images named 

%im = [im2 im im3];

set(h,'CData',im);

%set(h2,'CData',im2);


%subplot(1,2,1); %
%h=imshow(im);
%subplot(1,2,2); 
%h2=imshow(im2);
drawnow;


%frame = getframe;
writeVideo(writerObj,im);
%imc = getimage(hh);
%writeVideo(writerObj,imc);
%himages = imhandles(gcf);
%writeVideo(writerObj,frame);


if(g)
    break;
end

end

close(writerObj);




