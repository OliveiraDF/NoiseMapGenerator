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
#include "MainDocument.h"
#include "resource.h"

#ifdef _DEBUG
#define new    DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainDocument, CDocument)

BEGIN_MESSAGE_MAP(CMainDocument, CDocument)
END_MESSAGE_MAP()

CMainDocument::CMainDocument() noexcept
   : m_pHeightMap(NULL)
   , m_pNoiseMap(NULL)
   , m_pColourMap(NULL)
   , m_fScale(0.)
   , m_uOctaveCount(0)
   , m_fPersistance(0.f)
   , m_fLacunarity(0.f)
{
}

CMainDocument::~CMainDocument()
{
   Clear();
}

BOOL CMainDocument::OnNewDocument()
{
   if (!CDocument::OnNewDocument())
   {
      return FALSE;
   }

   retro::core::Log(I18N(IDS_LOG_NEW_DOCUMENT));

   // TODO: ajoutez ici le code de réinitialisation
   // (les documents SDI réutiliseront ce document)
   MAKE_DUMP(this);

   m_szMap        = { 500, 500 };
   m_fScale       = 25.;
   m_uOctaveCount = 5;
   m_fPersistance = 0.5f;
   m_fLacunarity  = 2.f;

   AfxGetMainWnd()->SendMessageToDescendants(WM_NEW_OPEN_DOCUMENT, 0U, (LPARAM)this);
   Generate(TRUE);

   return TRUE;
}

void CMainDocument::Serialize(CArchive& ar)
{
   if (ar.IsStoring())
   {
      // TODO: ajoutez ici le code de stockage
      ar << m_szMap << m_fScale << m_uOctaveCount << m_fPersistance << m_fLacunarity;
   }
   else
   {
      // TODO: ajoutez ici le code de chargement
      ar >> m_szMap >> m_fScale >> m_uOctaveCount >> m_fPersistance >> m_fLacunarity;
   }
}

#ifdef _DEBUG
void CMainDocument::AssertValid() const
{
   CDocument::AssertValid();
}

void CMainDocument::Dump(CDumpContext& dc) const
{
   CDocument::Dump(dc);

   dc << _T("Width: ") << m_szMap.cx << _T("\n");
   dc << _T("Height: ") << m_szMap.cy << _T("\n");
   dc << _T("Scale: ") << m_fScale << _T("\n");
   dc << _T("OctaveCount: ") << m_uOctaveCount << _T("\n");
   dc << _T("Persistance: ") << m_fPersistance << _T("\n");
   dc << _T("Lacunarity: ") << m_fLacunarity << _T("\n");
}

#endif //_DEBUG

HRESULT CMainDocument::Generate(BOOL bRealloc)
{
   // TODO: Ajoutez ici votre code d'implémentation..
   static const struct
   {
      LPCTSTR  lpszName;
      DOUBLE   fHeight;
      COLORREF clrColour;
   } s_Regions[] =
   {
      { _T("DeepWater"),     0.3, RGB(108,   0,  46) },
      { _T("ShallowWater"),  0.4, RGB(156,  97,  38) },
      { _T("Sand"),         0.45, RGB(169, 205, 224) },
      { _T("Grass1"),       0.55, RGB(15,  120,  34) },
      { _T("Grass2"),        0.6, RGB(50,   87,  23) },
      { _T("Rock1"),         0.7, RGB(40,   86, 149) },
      { _T("Rock2"),         0.9, RGB(0,    41,  88) },
      { _T("Snow"),           1., RGB(255, 255, 255) }
   };
   static constexpr const UINT s_uRegionCount = ARRAYSIZE(s_Regions);

   const UINT uSize = GetWidth() * GetHeight();

   if (bRealloc)
   {
      Clear();

      m_pNoiseMap = new DOUBLE[uSize];
      if (!m_pNoiseMap)
      {
         return E_OUTOFMEMORY;
      }

      m_pColourMap = new COLORREF[uSize];
      if (!m_pColourMap)
      {
         return E_OUTOFMEMORY;
      }

      m_pHeightMap = new COLORREF[uSize];
      if (!m_pHeightMap)
      {
         return E_OUTOFMEMORY;
      }
   }

   retro::core::NoiseMap(m_pNoiseMap, m_szMap.cx, m_szMap.cy, m_fScale, m_uOctaveCount, m_fPersistance, m_fLacunarity);

   for (UINT i = 0; i < uSize; i++)
   {
      const DOUBLE fCurrentHeight = m_pNoiseMap[i];
      const BYTE   uNG            = static_cast <BYTE>(retro::core::Lerp(0., 255., fCurrentHeight));
      m_pHeightMap[i] = RGB(uNG, uNG, uNG);
      for (UINT j = 0; j < s_uRegionCount; j++)
      {
         if (fCurrentHeight <= s_Regions[j].fHeight)
         {
            m_pColourMap[i] = s_Regions[j].clrColour;
            break;
         }
      }
   }

   retro::core::Log(I18N(IDS_LOG_GENERATE_SUCCESS));

   UpdateAllViews(NULL);

   return S_OK;
}

