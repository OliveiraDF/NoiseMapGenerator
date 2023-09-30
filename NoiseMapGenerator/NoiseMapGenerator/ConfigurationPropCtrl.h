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

class CConfigurationPropCtrl : public CMFCPropertyGridCtrl
{
	#pragma region Constructors

	DECLARE_DYNAMIC(CConfigurationPropCtrl)

public:

	CConfigurationPropCtrl();
	virtual ~CConfigurationPropCtrl();

	#pragma endregion
	#pragma region Attributes

private:

	CMFCPropertyGridProperty* m_pSizeX;
	CMFCPropertyGridProperty* m_pSizeY;
	CMFCPropertyGridProperty* m_pNoiseScale;
	CMFCPropertyGridProperty* m_pOctaveCount;
	CMFCPropertyGridProperty* m_pPersistance;
	CMFCPropertyGridProperty* m_pLacunarity;

	#pragma endregion
	#pragma region Overridables

public:

	void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const override;

	#pragma endregion
	#pragma region Messages

protected:

	DECLARE_MESSAGE_MAP()

public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:

	afx_msg LRESULT OnNewOpenDocument(WPARAM wParam, LPARAM lParam);

	#pragma endregion
};
