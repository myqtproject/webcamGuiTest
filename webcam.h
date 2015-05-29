#ifndef WEBCAM_H
#define WEBCAM_H

#include <QDialog>
#include <QPainter>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>


using namespace cv;
using namespace std;


namespace Ui {
class WebCam;
}


class WebCam : public QDialog
{
    Q_OBJECT
    
public:
    explicit WebCam(QWidget *parent = 0);
    ~WebCam();



private:
    Ui::WebCam *ui;
    VideoCapture capture;
    Mat frame;
    Mat camProcessed;
    Mat frame_gray;
    vector<Rect> faces;

    QImage img;
    QTimer *time;


    CascadeClassifier face_cascade;


//protected:
    //void paintEvent(QPaintEvent *detectevent);

public slots:
    void processFrameAndUpdateGUI();


private slots:
    void on_cameraOpen_clicked();
    void on_faceDetect_clicked();
    void on_takePictures_clicked();
};

#endif // WEBCAM_H
