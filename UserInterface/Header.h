#ifndef HEADER_H
#define HEADER_H

#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

class Button
{
private:
	int x; int y;
	string buttonSrc;
public:
	string buttonFunctionFlag;
	string buttonColor;

	Button();
	Button(const int _x, const int _y, string _buttonSrc, string _buttonFlag, string _buttonColor);

	Mat imgButton = imread(buttonSrc, IMREAD_UNCHANGED);;
	Rect rectButton = Rect(x, y, imgButton.cols, imgButton.rows);
};

class CheckBox
{
private:
	int x; int y;
public:
	string checkBoxOnSrc; string checkBoxOffSrc;
	string checkBoxFunctionFlag;

	CheckBox();
	CheckBox(const int _x, const int _y, string _checkBoxOnSrc, string _checkBoxOffSrc, string _checkBoxFlag);

	bool checkBoxFlag = true;
	Mat imgCheckBox = imread(checkBoxOnSrc, IMREAD_UNCHANGED);
	Rect rectCheckBox = Rect(x, y, imgCheckBox.cols, imgCheckBox.rows);
};

class Manager
{
public:
	vector<Button> buttons;
	vector<CheckBox> checkboxes;

	Mat interfaceImg = imread("Interface.png", IMREAD_UNCHANGED);
	Mat backup;
	Mat canvas;

	bool colorFlag = true;

	Manager();

	void AddCanvas(string canvasSrc);
	void AddButton(Button button);
	void AddCheckbox(CheckBox checkbox);

	void Save();
	void Load();
	void Color(string colorName);
	void Grid(int color);
};

// обработчик событий от мышки
void myMouseCallback(int event, int x, int y, int flags, void* param);

#endif