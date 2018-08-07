#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace std;
using namespace cv;

struct points{
	float x,y;
	int fnum;
};
typedef struct points Points;

struct pointstrack{
	int trackLength;
	vector<Points> trackPoints;
};
typedef struct pointstrack pointsTrack;

struct pointsandFrameNum{
	int totalFrameNum;
	vector<pointsTrack> allTrackPoints;
};
typedef struct pointsandFrameNum pointsAndFrameNum;

struct labeledobj{
	string object;
	vector<Point2f> labeledPoints;
};
typedef struct labeledobj labeledObj;

struct labeltrackobject{
	string object;
	vector<Point2f> labeltrackPoints;
};
typedef struct labeltrackobject labelTrackObject;

pointsAndFrameNum sortTrackingDataByEachPoint(FILE* fTrack){
	int i, finish = 0;
	int zero;
	char input[100];
	Points p;
	pointsAndFrameNum pointsAndFrameNumber;

	fgets(input, 100, fTrack);
	sscanf(input, "%d", &(pointsAndFrameNumber.totalFrameNum));
	fgets(input, 100, fTrack);
	while(finish == 0){
		fgets(input, 100, fTrack);
		pointsTrack trackPoint;
		sscanf(input, "%d %d", &zero, &trackPoint.trackLength);
		for(i = 1;i <= trackPoint.trackLength; i++){
			if(fgets(input, 100, fTrack)){
				sscanf(input, "%f %f %d", &(p.x), &(p.y), &(p.fnum));
				trackPoint.trackPoints.push_back(p);
				//cout << p.x << " " << p.y << " " << p.fnum << endl;
			}
			else{
				finish = 1;
				break;
			}
		}
		pointsAndFrameNumber.allTrackPoints.push_back(trackPoint);
	}

	return pointsAndFrameNumber;
}

void sortTrackingDataByFrame(pointsAndFrameNum pointsAndFrameNumber, vector<Points>* pointsPerFrame){
	vector<pointsTrack>::iterator outerIter;
	vector<Points>::iterator innerIter;
	for(outerIter = pointsAndFrameNumber.allTrackPoints.begin();outerIter != pointsAndFrameNumber.allTrackPoints.end();outerIter++){
		for(innerIter = (*outerIter).trackPoints.begin();innerIter != (*outerIter).trackPoints.end();innerIter++){
			//cout << innerIter->x << " " << innerIter->y << " " << innerIter->fnum << endl;
			if(innerIter->fnum >= 0 && innerIter->fnum < pointsAndFrameNumber.totalFrameNum){
				pointsPerFrame[innerIter->fnum].push_back(*innerIter);
			}
		}
	}
	/*for(innerIter = pointsPerFrame[153].begin();innerIter != pointsPerFrame[153].end(); innerIter++){
		cout << innerIter->x << " " << innerIter->y << " " << innerIter->fnum << endl;
	}*/
}

vector<labeledObj> loadLabeledObjects(FILE* fLabeledPoints){
	int i, finish = 0, pointsNum;
	char input[100];
	char* pch;
	vector<labeledObj> labeledObjectsList;
	Point2f p;

	while(finish == 0){
			if(!fgets(input, 100, fLabeledPoints))
				break;
			labeledObj labeledObjects;
			pch = strtok(input, " \n");
			labeledObjects.object.assign(pch);
			//labeledObjects.object.c_str() = pch;
			//cout<< labeledObjects.object << endl;
			if(pch != NULL)
				pch = strtok(NULL, " \n");
			pointsNum = atoi(pch);
			//cout << pointsNum << endl;
			//puts(labeledObjects.object);
			for(i = 1;i <= pointsNum; i++){
				if(fgets(input, 100, fLabeledPoints)){
					sscanf(input, "%f %f", &(p.x), &(p.y));
					labeledObjects.labeledPoints.push_back(p);
					//cout << p.x << " " << p.y << endl;
				}
				else{
					finish = 1;
					break;
				}
			}
			labeledObjectsList.push_back(labeledObjects);
			//puts(labeledObjects.object);
	}
	return labeledObjectsList;
}

void drawContour(vector<labeledObj> labeledObjectsList, Mat img){
	int i, j;
	/*vector<labeledObj>::iterator Iter;
	for(Iter = labeledObjectsList.begin();Iter != labeledObjectsList.end();Iter++){
		drawContours(img, (*Iter).labeledPoints, CV_FILLED, Scalar(0,255,255), 2, 8);
	}*/
	/*vector<vector<Point2f> > a;
	for(i = 0;i < labeledObjectsList.size();i++)
		a.push_back(labeledObjectsList[i].labeledPoints);*/

	for(i = 0;i < labeledObjectsList.size();i++){
		//cout << labeledObjectsList[i].object << endl;
		//drawContours(img, labeledObjectsList[i].labeledPoints, CV_FILLED, Scalar(0,255,255), 2, 8);
		for(j = 0;j < labeledObjectsList[i].labeledPoints.size();j++){
			//cout << labeledObjectsList[i].labeledPoints[j].x << labeledObjectsList[i].labeledPoints[j].y << endl;
			if(j != labeledObjectsList[i].labeledPoints.size()-1){
				switch(i % 6){
					case 0: //Yellow
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(0,255,255),3);
						break;
					case 1: //Green
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(0,255,0),3);
						break;
					case 2: //Magenta
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(255,0,255),3);
						break;
					case 3: //Cyan
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(255,255,0),3);
						break;
					case 4: //Blue
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(255,0,0),3);
						break;
					case 5: //Red
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[j+1], Scalar(0,0,255),3);
						break;
					default:
						break;
				}
			}
			else{
				switch(i % 6){
					case 0: //Yellow
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(0,255,255),3);
						break;
					case 1: //Green
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(0,255,0),3);
						break;
					case 2: //Magenta
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(255,0,255),3);
						break;
					case 3: //Cyan
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(255,255,0),3);
						break;
					case 4: //Blue
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(255,0,0),3);
						break;
					case 5: //Red
						line(img, labeledObjectsList[i].labeledPoints[j], labeledObjectsList[i].labeledPoints[0], Scalar(0,0,255),3);
						break;
					default:
						break;
				}
			}
		}
	}
}

