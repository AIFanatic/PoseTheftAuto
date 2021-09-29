#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <string>

class ScreenRecorder
{
	public:
		ScreenRecorder::ScreenRecorder(std::string output_path, int screen_width, int screen_height);

		void ScreenRecorder::Record_Frame(int frame);

	private:
		int ScreenRecorder::GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
		int ScreenRecorder::StringToWString(std::wstring& ws, const std::string& s);

		std::wstring output_path;
		int screen_width;
		int screen_height;
		int imageWidth;
		int imageHeight;

		HWND hWnd;
		HDC hWindowDC;
		HDC hCaptureDC;
		HBITMAP hCaptureBitmap;
		CLSID pngClsid;
};

