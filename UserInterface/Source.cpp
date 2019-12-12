#include "Header.h"

Button::Button()
	: x(0), y(0), buttonSrc("./Assets/images/On_Button2.png") { }

Button::Button(const int _x, const int _y, string _buttonSrc, string _buttonFlag, string _buttonColor)

		: x(_x), y(_y), buttonSrc(_buttonSrc), buttonFunctionFlag(_buttonFlag), buttonColor(_buttonColor){ }

CheckBox::CheckBox()
		:x(0), y(0), checkBoxOnSrc("./Assets/images/CheckBoxON.png"), checkBoxOffSrc("./Assets/images/CheckBoxOFF.png") { }

CheckBox::CheckBox(const int _x, const int _y, string _checkBoxOnSrc, string _checkBoxOffSrc, string _checkBoxFlag)
		:x(_x), y(_y), checkBoxOnSrc(_checkBoxOnSrc), checkBoxOffSrc(_checkBoxOffSrc), checkBoxFunctionFlag(_checkBoxFlag){ }

Manager::Manager() {}

void Manager::AddCanvas(string canvasSrc)
{
	canvas = imread(canvasSrc, IMREAD_UNCHANGED);
}

void Manager::AddButton(Button button)
{
	buttons.push_back(button);
	buttons.back().imgButton.copyTo(interfaceImg(buttons.back().rectButton));
}

void Manager::AddCheckbox(CheckBox checkbox)
{
	checkboxes.push_back(checkbox);
	checkboxes.back().imgCheckBox.copyTo(interfaceImg(checkboxes.back().rectCheckBox));
}

void Manager::Save()
	{
		while (1)
		{
			cout << "Enter the file name:" << endl;

			string canvasSrc;
			cin >> canvasSrc;

			try 
			{
				imwrite("canvasSrc", canvas);
			}
			catch (runtime_error& ex)
			{
				fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
				return;
			}

			cout << "Saved";
			break;
		}
	}

void Manager::Load()
	{
		while (1)
		{
			cout << "Enter the file name:" << endl;

			string canvasSrc;
			cin >> canvasSrc;

			canvas = imread(canvasSrc, IMREAD_UNCHANGED);
			if (!canvas.data)                              // Check for invalid input
			{
				cout << "Could not open or find the image" << endl;
			}
			else
			{
				break;
			}
		}
	}

void Manager::Color(string colorName)
	{
		int channel;

		if (colorName == "blue") { channel = 0;}
		else if (colorName == "green") { channel = 1; }
		else if (colorName == "red") { channel = 2; }
		else { channel = 0; }

		for (int i = 0; i < canvas.rows; i++)
		{
			for (int j = 0; j < canvas.cols; j++)
			{
				if (colorFlag)
				{
					canvas.at<Vec3b>(i, j)[channel] += 255 / 10;
				}
				else
				{
					canvas.at<Vec3b>(i, j)[channel] -= 255 / 10;
				}
			}
		}
	}

void Manager::Grid(int color)
	{
		backup = canvas.clone();
		for (int i = 0; i < canvas.rows; i++)
		{
			for (int j = 0; j < canvas.cols; j++)
			{
				if ((i % 20 == 10 && j % 2 == 1) || (j % 50 == 25 && i % 2 == 1))
				{
					canvas.at<Vec3b>(i, j)[0] = color;
					canvas.at<Vec3b>(i, j)[1] = color;
					canvas.at<Vec3b>(i, j)[2] = color;
				}
			}
		}
	}


// обработчик событий от мышки
void myMouseCallback(int event, int x, int y, int flags, void* param)
{
	Manager *manager = (Manager*)param;

	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		break;

	case CV_EVENT_LBUTTONDOWN:
		if (event == EVENT_LBUTTONDOWN)
		{
			for (int n = 0; n < (*manager).buttons.size(); n++)
			{
				if ((*manager).buttons[n].rectButton.contains(Point(x, y)))
				{
					cout << "Button " << n + 1 << " clicked!" << endl;
					
					if ((*manager).buttons[n].buttonFunctionFlag == "Color")
					{
						(*manager).Color((*manager).buttons[n].buttonColor);
					}

					if ((*manager).buttons[n].buttonFunctionFlag == "Save")
					{
						(*manager).Save();
					}

					if ((*manager).buttons[n].buttonFunctionFlag == "Load")
					{
						(*manager).Load();
					}
				}
			}

			for (int n = 0; n < (*manager).checkboxes.size(); n++)
			{
				if ((*manager).checkboxes[n].rectCheckBox.contains(Point(x, y)))
				{
					cout << "CheckBox " << n + 1 << " clicked!" << endl;

					if ((*manager).checkboxes[n].checkBoxFlag)
					{
						(*manager).checkboxes[n].checkBoxFlag = false;
						(*manager).checkboxes[n].imgCheckBox = imread((*manager).checkboxes[n].checkBoxOffSrc, IMREAD_UNCHANGED);
						(*manager).checkboxes[n].imgCheckBox.copyTo((*manager).interfaceImg((*manager).checkboxes[n].rectCheckBox));

						if ((*manager).checkboxes[n].checkBoxFunctionFlag == "grid")
						{
							(*manager).Grid(255);
						}

						if ((*manager).checkboxes[n].checkBoxFunctionFlag == "color")
						{
							(*manager).colorFlag = false;
						}
					}
					else
					{
						(*manager).checkboxes[n].checkBoxFlag = true;
						(*manager).checkboxes[n].imgCheckBox = imread((*manager).checkboxes[n].checkBoxOnSrc, IMREAD_UNCHANGED);
						(*manager).checkboxes[n].imgCheckBox.copyTo((*manager).interfaceImg((*manager).checkboxes[n].rectCheckBox));

						if ((*manager).checkboxes[n].checkBoxFunctionFlag == "grid")
						{
							(*manager).canvas = (*manager).backup.clone();
						}

						if ((*manager).checkboxes[n].checkBoxFunctionFlag == "color")
						{
							(*manager).colorFlag = true;
						}
					}
				}
			}

			printf("%d x %d\n", x, y);
			break;
		}

	case CV_EVENT_LBUTTONUP:
		break;
	}
}

