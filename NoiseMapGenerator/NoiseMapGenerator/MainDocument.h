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

protected:

   // création à partir de la sérialisation uniquement
   CMainDocument() noexcept;
   DECLARE_DYNCREATE(CMainDocument)

// Attributs

public:

// Opérations

public:

// Substitutions

public:

   virtual BOOL OnNewDocument();
   virtual void Serialize(CArchive& ar);

// Implémentation

public:

   virtual ~CMainDocument();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages

protected:

   DECLARE_MESSAGE_MAP()

public:

   HRESULT Generate(BOOL bRealloc);

private:

   COLORREF* m_pColourMap;
   COLORREF* m_pHeightMap;
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
   const COLORREF* GetColourMap() const;
   const COLORREF* GetHeightMap() const;

private:

   void Clear();

public:

   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
