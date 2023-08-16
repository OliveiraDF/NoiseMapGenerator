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

#pragma once

class CMainDocument;

class CHeightMapView : public CView
{
   DECLARE_DYNCREATE(CHeightMapView)

protected:

   CHeightMapView();                // constructeur protégé utilisé par la création dynamique
   virtual ~CHeightMapView();

public:

   CMainDocument* GetDocument() const;
   virtual void OnDraw(CDC* pDC);            // substitué pour dessiner cette vue

#ifdef _DEBUG
   virtual void AssertValid() const;

#ifndef _WIN32_WCE
   virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

   afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);

   DECLARE_MESSAGE_MAP()

public:

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

private:

   HRESULT Create2DResources();

   CD2DBitmap* m_pBitmap;
   CSize m_szBitmap;
};

#ifndef _DEBUG  // version Debug dans MainTabView.cpp
inline CMainDocument* CHeightMapView::GetDocument() const
{
   return reinterpret_cast <CMainDocument*>(m_pDocument);
}

#endif
