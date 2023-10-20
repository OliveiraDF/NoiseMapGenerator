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

class CMainDocument : public CDocument
{
public:

	enum EProperty
	{
		EProperty_Size_X,
		EProperty_Size_Y,
		EProperty_Scale,
		EProperty_OctaveCount,
		EProperty_Persistance,
		EProperty_Lacunarity,

		EProperty_COUNT
	};

	enum EHint : LPARAM
	{
		EHint_Recreate,
		EHint_Update,

		EHint_COUNT
	};

	#pragma region Constructors

protected:

	CMainDocument() noexcept;
	DECLARE_DYNCREATE(CMainDocument)

public:

	virtual ~CMainDocument();

	#pragma endregion
	#pragma region Attributes

private:

	IWICBitmap* m_pColourMap;
	IWICBitmap* m_pHeightMap;
	DOUBLE* m_pNoiseMap;
	DOUBLE m_fScale;
	UINT m_uOctaveCount;
	FLOAT m_fPersistance;
	FLOAT m_fLacunarity;
	CSize m_szMap;

public:

	void SetProperty(DWORD_PTR uProperty, const COleVariant& Variant);
	const CSize& GetSize() const;
	LONG GetWidth() const;
	LONG GetHeight() const;
	DOUBLE GetScale() const;
	FLOAT GetLacunarity() const;
	FLOAT GetPersistance() const;
	UINT GetOctaveCount() const;
	IWICBitmap* GetColourMap() const;
	IWICBitmap* GetHeightMap() const;

	#pragma endregion
	#pragma region Operations

public:

	HRESULT ExportColourMap(LPCTSTR lpszFileName) const;
	HRESULT ExportHeightMap(LPCTSTR lpszFileName) const;

	#pragma endregion
	#pragma region Overridables

public:

	BOOL OnNewDocument() override;
	BOOL OnOpenDocument(LPCTSTR lpszPathName) override;
	void Serialize(CArchive& ar) override;

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

	#pragma endregion
	#pragma region Implementations

private:

	HRESULT Generate(BOOL bRealloc);
	HRESULT ExportMap(LPCTSTR lpszFileName, IWICBitmap* pMap) const;
	void Clear();

	#pragma endregion
	#pragma region Messages

protected:

	DECLARE_MESSAGE_MAP()

	#pragma endregion
};
