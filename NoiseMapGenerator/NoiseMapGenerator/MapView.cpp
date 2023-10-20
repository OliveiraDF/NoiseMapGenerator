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
#include "MapView.h"
#include "MainDocument.h"

#pragma region Constructors

IMPLEMENT_DYNCREATE(CMapView, retro::gl::CRenderView)

CMapView::CMapView()
	: m_uTextureID(0)
{
}

CMapView::~CMapView()
{
}

#pragma endregion
#pragma region Operations

#ifdef _DEBUG
CMainDocument* CMapView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDocument)));
	return (CMainDocument*)m_pDocument;
}
#endif

#pragma endregion
#pragma region Overridables

void CMapView::OnInitialUpdate()
{
	retro::gl::CRenderView::OnInitialUpdate();
}

void CMapView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	UNREFERENCED_PARAMETER(pSender);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pHint);

	const CMainDocument* pDoc    = GetDocument();
	const LONG           nWidth  = pDoc->GetWidth();
	const LONG           nHeight = pDoc->GetHeight();
	LPCVOID pMap = GetMap();

	MakeCurrent(GetDC());

	if (lHint == CMainDocument::EHint_Recreate)
	{
		if (m_uTextureID)
		{
			DeleteTextures(1, &m_uTextureID);
			m_uTextureID = 0;
		}

		GenTextures(1, &m_uTextureID);
		BindTexture(retro::gl::ETextureType_2D, m_uTextureID);
		TexImage2D(0, 4, { nWidth, nHeight }, 0, retro::gl::EFormatType_RGBA, retro::gl::EDataType_Unsigned_Byte, pMap);
		TexParameter(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Min_Filter, retro::gl::ETextureValue_Nearest);
		TexParameter(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Mag_Filter, retro::gl::ETextureValue_Nearest);
		TexParameter(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Wrap_S, retro::gl::ETextureValue_Clamp);
		TexParameter(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Wrap_T, retro::gl::ETextureValue_Clamp);

		NewList(10, retro::gl::ECompilationMode_Compile);
		Begin(retro::gl::EPrimitiveType_Quads);
		TexCoord2({ 0.f, 0.f }); Vertex2({ 0.f, 0.f });
		TexCoord2({ 1.f, 0.f }); Vertex2({ (FLOAT)nWidth, 0.f });
		TexCoord2({ 1.f, 1.f }); Vertex2({ (FLOAT)nWidth, (FLOAT)nHeight });
		TexCoord2({ 0.f, 1.f }); Vertex2({ 0.f, (FLOAT)nHeight });
		End();
		EndList();
	}
	else if (lHint == CMainDocument::EHint_Update)
	{
		BindTexture(retro::gl::ETextureType_2D, m_uTextureID);
		TexSubImage2D(0, { 0, 0 }, { nWidth, nHeight }, retro::gl::EFormatType_RGBA, retro::gl::EDataType_Unsigned_Byte, pMap);
	}

	UnmakeCurrent();

	Invalidate();
}

void CMapView::OnDraw(CDC* pDC)
{
	// TODO: ajoutez ici le code de dessin
	ASSERT(pDC);
	ASSERT_VALID(pDC);

	CRect rcWnd;
	GetClientRect(rcWnd);

	const CMainDocument* pDoc     = GetDocument();
	const FLOAT          fWidth   = pDoc->GetWidth();
	const FLOAT          fHeight  = pDoc->GetHeight();

	MakeCurrent(pDC);

	ClearColor({ 32, 32, 32 });
	Clear(retro::gl::EClearMask_Color_Buffer_Bit);

	Viewport({ rcWnd });

	MatrixMode(retro::gl::EMatrixMode_Projection);
	LoadIdentity();
	Ortho({ rcWnd }, 1., -1.);

	MatrixMode(retro::gl::EMatrixMode_ModelView);
	LoadIdentity();

	const FLOAT fScaleWidth = static_cast<FLOAT>(rcWnd.Width()) / fWidth;
	const FLOAT fScaleHeight = static_cast<FLOAT>(rcWnd.Height()) / fHeight;
	const FLOAT fBestScale = min(fScaleWidth, fScaleHeight);

	FLOAT fTranslateX = 0.f;
	FLOAT fTranslateY = 0.f;

	if (fScaleWidth > fScaleHeight)
	{
		fTranslateX = ((static_cast<FLOAT>(rcWnd.Width()) - fWidth * fBestScale) * 0.5f);
	}
	else
	{
		fTranslateY = ((static_cast<FLOAT>(rcWnd.Height()) - fHeight * fBestScale) * 0.5f);
	}

	Translate(fTranslateX, fTranslateY, 0.f);
	Scale(fBestScale, fBestScale, 1.f);

	BindTexture(retro::gl::ETextureType_2D, m_uTextureID);

	CallList(10);

	Flush();
	::SwapBuffers(pDC->GetSafeHdc());

	UnmakeCurrent();
}

LPCVOID CMapView::GetMap() const
{
	ASSERT(FALSE);
	return NULL;
}

#pragma endregion
#pragma region Messages

BEGIN_MESSAGE_MAP(CMapView, retro::gl::CRenderView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CMapView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (retro::gl::CRenderView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// TODO:  Ajoutez ici votre code de création spécialisé
	MakeCurrent(GetDC());

	Disable(retro::gl::EFeatureType_Cull_Face);
	Disable(retro::gl::EFeatureType_Lightning);
	Disable(retro::gl::EFeatureType_Depth_Test);
	Disable(retro::gl::EFeatureType_Alpha_Test);
	Enable(retro::gl::EFeatureType_Texture_2D);

	UnmakeCurrent();

	return 0;
}

#pragma endregion