vector<labelTrackObject> drawFeatureInContourAndExtCorPoint(pointsAndFrameNum pointsAndFrameNumber, vector<Points>* pointsPerFrame, vector<labeledObj> labeledObjectsList, Mat img1, int frameNum, Mat img2){
	int i,j,k;
	vector<labelTrackObject> labelTrackObjects;
	labelTrackObject TrackObject;
	vector<Points>::iterator innerIter;
	for(innerIter = pointsPerFrame[frameNum].begin();innerIter != pointsPerFrame[frameNum].end(); innerIter++){
		//cout << innerIter->x << " " << innerIter->y << " " << innerIter->fnum << endl;
		for(i = 0;i < labeledObjectsList.size();i++){
			TrackObject.object = labeledObjectsList[i].object;
			if(pointPolygonTest(labeledObjectsList[i].labeledPoints, Point2f(innerIter->x, innerIter->y), false) == 1){
				line(img1, Point2f(innerIter->x, innerIter->y), Point2f(innerIter->x, innerIter->y), Scalar(255,0,0),2);
				for(j = 0;j < pointsAndFrameNumber.allTrackPoints.size();j++){
					for(k = 0;k < pointsAndFrameNumber.allTrackPoints[j].trackPoints.size();k++){
						if(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k].fnum + pointsAndFrameNumber.allTrackPoints[j].trackLength-1 < frameNum || pointsAndFrameNumber.allTrackPoints[j].trackPoints[k].fnum > frameNum)
							break;
						else{
							if(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k].fnum == frameNum){
								if(innerIter->x == pointsAndFrameNumber.allTrackPoints[j].trackPoints[k].x && innerIter->y == pointsAndFrameNumber.allTrackPoints[j].trackPoints[k].y && k != pointsAndFrameNumber.allTrackPoints[j].trackPoints.size()-1){
									cout << innerIter->x << " " << innerIter->y << endl;
									if(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].fnum == frameNum+1){
										line(img2, Point2f(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].x, pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].y), Point2f(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].x, pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].y), Scalar(255,0,0),2);
										TrackObject.labeltrackPoints.push_back(Point2f(pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].x, pointsAndFrameNumber.allTrackPoints[j].trackPoints[k+1].y));
										break;
									}
								}
							}
						}
					}
				}
			}
			labelTrackObjects.push_back(TrackObject);
		}
	}
	return labelTrackObjects;
}

int main(){
	FILE* fTrack;
	FILE* fLabeledPoints;
	pointsAndFrameNum pointsAndFrameNumber;
	//vector<Points>::iterator innerIter;
	fTrack = fopen("D:\\research\\denseopticalflow\\scene2\\input1Tracks154.dat","r");
	if(!fTrack)
		cout << "track file not found" <<endl;
	pointsAndFrameNumber = sortTrackingDataByEachPoint(fTrack);
	//cout << "Sort by frame" << endl;
	//vector<Points> pointsPerFrame[pointsAndFrameNumber.totalFrameNum];
	vector<Points> pointsPerFrame[154];
	sortTrackingDataByFrame(pointsAndFrameNumber, pointsPerFrame);
	/*for(innerIter = pointsPerFrame[153].begin();innerIter != pointsPerFrame[153].end(); innerIter++){
			cout << innerIter->x << " " << innerIter->y << " " << innerIter->fnum << endl;
	}*/
	fLabeledPoints = fopen("D:\\research\\denseopticalflow\\scene2\\labeledPoints38.txt","r");
	if(!fLabeledPoints)
		cout << "labeledPoints file not found" <<endl;
	vector<labeledObj> labeledObjectsList;
	labeledObjectsList = loadLabeledObjects(fLabeledPoints);

	Mat img1 = imread("D:\\research\\denseopticalflow\\scene2\\0000000038.png");
	if(img1.empty())
		cout << "img1 file not found" << endl;
	Mat img2 = imread("D:\\research\\denseopticalflow\\scene2\\0000000039.png");
	if(img2.empty())
		cout << "img2 file not found" << endl;
	drawContour(labeledObjectsList, img1);
	vector<labelTrackObject> labelTrackObjects;
	labelTrackObjects = drawFeatureInContourAndExtCorPoint(pointsAndFrameNumber, pointsPerFrame, labeledObjectsList, img1, 38, img2);

	imshow("label", img1); 
	imshow("labelTracking", img2);
	waitKey();
	fclose(fTrack);
	fclose(fLabeledPoints);
	//system("pause");
	return 0;
}
