#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#define SIGNGLE_WIDTH 1272
#define CHANNEL_NUM 6

class QImage;

struct PixelOffset
{
    int m_top;
    int m_left;
    int m_right;
};
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

private slots:
    void on_btn_open_clicked();

    void on_btn_import_clicked();

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

private:
    Ui::MainWindow *ui;
private:
    QImage* m_image;
    PixelOffset m_offset[CHANNEL_NUM];
};

#endif // MAINWINDOW_H
