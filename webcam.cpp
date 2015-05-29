#include "webcam.h"
#include "ui_webcam.h"

#include <QtCore>
#include <QDebug>

#define FEAT_FACE_FILE "haarcascade_frontalface_alt.xml"


RNG rng(12345);

WebCam::WebCam(QWidget *parent) : QDialog(parent),ui(new Ui::WebCam)
{
    ui->setupUi(this);

    time = new QTimer(this);

    connect(time, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));

    time->start(50);
}

WebCam::~WebCam()
{
    capture.release();

    time->stop();

    delete ui;
}

//Read the camera.
void WebCam::processFrameAndUpdateGUI()
{
    capture.read(frame);
    if(frame.empty() == true)
        return;

    inRange(frame, Scalar(0,0,175), Scalar(100,100,256), camProcessed);
    GaussianBlur(camProcessed, camProcessed, Size(9,9), 1.5);
    cvtColor(frame, camProcessed, CV_BGR2RGB);

    img = QImage((const uchar*)frame.data, frame.rows, frame.cols, QImage::Format_RGB888);
    ui->webcamView->setPixmap(QPixmap::fromImage(img));


}

/*
void WebCam::paintEvent(QPaintEvent *detectevent)
{
    QPainter painter;

    painter.drawImage();
}
*/

//Open the camera.
void WebCam::on_cameraOpen_clicked()
{
    capture.open(0);
    if(capture.isOpened() == false){
        ui->camMessage->append("error: The Webcam is not open!");
        return;
    }

}

//Detecting the face.

void WebCam::on_faceDetect_clicked()
{
    //Checking the XML files.
    QString xmlfile;
    if(face_cascade.empty())
    {
        xmlfile = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FEAT_FACE_FILE);
        if(!face_cascade.load(xmlfile.toLatin1().constData()))
            qDebug() << tr("Cannot find %1").arg(xmlfile);
    }




    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);


    //Detect the faces.
    /*
    if(face_cascade)
    {




     }
     */
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0
                              //|CV_HAAR_DO_CANNY_PRUNING
                            |CV_HAAR_SCALE_IMAGE
                            //|CV_HAAR_FIND_BIGGEST_OBJECT
                            //|CV_HAAR_DO_ROUGH_SEARCH
                              ,Size(60, 60));

    //double detect_time = (double)getTickCount();

    //detect_time = (double)getTickCount() - detect_time;
    //time_total = detect_time / (double)getTickCount() * 1000;

    //cout << "Detection Time: %gms\n" << endl;

    for(size_t i = 0; i < faces.size(); i++)
    {
        int x = faces[i].x;
        int y = faces[i].y;
        int wid = faces[i].width;
        int hei = faces[i].height;

        Point face_point1(x, y);
        Point face_point2(x+wid, y+hei);

        rectangle(frame, face_point1, face_point2, Scalar(255, 0, 0), 3, 8, 0);
    }

    frame.release();
    frame_gray.release();

    QImage img((uchar*)frame.data, frame.rows, frame.cols, QImage::Format_RGB888);
    ui->webcamView->setPixmap(QPixmap::fromImage(img));
}


void WebCam::on_takePictures_clicked()
{
    Mat faceimg(320, 240, CV_BGR2RGB, Scalar(0, 50000, 50000));

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(98);

    bool get_image = imwrite("/home/pi/faceimages/test01.jpg", faceimg, compression_params);

    if(!get_image)
    {
        cout << "Error: Failed to save the image" << endl;
    }
}
