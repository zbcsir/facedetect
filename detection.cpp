#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <detection.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

string cascadeName = "C:\\Qt\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
//string cascadeName = "C:\\Users\\zbc\\Downloads\\FrontalFace10\\haarcascade_frontalface_default.xml" ;
//string cascadeName = "D:\\FaceDetection\\Image_Download\\20x20face_non_faceBMP\\data.xml" ;
//string cascadeName = "D:\\FaceDetection\\Image_Download\\facenoface224\\AFLW_facedetectSet\\data\\cascade.xml" ;
//string cascadeName = "D:\\FaceDetection\\Image_Download\\facenoface224\\imagenew\\classfiernew\\cascade.xml" ;
string nestedCascadeName = "C:\\Qt\\opencv\\sources\\data\\lbpcascades\\lbpcascade_frontalface.xml";
String cascadeNameProfile = "C:\\Qt\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml" ;

int detect(const QString imageName ,double scale)
{
    Mat image;
    string inputName;
    bool tryflip = false;


    CascadeClassifier cascade;
    CascadeClassifier cascadeProfile ;
//    double scale = 2;

    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }



    //读取图像
    image = imread(imageName.toStdString(), 1 );
    if(image.empty()) cerr << "Couldn't read image" << endl;

    cvNamedWindow( "result", 1 );

    int faceCount = 0 ;
//    cout << "In image read" << endl;
    if( !image.empty() )
    {
        faceCount = detectAndDraw( image, cascade, cascadeProfile, scale, tryflip );
//            cout<<"The Count Of Face Is : "<<faceCount<<endl ;
        waitKey(0);
    }
    else if( !inputName.empty() )
    {
        /* assume it is a text file containing the
        list of the image filenames to be processed - one per line */
        FILE* f = fopen( inputName.c_str(), "rt" );
        if( f )
        {
            char buf[1000+1];
            while( fgets( buf, 1000, f ) )
            {
                int len = (int)strlen(buf), c;
                while( len > 0 && isspace(buf[len-1]) )
                    len--;
                buf[len] = '\0';
                //cout << "file " << buf << endl;
                image = imread( buf, 1 );
                if( !image.empty() )
                {
                    faceCount = detectAndDraw( image, cascade, cascadeProfile, scale, tryflip );
                  //  cout<<"The Count Of Face Is : "<<faceCount<<endl ;
                    c = waitKey(0);
                    if( c == 27 || c == 'q' || c == 'Q' )
                        break;
                }
                else
                {
                    cerr << "Aw snap, couldn't read image " << buf << endl;
                }
            }
            fclose(f);
        }
    }

    cvDestroyWindow("result");

    return 0;
}

//检测
int detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& cascadeProfile,
                    double scale, bool tryflip )
{
    int faceCount = 0 ;
    int i = 0 ;
    double t = 0;
    vector<Rect> faces, faces2;
    vector<Rect> facesProfile , facesProfile2 ;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;

    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    t = (double)cvGetTickCount();

    //检测正脸人头数
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30) );

    //检测侧脸人头
    cascadeProfile.detectMultiScale(smallImg ,facesProfile, 1.1, 2,
                                     0|CV_HAAR_SCALE_IMAGE,
                                     Size(30,30));
    if( tryflip )
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale( smallImg, faces2,
                                 1.1, 2, 0
                                 //|CV_HAAR_FIND_BIGGEST_OBJECT
                                 //|CV_HAAR_DO_ROUGH_SEARCH
                                 |CV_HAAR_SCALE_IMAGE
                                 ,
                                 Size(30, 30) );
        for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++ )
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }

        cascadeProfile.detectMultiScale(smallImg ,facesProfile2, 1.1, 2,
                                         0|CV_HAAR_SCALE_IMAGE,
                                         Size(30,30));
        for( vector<Rect>::const_iterator r = facesProfile2.begin(); r != facesProfile2.end(); r++ )
        {
            facesProfile.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }
    t = (double)cvGetTickCount() - t;
//    printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r->width/r->height;
        if(0.75 < aspect_ratio && aspect_ratio < 1.33 )
        {
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
            faceCount ++ ;
        }
        else{
            rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
                                   cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
                                   color, 3, 8, 0);
        }
    }

    cv::imshow( "result", img );
    return faceCount ;
}
