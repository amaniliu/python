#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ImageProcess.h"

namespace Ui {
class MainWindow;
}

class QImage;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_btn_save_clicked();

    void on_hslider_optimize_valueChanged(int value);

    void on_btn_dir_clicked();

    void on_spin_h_edit_finished();

    void on_spin_v_edit_finished();

    void on_check_montage_toggled(bool checked);

    void on_check_contour_toggled(bool checked);

    void showImage(uchar* buffer, long length);

	void reciveMsg(int msg);

private:
    void initUI();

    void initSettings();

    void initUsbDevice();

    void saveSettings();

    void getCorrectData();

	void getMontageData();

    static void callback_getPicInfo(uchar* buffer, long length);

    static void callback_reciveMsg(int msg);

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long * result);

private:
    Ui::MainWindow *ui;
private:
    QImage* m_image;
    ImageProcess* m_imageProcess;
    PixelOffset offsets[6];
};

#endif // MAINWINDOW_H
