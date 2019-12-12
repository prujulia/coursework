#include "Header.h"

int main(int argc, char* argv[])
{
	const string redButtonSrc = "RedButton.png";
	const string greenButtonSrc = "GreenButton.png";
	const string blueButtonSrc = "BlueButton.png";
	const string saveSrc = "Save.png";
	const string loadSrc = "Load.png";
	const string checkBoxOnSrc = "CheckBoxON.png"; const string checkBoxOffSrc = "CheckBoxOFF.png";
	const string canvasSrc = "canvas.png";

	Manager manager;

	manager.AddCanvas(canvasSrc);

	//manager.AddButton(Button(75, 120, purpleButtonSrc, "Color", "purple"));
	manager.AddButton(Button(75, 180, blueButtonSrc, "Color", "blue"));
	manager.AddButton(Button(30, 150, redButtonSrc, "Color", "red"));
	manager.AddButton(Button(120, 150, greenButtonSrc, "Color", "green"));

	manager.AddButton(Button(25, 300, saveSrc, "Save", "None"));
	manager.AddButton(Button(115, 300, loadSrc, "Load", "None"));

	manager.AddCheckbox(CheckBox(25, 66, checkBoxOnSrc, checkBoxOffSrc, "color"));
	manager.AddCheckbox(CheckBox(125, 66, checkBoxOnSrc, checkBoxOffSrc, "grid"));

	void *interfaceParam = &manager;

	// окно для отображения картинки
	cvNamedWindow("interface", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("canvas", CV_WINDOW_AUTOSIZE);

	// вешаем обработчик мышки
	cvSetMouseCallback("interface", myMouseCallback, interfaceParam);

	while (1) {
		// показываем картинку
		imshow("interface", manager.interfaceImg);
		imshow("canvas", manager.canvas);

		char c = cvWaitKey(33);
		if (c == 27) { // если нажата ESC - выходим
			break;
		}
	}

	// удаляем окно
	cvDestroyWindow("original");
	return 0;
}