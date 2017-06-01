#include "Header.h"
int CaptureBMP(LPCTSTR szFile)
{
	HDC hdcScr, hdcMem;
	HBITMAP hbmScr;
	BITMAP bmp;
	int iXRes, iYRes;
	hdcScr = CreateDC("DISPLAY", NULL, NULL, NULL);
	hdcMem = CreateCompatibleDC(hdcScr);
	iXRes = GetDeviceCaps(hdcScr, HORZRES);
	iYRes = GetDeviceCaps(hdcScr, VERTRES);
	hbmScr = CreateCompatibleBitmap(hdcScr, iXRes, iYRes);
	if (hbmScr == 0)
		return 0;
	if (!SelectObject(hdcMem, hbmScr))
		return 0;
	if (!StretchBlt(hdcMem, 0, 0, iXRes, iYRes, hdcScr, 0, 0, iXRes, iYRes, SRCCOPY))
		return 0;
	PBITMAPINFO pbmi;
	WORD cClrBits;
	if (!GetObject(hbmScr, sizeof(BITMAP), (LPSTR)&bmp))
		return 0;
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;
	if (cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);
	pbmi->bmiHeader.biCompression = BI_RGB;
	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * cClrBits;
	pbmi->bmiHeader.biClrImportant = 0;
	HANDLE hf;                 
	BITMAPFILEHEADER hdr;       
	PBITMAPINFOHEADER pbih;     
	LPBYTE lpBits;              
	DWORD dwTotal;             
	DWORD cb;                   
	BYTE *hp;                   
	DWORD dwTmp;
	pbih = (PBITMAPINFOHEADER)pbmi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	if (!lpBits) return 0;
	if (!GetDIBits(hdcMem, hbmScr, 0, (WORD)pbih->biHeight, lpBits, pbmi, DIB_RGB_COLORS)) return 0;
	hf = CreateFile(szFile, GENERIC_READ | GENERIC_WRITE, (DWORD)0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		return 0;
	hdr.bfType = 0x4d42;       
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed *sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed *sizeof(RGBQUAD);
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER), (LPDWORD)&dwTmp, NULL))
		return 0;

	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof(RGBQUAD), (LPDWORD)&dwTmp, NULL))
		return 0;
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) return 0;

	if (!CloseHandle(hf))
		return 0;
	GlobalFree((HGLOBAL)lpBits);
	ReleaseDC(0, hdcScr);
	ReleaseDC(0, hdcMem);
	return 1;
}
void MkScreen(char path[], struct Data *data)
{
	setlocale(LC_CTYPE, "russian");
	for (int i = 0; i < strlen(path); i++)
	{
		path[i] = path[i + 1];
	}
	char str[100] = "D:\\RemoteAdministration\\";
	strcat(str, path);
	CaptureBMP(str);
	char a[100];
	strcpy(a, "f");
	strcat(a, path);
	sendFileFunction(a, data);
}