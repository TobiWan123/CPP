#include "Graphic.h"

Graphic::Graphic() {
	renderTarget = NULL;
	factory = NULL;
}

Graphic::~Graphic() {
    if (factory) SAFE_RELEASE(factory);;
    if (renderTarget) SAFE_RELEASE(renderTarget);;
    if (brush) SAFE_RELEASE(brush);
}

bool Graphic::init(HWND windowHandle) {
    if (!renderTarget)
    {
        HRESULT hr;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
        if (FAILED(hr))
        {
            MessageBox(windowHandle, L"Create D2D factory failed!", L"Error", 0);
            return false;
        }

        // Obtain the size of the drawing area
        RECT rc;
        GetClientRect(windowHandle, &rc);

        // Create a Direct2D render target
        hr = factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                windowHandle,
                D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
            ),
            &renderTarget
        );
        if (FAILED(hr))
        {
            MessageBox(windowHandle, L"Create render target failed!", L"Error", 0);
            return false;
        }

        if (!Graphic::setBrush(D2D1::ColorF::Black)) {
            MessageBox(windowHandle, L"Create brush failed!", L"Error", 0);
            return false;
        }
        return true;
    }

    return false;
}

bool Graphic::setBrush(D2D1::ColorF color) {
    
    if (brush) SAFE_RELEASE(brush);

    // Create a brush
    HRESULT hr = renderTarget->CreateSolidColorBrush(
        D2D1::ColorF(color),
        &brush
    );
    
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void Graphic::ClearScreen() {
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}