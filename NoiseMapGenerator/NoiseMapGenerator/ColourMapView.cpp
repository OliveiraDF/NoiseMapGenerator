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
#include "NoiseMapGenerator.h"
#include "ColourMapView.h"
#include "MainDocument.h"


// CColourMapView

IMPLEMENT_DYNCREATE(CColourMapView, CView)

CColourMapView::CColourMapView()
   : m_pBitmap(NULL)
{
}

CColourMapView::~CColourMapView()
{
}

BEGIN_MESSAGE_MAP(CColourMapView, CView)
ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CColourMapView::OnDraw2D)
ON_WM_CREATE()
END_MESSAGE_MAP()


int CColourMapView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CView::OnCreate(lpCreateStruct) == -1)
   {
      return -1;
   }

   // TODO:  Ajoutez ici votre code de création spécialisé
   EnableD2DSupport();

   return 0;
}

void CColourMapView::OnDraw(CDC*)
{
   // TODO: ajoutez ici le code de dessin
}

afx_msg LRESULT CColourMapView::OnDraw2D(WPARAM /*wParam*/, LPARAM lParam)
{
   CMainDocument* pDoc = GetDocument();

   ASSERT_VALID(pDoc);
   if (!pDoc)
   {
      return 0L;
   }

   const COLORREF* pColourMap = pDoc->GetColourMap();
   if (!pColourMap)
   {
      return 0L;
   }

   if (!m_pBitmap || m_szBitmap != pDoc->GetSize())
   {
      Create2DResources();
   }

   ASSERT_VALID(m_pBitmap);
   m_pBitmap->CopyFromMemory(pColourMap, pDoc->GetWidth() * sizeof(COLORREF));

   CHwndRenderTarget* pRenderTarget = reinterpret_cast <CHwndRenderTarget*>(lParam);
   ASSERT_VALID(pRenderTarget);

   const CD2DSizeF& vSize = pRenderTarget->GetSize();
   CD2DRectF        rcDest;
   rcDest.left   = (vSize.width - pDoc->GetWidth()) * 0.5f;
   rcDest.top    = (vSize.height - pDoc->GetHeight()) * 0.5f;
   rcDest.right  = rcDest.left + pDoc->GetWidth();
   rcDest.bottom = rcDest.top + pDoc->GetHeight();

   pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF(RGB(32, 32, 32))));
   pRenderTarget->DrawBitmap(m_pBitmap, rcDest);

   return 0L;
}

// diagnostics de CColourMapView

#ifdef _DEBUG
void CColourMapView::AssertValid() const
{
   CView::AssertValid();
}

#ifndef _WIN32_WCE
void CColourMapView::Dump(CDumpContext& dc) const
{
   CView::Dump(dc);
}

#endif
CMainDocument* CColourMapView::GetDocument() const  // la version non Debug est inline
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDocument)));
   return (CMainDocument*)m_pDocument;
}

#endif //_DEBUG


// gestionnaires de messages de CColourMapView



HRESULT CColourMapView::Create2DResources()
{
   CMainDocument* pDoc = GetDocument();

   ASSERT_VALID(pDoc);
   if (!pDoc)
   {
      return E_ABORT;
   }

   if (m_pBitmap)
   {
      delete m_pBitmap;
      m_pBitmap = NULL;
   }

   HBITMAP hBitmap = ::CreateBitmap(pDoc->GetWidth(), pDoc->GetHeight(), 1, sizeof(COLORREF), NULL);
   if (!hBitmap)
   {
      return E_OUTOFMEMORY;
   }

   CHwndRenderTarget* pRenderTarget = GetRenderTarget();

   m_szBitmap = pDoc->GetSize();
   m_pBitmap  = new CD2DBitmap(pRenderTarget, hBitmap);

   ::DeleteObject(hBitmap);

   return S_OK;
}
