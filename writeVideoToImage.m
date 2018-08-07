%xyloObj = VideoReader('D:/Hank/Tracker/data-moving/cars/cars.mp4');
%xyloObj = VideoReader('/home/pal/Projects/Data/Taipei_scooter/Taipei scooter lane.mp4');
%xyloObj = VideoReader('/home/pal/Projects/Data/cars_ppl_ppm/VIDEO0030.mp4');
xyloObj = VideoReader('truck2.avi');


nFrames = xyloObj.NumberOfFrames
vidHeight = xyloObj.Height;
vidWidth = xyloObj.Width;

start = 1;
       


figure;
im = read(xyloObj, start);
%im = imresize(im,[480 640]);
h=imshow(im, 'border','tight');

g=0;
b = uicontrol('style','push','string','quit','callback','g=g+1');
k = start;

% Read one frame at a time.
while (g == 0) && (k < start+nFrames)
  
    im = read(xyloObj, k);
    %im = imresize(im,[480 640]);
    mov(k).cdata = read(xyloObj, k);
    filename = sprintf(['img_%04d'],k-1);
    imwrite(im,['Data/' filename '.jpg'],'jpg');
    %imwrite(im,['Data/' filename '.ppm'],'ppm');
    set(h,'CData',im);
    drawnow;
    
    k = k+1; 
end






