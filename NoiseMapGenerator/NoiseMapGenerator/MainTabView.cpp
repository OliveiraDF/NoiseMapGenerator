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
#include "framework.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL, et permettent le partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "NoiseMapGenerator.h"
#endif

#include "MainDocument.h"
#include "MainTabView.h"

#include "ColourMapView.h"
#include "HeightMapView.h"

#ifdef _DEBUG
#define new    DEBUG_NEW
#endif

#pragma region Constructors

IMPLEMENT_DYNCREATE(CMainTabView, CTabView)

CMainTabView::CMainTabView() noexcept
{
	
}

CMainTabView::~CMainTabView()
{

}

#pragma endregion
#pragma region Operations

#ifdef _DEBUG
CMainDocument* CMainTabView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDocument)));
	return (CMainDocument*)m_pDocument;
}
#endif

#pragma endregion
#pragma region Overridables

void CMainTabView::OnDraw(CDC* /*pDC*/)
{
	CMainDocument* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}
}

BOOL CMainTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTabView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CMainTabView::AssertValid() const
{
	CTabView::AssertValid();
}

void CMainTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif

#pragma endregion
#pragma region Messages

BEGIN_MESSAGE_MAP(CMainTabView, CTabView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CMainTabView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMainTabView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

int CMainTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// TODO:  Ajoutez ici votre code de création spécialisé
	CCreateContext Context;
	Context.m_pCurrentDoc = GetDocument();

	AddView(RUNTIME_CLASS(CColourMapView), I18N(IDS_VIEW_COLOUR_MAP), 100, &Context);
	AddView(RUNTIME_CLASS(CHeightMapView), I18N(IDS_VIEW_HEIGHT_MAP), 101, &Context);

	return 0;
}

#pragma endregion