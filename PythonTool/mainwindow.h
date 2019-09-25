#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "../ImageProcess/imageprocess.h"

#define SIGNGLE_WIDTH 1272
#define CHANNEL_NUM 6

class QImage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();

    void initOffset();

    void updateImage();

    void h_offset(bool isLeft, int offset);

    void v_offset(bool isLeft, int offset);	
	
    void getCorrectData(uchar* src, int width, int height, uchar *dst);
	
    void saveCorrectData(const QString& filename, const char* black, const char* white, size_t length = SIGNGLE_WIDTH * CHANNEL_NUM);

private slots:
    void on_btn_open_clicked();

    void on_btn_import_clicked();

	void on_btn_preview_clicked();

    void on_btn_export_clicked();

    void on_comboBox_gap_currentIndexChanged(int index);

    void on_btn_l_l_clicked();

    void on_btn_l_ll_clicked();

    void on_btn_l_r_clicked();

    void on_btn_l_rr_clicked();

    void on_btn_l_u_clicked();

    void on_btn_l_uu_clicked();

    void on_btn_l_d_clicked();

    void on_btn_l_dd_clicked();

    void on_btn_r_l_clicked();

    void on_btn_r_ll_clicked();

    void on_btn_r_r_clicked();

    void on_btn_r_rr_clicked();

    void on_btn_r_u_clicked();

    void on_btn_r_uu_clicked();

    void on_btn_r_d_clicked();

    void on_btn_r_dd_clicked();

    void on_btn_dir_black_clicked();

    void on_btn_path_white_clicked();

    void on_btn_export_correct_clicked();

    void on_checkBox_black_clicked(bool checked);

    void on_checkBox_white_clicked(bool checked);

private:
    Ui::MainWindow *ui;
private:
    QImage* m_image;
    PixelOffset m_offset[CHANNEL_NUM];
};

#endif // MAINWINDOW_H
