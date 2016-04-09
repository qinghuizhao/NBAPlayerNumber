#include <QCoreApplication>
#include <iostream>
#include "cv.h"
#include "highgui.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CvCapture* capture = cvCreateFileCapture("./NBA.mp4");
    IplImage* pFrame ;//读取视频帧
    IplImage* pFrameDelect=cvCreateImage(cvSize(1024,576),IPL_DEPTH_8U,3);
    IplImage *pGrayImage =  cvCreateImage(cvSize(1024,576), IPL_DEPTH_8U, 1);
    IplImage *pBinaryImage = cvCreateImage(cvSize(1024,576), IPL_DEPTH_8U, 1);
    IplImage *pBinaryImageTemp = cvCreateImage(cvSize(1024,576), IPL_DEPTH_8U, 1);
    IplImage*pTemp=cvCreateImage(cvSize(1024,576),8,1);
    CvScalar pFrameScalar;
    CvFont font;
    char text[4];
    char textTemp[4];
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.8, 0.8, 0, 1, 8);
    int nFrameNum=0;
    cvNamedWindow("NBAVideo");
    while (pFrame=cvQueryFrame(capture))
    {
        nFrameNum++;

        for (int i = 0; i < pFrame->height; i++)
        {
            for (int j = 0; j < pFrame->width; j++)
            {
                pFrameScalar=cvGet2D(pFrame, i, j);
                if (i<pFrame->height*1/5+50||i>pFrame->height*4/5||(i<3*j/4-275))
                    pFrameScalar.val[0]=pFrameScalar.val[1]=pFrameScalar.val[2]=0;
                if (!(pFrameScalar.val[0]>80 && pFrameScalar.val[0]<145 && pFrameScalar.val[1]>80 && pFrameScalar.val[1]<145 && pFrameScalar.val[2]>80 && pFrameScalar.val[2]<145)||
                        (abs(pFrameScalar.val[0]-pFrameScalar.val[1])>25||abs(pFrameScalar.val[1]-pFrameScalar.val[2])>25||abs(pFrameScalar.val[0]-pFrameScalar.val[2])>25))
                    pFrameScalar.val[0]=pFrameScalar.val[1]=pFrameScalar.val[2]=0;
                cvSet2D(pFrameDelect, i, j, pFrameScalar);
            }
        }
        CvSeq *contours = NULL;
        CvMemStorage *storage = cvCreateMemStorage(0);//储存矩形框
        CvMemStorage *storageTemp = cvCreateMemStorage(0);//储存矩形框
        cvCvtColor(pFrameDelect, pGrayImage, CV_BGR2GRAY);
        cvThreshold(pGrayImage, pBinaryImage, 0, 255, CV_THRESH_BINARY);
        cvCopy(pBinaryImage,pBinaryImageTemp);
        cvFindContours(pBinaryImageTemp, storage, &contours, sizeof(CvContour),CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        cvZero(pTemp);
        CvSeq* c = 0;
        for (c = contours; c != NULL; c = c->h_next)
        {
            int vale = fabs(cvContourArea(c, CV_WHOLE_SEQ)); //获取当前轮廓面积
            if (vale<200)
            {
                cvZero(c);
            }
        }
        CvSeq *contoursTemp = NULL;
        cvDrawContours(pTemp,contours, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255),2, CV_FILLED, 8, cvPoint(0, 0));
        cvDilate(pTemp, pTemp);
        cvFindContours( pTemp, storageTemp, &contoursTemp, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
        int personNumber=0;
        for( ; contoursTemp != 0; contoursTemp = contoursTemp->h_next )
        {
            personNumber++;
            CvRect rectimg=cvBoundingRect(contoursTemp,1);
            cvRectangle(pFrame,cvPoint(rectimg.x,rectimg.y),cvPoint(rectimg.x+rectimg.width ,rectimg.y+rectimg.height),CV_RGB(255,0,0),2);
        }
        if (personNumber>5)personNumber=5;
        cvPutText(pFrame, "grayPersonNum:", cvPoint(100,50), &font, cvScalar(0, 0, 255));
        sprintf(text, "%d",personNumber);
        cvPutText(pFrame, text, cvPoint(350,50), &font, cvScalar(0, 255, 0));
        sprintf(textTemp, "%d",nFrameNum);
        cvPutText(pFrame, textTemp, cvPoint(20,20), &font, cvScalar(0, 255, 0));
        cvShowImage("NBAVideo",  pFrame);
        cvWaitKey(1);
        cvReleaseMemStorage(&storage);
        cvReleaseMemStorage(&storageTemp);
    }
    cvDestroyAllWindows();
    cvReleaseImage(&pGrayImage);
    cvReleaseImage(&pBinaryImage);
    cvReleaseImage(&pBinaryImageTemp);
    cvReleaseImage(&pTemp);
    cvReleaseImage(&pFrameDelect);
    return a.exec();
    return 0;
}
