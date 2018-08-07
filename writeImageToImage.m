figure;



% Read one frame at a time.
for k =0:844
  
    %filename = sprintf(['D:/Hank/Tracker/data-moving/cars/imgs/img_%04d.jpg'],k);
    %filename = sprintf(['/media/DATA/Hank/Tracker/data-moving/cars/imgs/img_%04d.jpg'], k);
    %filename = sprintf(['/home/pal/Downloads/moseg/marple2/marple2_%03d.jpg'],k);
    %filename = sprintf(['D:/Hank/Data_mono/msm_201211281601/right%06d_img.jpg'],k);
    %filename = sprintf(['/media/DATA/Hank/movingObjectDetectionLibViso/data/outdoor_ntu_cafe/right%06d_img.jpg'],k);
    %filename = sprintf(['/dev/shm/right.ppm'],k);
    %filename = sprintf(['D:/Hank/movingObjectDetectionLibViso/data/outdoor_ntu_cafe/color%06d_img.jpg'],k);
    %filename = sprintf(['/home/pal/Projects/Data/Data_ntu_cafe/input4Results/Tracking%03d.ppm'],k);
    %filename = sprintf(['/media/DATA/Hank/Data_mono/h1/color%06d_img.jpg'],k);
    %filename = sprintf(['/home/pal/Projects/Data/msmh1_ppm/input1Results/Tracking%03d.ppm'],k);
    filename = sprintf(['D:/Hank/movingObjectDetectionLibViso/data/2011_09_26/2011_09_26_drive_0005_sync/image_02/data/%010d.png'],k);
    %filename = sprintf(['/home/pal/Desktop/data/%010d.png'],k);
    im = imread(filename);
    %im = imresize(im,[480 640]);
    %filename = sprintf(['color%03d_img.jpg'],k);
    filename = sprintf(['%010d.jpg'],k);
    imwrite(im,['Data/' filename ]);
    %filename2 = sprintf(['D:/Hank/movingObjectDetectionLibViso/data/outdoor_ntu_cafe/small/color%06d.jpg'],k);
    %filename2 = sprintf(['Data/Tracking%03d.png'],k);
    %im = imresize(im,[240,320]);
    
    %imwrite(im,filename2 ,'png');

    if(~exist('h'))
        h=imshow(im, 'border','tight');
    end
    
    set(h,'CData',im);
    drawnow;
    
    k = k+1; 
end