#include "Prototype.h"

// コールバック関数
void onMouse(int event, int x, int y, int flags, void* param){
	// eventに起きたイベントの種類が格納される
	// flagsに共起したイベントが含まれている
	if(event == CV_EVENT_LBUTTONDOWN && !strcmp((char*)param, "ROTATE")){
		printf("x:%03d y:%03d\n", x, y);
	}
	char str[64];
	static int line = 0;
	const int max_line = 15, w = 15, h = 30;

	//マウスイベントを取得
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MOUSE_MOVE");
		break;
	case CV_EVENT_LBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOWN");
		break;
	case CV_EVENT_RBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOWN");
		break;
	case CV_EVENT_MBUTTONDOWN:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOWN");
		break;
	case CV_EVENT_LBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_UP");
		break;
	case CV_EVENT_RBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_UP");
		break;
	case CV_EVENT_MBUTTONUP:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_UP");
		break;
	case CV_EVENT_LBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOUBLE_CLICK");
		break;
	case CV_EVENT_RBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOUBLE_CLICK");
		break;
	case CV_EVENT_MBUTTONDBLCLK:
		snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOUBLE_CLICK");
		break;
	}
	// (5)マウスボタン，修飾キーを取得
	if (flags & CV_EVENT_FLAG_LBUTTON)
		strncat (str, " + LBUTTON", 64);
	if (flags & CV_EVENT_FLAG_RBUTTON)
		strncat (str, " + RBUTTON", 64);
	if (flags & CV_EVENT_FLAG_MBUTTON)
		strncat (str, " + MBUTTON", 64);
	if (flags & CV_EVENT_FLAG_CTRLKEY)
		strncat (str, " + CTRL", 64);
	if (flags & CV_EVENT_FLAG_SHIFTKEY)
		strncat (str, " + SHIFT", 64);
	if (flags & CV_EVENT_FLAG_ALTKEY)
		strncat (str, " + ALT", 64);

	cout<< str << endl;
}