void CMainDocument::SetProperty(DWORD_PTR uProperty, const COleVariant& Variant)
{
   const EProperty eProperty = static_cast <EProperty>(uProperty);
   BOOL            bRealloc  = FALSE;

   switch (eProperty)
   {
       case EProperty_Size_X:
          m_szMap.cx = Variant.lVal;
          bRealloc   = TRUE;
          break;

       case EProperty_Size_Y:
          m_szMap.cy = Variant.lVal;
          bRealloc   = TRUE;
          break;

       case EProperty_Scale:
          m_fScale = Variant.dblVal;
          break;

       case EProperty_OctaveCount:
          m_uOctaveCount = Variant.uintVal;
          break;

       case EProperty_Persistance:
          m_fPersistance = Variant.fltVal;
          break;

       case EProperty_Lacunarity:
          m_fLacunarity = Variant.fltVal;
          break;

       default:
          return;
   }

   SetModifiedFlag(TRUE);
   Generate(bRealloc);
}

const CSize& CMainDocument::GetSize() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   // TODO: insérer une instruction return ici
   return m_szMap;
}

LONG CMainDocument::GetWidth() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_szMap.cx;
}

LONG CMainDocument::GetHeight() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_szMap.cy;
}

DOUBLE CMainDocument::GetScale() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_fScale;
}

FLOAT CMainDocument::GetLacunarity() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_fLacunarity;
}

FLOAT CMainDocument::GetPersistance() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_fPersistance;
}

UINT CMainDocument::GetOctaveCount() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_uOctaveCount;
}

const COLORREF* CMainDocument::GetColourMap() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_pColourMap;
}

const COLORREF* CMainDocument::GetHeightMap() const
{
   // TODO: Ajoutez ici votre code d'implémentation..
   return m_pHeightMap;
}

void CMainDocument::Clear()
{
   // TODO: Ajoutez ici votre code d'implémentation..
   if (m_pNoiseMap)
   {
      delete[] m_pNoiseMap;
      m_pNoiseMap = NULL;
   }

   if (m_pColourMap)
   {
      delete[] m_pColourMap;
      m_pColourMap = NULL;
   }

   if (m_pHeightMap)
   {
      delete[] m_pHeightMap;
      m_pHeightMap = NULL;
   }
}

BOOL CMainDocument::OnOpenDocument(LPCTSTR lpszPathName)
{
   if (!CDocument::OnOpenDocument(lpszPathName))
   {
      return FALSE;
   }

   CString strLog;
   strLog.Format(IDS_LOG_OPEN_DOCUMENT, lpszPathName);
   retro::core::Log(strLog.GetString());

   // TODO:  Ajoutez ici votre code de création spécialisé
   AfxGetMainWnd()->SendMessageToDescendants(WM_NEW_OPEN_DOCUMENT, 0U, (LPARAM)this);
   Generate(TRUE);

   return TRUE;
}
