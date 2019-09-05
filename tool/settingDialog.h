#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QWidget>
#include <QToolButton>
#include <QComboBox>
#include <QGraphicsView>
#include <QGraphicsScene>

class QImage;

struct PixelOffset
{
	unsigned int m_top;
	unsigned int m_left;
	unsigned int m_right;
};

class CorrectDialog;
class SettingDialog : public QWidget
{
	Q_OBJECT
public:
	SettingDialog(QWidget* parent = 0);
	~SettingDialog();
private:
	void initUi();
	void initOffset();
	void h_offset(bool isLeft, int offset);
	void v_offset(bool isLeft, int offset);

	void updateImage();
private slots:
	void btn_open();
	void btn_save();
	void btn_improt();

	void indexChanged(int);

	void btn_l_l();
	void btn_l_ll();
	void btn_l_u();
	void btn_l_uu();
	void btn_l_r();
	void btn_l_rr();
	void btn_l_d();
	void btn_l_dd();

	void btn_r_l();
	void btn_r_ll();
	void btn_r_u();
	void btn_r_uu();
	void btn_r_r();
	void btn_r_rr();
	void btn_r_d();
	void btn_r_dd();
private:
	QToolButton* m_btn_open;
	QToolButton* m_btn_import;
	QToolButton* m_btn_save;

	QComboBox* m_cb_channel;

	QGraphicsView* m_view;
	QGraphicsScene* m_scene;
	QToolButton *m_btn_l_l;
	QToolButton *m_btn_l_ll;
	QToolButton *m_btn_l_r;
	QToolButton *m_btn_l_rr;
	QToolButton *m_btn_l_u;
	QToolButton *m_btn_l_uu;
	QToolButton *m_btn_l_d;
	QToolButton *m_btn_l_dd;

	QToolButton *m_btn_r_l;
	QToolButton *m_btn_r_ll;
	QToolButton *m_btn_r_r;
	QToolButton *m_btn_r_rr;
	QToolButton *m_btn_r_u;
	QToolButton *m_btn_r_uu;
	QToolButton *m_btn_r_d;
	QToolButton *m_btn_r_dd;

	CorrectDialog* m_correctDialog;
private:
	QImage* m_image;
	PixelOffset m_offset[6];
};
#endif
