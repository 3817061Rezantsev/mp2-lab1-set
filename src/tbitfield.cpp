// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0) throw "NEGATIVE_LENGTH";
  bitLen = len;
  memLen = (len + 31) >> 5;
  pMem = new TELEM[memLen];
  if (pMem != 0)
    for (int i = 0; i < memLen; i++)
      pMem[i] = 0;
}
// ---------------------------------------------------------------------------
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  if (pMem != 0)
     for (int i = 0; i < memLen; i++)
       pMem[i] = bf.pMem[i];
}
// ---------------------------------------------------------------------------
TBitField::~TBitField()
{
  if (pMem != 0)
    delete pMem;
  pMem = NULL;
}
// ---------------------------------------------------------------------------
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n >> 5;
}
// ---------------------------------------------------------------------------
TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM tmp = 1;
  return tmp << (n % 32);
}
// ---------------------------------------------------------------------------
// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}
// ---------------------------------------------------------------------------
void TBitField::SetBit(const int n) // установить бит
{
  if ((n > -1) && (n < bitLen))
  {
    int i = GetMemIndex(n);
    pMem[i] = pMem[i] | GetMemMask(n);
  }
  else throw "SET_BIT_WITH_NEGATIVE_OR_TOO_LARGE_INDEX";
}
// ---------------------------------------------------------------------------
void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n > -1) && (n < bitLen))
  {
    int i = GetMemIndex(n);
    pMem[i] = pMem[i] & ~GetMemMask(n);
  }
  else throw "CLEAR_BIT_WITH_NEGATIVE_OR_TOO_LARGE_INDEX";
}
// ---------------------------------------------------------------------------
int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n > -1) && (n < bitLen))
  {
    int i = GetMemIndex(n);
    return (pMem[i] & GetMemMask(n)) >> (n % 16);
  }
  else throw "GET_BIT_WITH_NEGATIVE_OR_TOO_LARGE_INDEX";
  return 0;
}
// ---------------------------------------------------------------------------
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  bitLen = bf.bitLen;
  if (memLen != bf.memLen)
  {
     memLen = bf.memLen;
     if (pMem != NULL)
       delete pMem;
     pMem = new TELEM[memLen];
  }
  if (pMem != NULL)
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}
// ---------------------------------------------------------------------------
int TBitField::operator==(const TBitField &bf) const // сравнение
{
  TELEM MemMask = 0xffffffff;
  int res = 1;
  if (bitLen != bf.bitLen)
    res = 0;
  else
    for (int i = 0; i < memLen - 1; i++)
      if ((pMem[i] & MemMask) != (bf.pMem[i] & MemMask))
      {
        res = 0;
        break;
      }
  for (int i = (memLen - 1) << 5; i < bitLen; i++)
    if (GetBit(i) != bf.GetBit(i))
    {
      res = 0;
      break;
    }
  return res;
}
// ---------------------------------------------------------------------------
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (int i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = bitLen;
	if (bf.bitLen > len)
		len = bf.bitLen;
	TBitField temp(len);
	for (int i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator~(void) // отрицание
{
	int len = bitLen;
	TBitField temp(len);
	for (int i = 0; i < bitLen; i++)
		if (GetBit(i) == 0)
			temp.SetBit(i);
	return temp;
}
// ---------------------------------------------------------------------------
// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;

	while (i<bf.bitLen)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1')
			bf.SetBit(i++);
		else break;
	}
	return istr;
}
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		ostr << bf.GetBit(i);
	return ostr;
}
