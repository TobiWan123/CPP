#pragma once
#include <d2d1.h>

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

class Graphic {
private:
	ID2D1Factory* factory = NULL; // Direct2D factory
	
public: 
	ID2D1HwndRenderTarget* renderTarget = NULL; // Render target
	ID2D1SolidColorBrush* brush = NULL; // A black brush, reflect the line color

	Graphic();
	~Graphic();

	bool init(HWND windowHandle);
	bool setBrush(D2D1::ColorF color);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); } 
	void ClearScreen();

};