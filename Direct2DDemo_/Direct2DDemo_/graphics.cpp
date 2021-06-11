#include <windows.h>
#include <D2D1.h>

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

ID2D1Factory* g_pD2DFactory = NULL; // Direct2D factory
ID2D1HwndRenderTarget* g_pRenderTarget = NULL; // Render target
ID2D1SolidColorBrush* g_pBlackBrush = NULL; // A black brush, reflect the line color

VOID CreateD2DResource(HWND hWnd)
{
    if (!g_pRenderTarget)
    {
        HRESULT hr;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
        if (FAILED(hr))
        {
            MessageBox(hWnd, L"Create D2D factory failed!", L"Error", 0);
            return;
        }

        // Obtain the size of the drawing area
        RECT rc;
        GetClientRect(hWnd, &rc);

        // Create a Direct2D render target
        hr = g_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                hWnd,
                D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
            ),
            &g_pRenderTarget
        );
        if (FAILED(hr))
        {
            MessageBox(hWnd, L"Create render target failed!", L"Error", 0);
            return;
        }

        // Create a brush
        hr = g_pRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Black),
            &g_pBlackBrush
        );
        if (FAILED(hr))
        {
            MessageBox(hWnd, L"Create brush failed!", L"Error", 0);
            return;
        }
    }
}

VOID DrawLine(HWND hwnd)
{
    CreateD2DResource(hwnd);

    g_pRenderTarget->BeginDraw();

    // Clear background color to White
    g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    // Draw Rectangle
    g_pRenderTarget->DrawLine(
        D2D1::Point2F(100.0f, 100.0f),
        D2D1::Point2F(500.0f, 500.0f),
        g_pBlackBrush
    );

    HRESULT hr = g_pRenderTarget->EndDraw();
    if (FAILED(hr))
    {
        MessageBox(NULL, L"Draw failed!", L"Error", 0);
        return;
    }
}


VOID Cleanup()
{
    SAFE_RELEASE(g_pRenderTarget);
    SAFE_RELEASE(g_pBlackBrush);
    SAFE_RELEASE(g_pD2DFactory);
}