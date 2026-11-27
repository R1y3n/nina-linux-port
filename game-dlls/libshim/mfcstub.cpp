// Clean-room implementation of the MFCStub classes (CString/CPoint/CRect),
// written against LT2/lithshared/mfcstub/*.h. Not original Monolith code.
#include "mfcstub.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

static char* cs_alloc(DWORD chars, DWORD len)
{
	CStringData* d = (CStringData*)malloc(sizeof(CStringData) + chars + 1);
	d->m_Length = len; d->m_BufferSize = chars + 1;
	return d->data();
}
static char* cs_new(const char* s, DWORD len)
{
	char* b = cs_alloc(len, len);
	if (s && len) memcpy(b, s, len);
	b[len] = 0; return b;
}
#define PD(b) (((CStringData*)(b)) - 1)

CString::CString() { m_pBuffer = cs_new(NULL, 0); }
CString::CString(LPCTSTR p) { m_pBuffer = cs_new(p, p ? (DWORD)strlen(p) : 0); }
CString::CString(const CString& o) { m_pBuffer = cs_new(o.m_pBuffer, o.GetLength()); }
CString::~CString() { if (m_pBuffer) free(PD(m_pBuffer)); }

void CString::CopyString(LPCTSTR p)
{
	DWORD n = p ? (DWORD)strlen(p) : 0;
	if (p == m_pBuffer) return;
	char* nb = cs_new(p, n);           // allocate first: p may alias our buffer
	if (m_pBuffer) free(PD(m_pBuffer));
	m_pBuffer = nb;
}
BOOL CString::ExpandBuffer(DWORD minLength)
{
	if (GetBufferSize() > minLength) return TRUE;
	DWORD len = GetLength();
	char* nb = cs_alloc(minLength, len);
	memcpy(nb, m_pBuffer, len); nb[len] = 0;
	free(PD(m_pBuffer)); m_pBuffer = nb; return TRUE;
}
BOOL CString::ShrinkBuffer(DWORD maxLength)
{
	DWORD len = GetLength(); if (len > maxLength) len = maxLength;
	char* nb = cs_alloc(maxLength, len);
	memcpy(nb, m_pBuffer, len); nb[len] = 0;
	free(PD(m_pBuffer)); m_pBuffer = nb; return TRUE;
}
LPSTR CString::GetBuffer(DWORD minLength) { ExpandBuffer(minLength); return m_pBuffer; }
void CString::ReleaseBuffer(SDWORD length)
{
	if (length < 0) length = (SDWORD)strlen(m_pBuffer);
	if ((DWORD)length >= GetBufferSize()) length = GetBufferSize() - 1;
	m_pBuffer[length] = 0; SetLength((DWORD)length);
}
void CString::FormatV(LPCTSTR fmt, va_list args)
{
	char stackbuf[512]; va_list a2; va_copy(a2, args);
	int n = vsnprintf(stackbuf, sizeof stackbuf, fmt, args);
	if (n < 0) n = 0;
	if ((size_t)n < sizeof stackbuf) CopyString(stackbuf);
	else {
		char* big = (char*)malloc(n + 1); vsnprintf(big, n + 1, fmt, a2);
		CopyString(big); free(big);
	}
	va_end(a2);
}
void CString::Format(LPCTSTR fmt, ...) { va_list a; va_start(a, fmt); FormatV(fmt, a); va_end(a); }
int CString::Find(char ch, DWORD start) const
{
	if (start > GetLength()) return -1;
	const char* p = strchr(m_pBuffer + start, ch); return (ch && p) ? (int)(p - m_pBuffer) : -1;
}
int CString::Find(LPCTSTR sub, DWORD start) const
{
	if (!sub || start > GetLength()) return -1;
	const char* p = strstr(m_pBuffer + start, sub); return p ? (int)(p - m_pBuffer) : -1;
}
int CString::Replace(LPCTSTR pOld, LPCTSTR pNew)
{
	if (!pOld || !*pOld) return 0; if (!pNew) pNew = "";
	size_t lo = strlen(pOld), ln = strlen(pNew); int count = 0;
	CString out; const char* s = m_pBuffer; const char* p;
	while ((p = strstr(s, pOld)) != NULL) {
		CString piece; piece.CopyString(NULL);
		out.Concat(CString(s).Left((DWORD)(p - s))); out.Concat(pNew); s = p + lo; count++;
	}
	if (count) { out.Concat(s); CopyString(out.m_pBuffer); }
	(void)ln; return count;
}
int CString::Compare(LPCTSTR s) const { return strcmp(m_pBuffer, s ? s : ""); }
int CString::CompareNoCase(LPCTSTR s) const { return _stricmp(m_pBuffer, s ? s : ""); }
void CString::Concat(LPCTSTR p)
{
	if (!p || !*p) return;
	DWORD add = (DWORD)strlen(p), len = GetLength();
	char* tmp = NULL; if (p >= m_pBuffer && p <= m_pBuffer + len) { tmp = (char*)malloc(add + 1); memcpy(tmp, p, add + 1); p = tmp; }
	ExpandBuffer(len + add); memcpy(m_pBuffer + len, p, add + 1); SetLength(len + add);
	if (tmp) free(tmp);
}
void CString::Concat(char ch) { char b[2] = { ch, 0 }; if (ch) Concat(b); }
CString CString::Mid(DWORD first, DWORD count) const
{
	DWORD len = GetLength(); if (first > len) first = len; if (count > len - first) count = len - first;
	CString r; r.m_pBuffer = (free(PD(r.m_pBuffer)), cs_new(m_pBuffer + first, count)); return r;
}
CString CString::Mid(DWORD first) const { return Mid(first, GetLength()); }
CString CString::Left(DWORD n) const { return Mid(0, n); }
CString CString::Right(DWORD n) const { DWORD len = GetLength(); if (n > len) n = len; return Mid(len - n, n); }

