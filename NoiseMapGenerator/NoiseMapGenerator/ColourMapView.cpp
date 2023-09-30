/**
 *
 * Noise Map Generator
 *
 * MIT License
 *
 * Copyright (c) 2023 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"
#include "ColourMapView.h"
#include "MainDocument.h"

#pragma region Constructors

IMPLEMENT_DYNCREATE(CColourMapView, retro::gl::CRenderView)

CColourMapView::CColourMapView()
{
}

CColourMapView::~CColourMapView()
{
}

#pragma endregion

BEGIN_MESSAGE_MAP(CColourMapView, retro::gl::CRenderView)
ON_WM_CREATE()
END_MESSAGE_MAP()

LPCVOID CColourMapView::GetMap() const
{
	CMainDocument* pDoc = GetDocument();

	IWICBitmap* pBitmap = pDoc->GetColourMap();

	IWICBitmapLock* pLock = NULL;

	pBitmap->Lock(NULL, WICBitmapLockRead, &pLock);

	UINT             uBufferSize = 0;
	WICInProcPointer pPixels     = NULL;
	pLock->GetDataPointer(&uBufferSize, &pPixels);

	return pPixels;
}

int CColourMapView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMapView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// TODO:  Ajoutez ici votre code de création spécialisé

	return 0;
}
