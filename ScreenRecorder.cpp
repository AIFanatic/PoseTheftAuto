#include "ScreenRecorder.h"

ScreenRecorder::ScreenRecorder(std::string output_path, int screen_width, int screen_height) {
	this->screen_width = screen_width;
	this->screen_height = screen_height;

	StringToWString(this->output_path, output_path);

	this->hWnd = ::FindWindow(NULL, "Compatitibility Theft Auto V");
	this->hWindowDC = GetDC(this->hWnd);
	this->hCaptureDC = CreateCompatibleDC(this->hWindowDC);
	this->hCaptureBitmap = CreateCompatibleBitmap(this->hWindowDC, this->screen_width, this->screen_height);
	SelectObject(this->hCaptureDC, hCaptureBitmap);
	SetStretchBltMode(this->hCaptureDC, COLORONCOLOR);

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	GetEncoderClsid(L"image/jpeg", &pngClsid);
}

int ScreenRecorder::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

int ScreenRecorder::StringToWString(std::wstring& ws, const std::string& s) {
	std::wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
	return 0;
}

void ScreenRecorder::Record_Frame(int frame) {
	StretchBlt(this->hCaptureDC, 0, 0, this->screen_width, this->screen_height, this->hWindowDC, 0, 0, this->screen_width, this->screen_height, SRCCOPY | CAPTUREBLT);
	Gdiplus::Bitmap image(hCaptureBitmap, (HPALETTE)0);
	image.Save((this->output_path + L"\\" + std::to_wstring(frame) + L".jpeg").c_str(), &pngClsid, NULL);
}