CPoint::CPoint() { x = 0; y = 0; }
CPoint::CPoint(const CPoint& p) { x = p.x; y = p.y; }
CPoint::CPoint(const POINT* p) { x = p ? p->x : 0; y = p ? p->y : 0; }
CPoint::CPoint(SDWORD nx, SDWORD ny) { x = nx; y = ny; }

CRect::CRect() { left = top = right = bottom = 0; }
CRect::CRect(const RECT& r) { left = r.left; top = r.top; right = r.right; bottom = r.bottom; }
CRect::CRect(const RECT* r) { if (r) *this = CRect(*r); else left = top = right = bottom = 0; }
CRect::CRect(SDWORD l, SDWORD t, SDWORD r, SDWORD b) { left = l; top = t; right = r; bottom = b; }
CRect::CRect(POINT tl, POINT br) { left = tl.x; top = tl.y; right = br.x; bottom = br.y; }
void CRect::SetRect(SDWORD l, SDWORD t, SDWORD r, SDWORD b) { left = l; top = t; right = r; bottom = b; }
BOOL CRect::IntersectRect(const RECT* a, const RECT* b)
{
	RECT r; r.left = a->left > b->left ? a->left : b->left; r.top = a->top > b->top ? a->top : b->top;
	r.right = a->right < b->right ? a->right : b->right; r.bottom = a->bottom < b->bottom ? a->bottom : b->bottom;
	if (r.left >= r.right || r.top >= r.bottom) { left = top = right = bottom = 0; return FALSE; }
	left = r.left; top = r.top; right = r.right; bottom = r.bottom; return TRUE;
}
CPoint& CRect::TopLeft() { return *(CPoint*)&left; }
CPoint& CRect::BottomRight() { return *(CPoint*)&right; }
const CPoint& CRect::TopLeft() const { return *(const CPoint*)&left; }
const CPoint& CRect::BottomRight() const { return *(const CPoint*)&right; }
void CRect::NormalizeRect()
{
	if (left > right) { SDWORD t = left; left = right; right = t; }
	if (top > bottom) { SDWORD t = top; top = bottom; bottom = t; }
}
