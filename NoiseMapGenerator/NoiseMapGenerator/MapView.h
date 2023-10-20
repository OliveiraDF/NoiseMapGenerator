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

class CMapView : public retro::gl::CRenderView
{
#pragma region Constructors

	DECLARE_DYNCREATE(CMapView)

protected:

	CMapView();
	virtual ~CMapView();

#pragma endregion
#pragma region Attributes

private:

	UINT m_uTextureID;
	CSize	m_vWindowSize;

#pragma endregion
#pragma region Operations

public:

	CMainDocument* GetDocument() const;

#pragma endregion
#pragma region Overridables

public:

	void OnInitialUpdate() override;
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
	void OnDraw(CDC* pDC) override;

	virtual LPCVOID GetMap() const;

#pragma endregion
#pragma region Messages

protected:

	DECLARE_MESSAGE_MAP()

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

#pragma endregion

};

#ifndef _DEBUG
inline CMainDocument* CMapView::GetDocument() const
{
	return reinterpret_cast <CMainDocument*>(m_pDocument);
}
#endif
