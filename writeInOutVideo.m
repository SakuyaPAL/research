

folder = 'F:/Research/master_thesis/';
folderOut = './';

listing = dir(folder);
listing = listing(3:end); % remove '.' and '..'


for i = 1:numel(listing)

    filename = '00060.MTS'; %listing(i).name;
    path = [folder filename];
    
xyloObj = VideoReader(path);

nFrames = xyloObj.NumberOfFrames;
vidHeight = xyloObj.Height;
vidWidth = xyloObj.Width;

start = 1;

debugOn = 0;
       
%type = 'Uncompressed AVI';
type = 'Motion JPEG AVI';
%type = 'MPEG-4';
writerObj = VideoWriter([folderOut filename], type);

%writerObj = VideoWriter('out.avi');
writerObj.FrameRate = xyloObj.FrameRate;
open(writerObj);       

%newsize = [320 480];
%newsize = 0.5;
newsize = 1;
figure(10);
im = read(xyloObj, start);
im = imresize(im,newsize );
h=imshow(im, 'border','tight'); drawnow;

g=0;
b = uicontrol('style','push','string','quit','callback','g=g+1');
k = start+1;

% Read one frame at a time.
while g == 0 && k < start+nFrames
  
    im = read(xyloObj, k);
    im = imresize(im,newsize );
 %   mov(k).cdata = read(xyloObj, k);
    writeVideo(writerObj,im);
    if(debugOn)
        set(h,'CData',im);
        drawnow;
    end
    
    k = k+1; 
end

close(writerObj);

end


