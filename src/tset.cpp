// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
  maxPower = mp;
}
// ---------------------------------------------------------------------------
// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
}
// ---------------------------------------------------------------------------
// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
  maxPower = bf.GetLength();
}
// ---------------------------------------------------------------------------
TSet::operator TBitField()
{
  TBitField tmp(this->bitField);
  return tmp;
}
// ---------------------------------------------------------------------------
int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}
// ---------------------------------------------------------------------------
int TSet::IsMember(const int Elem) const // элемент множества?
{
  return bitField.GetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::InsElem(const int Elem) // включение элемента множества
{
  bitField.SetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::DelElem(const int Elem) // исключение элемента множества
{
  bitField.ClrBit(Elem);
}
// ---------------------------------------------------------------------------
// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  maxPower = s.GetMaxPower();
  bitField = s.bitField;
  return *this;
}
// ---------------------------------------------------------------------------
int TSet::operator==(const TSet &s) const // сравнение
{
  return bitField == s.bitField;
}
// ---------------------------------------------------------------------------
int TSet::operator!=(const TSet &s) const // сравнение
{
  return bitField != s.bitField;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const TSet &s) // объединение
{
  TSet tmp(bitField | s.bitField);
  return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet tmp(*this);
  tmp.bitField.SetBit(Elem);
  return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet tmp(*this);
  tmp.bitField.ClrBit(Elem);
  return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet tmp(bitField & s.bitField);
  return tmp;
}
// ---------------------------------------------------------------------------
TSet TSet::operator~(void) // дополнение
{
  TSet tmp(~bitField);
  return tmp;
}
// ---------------------------------------------------------------------------
// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int tmp;
  char ch;
  int i = 0;
  while (i<s.maxPower)
  {
    istr >> tmp;
    s.InsElem(tmp);
    i++;
  }
  return istr;
}
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  char ch = ' ';
  ostr << '{';
  for (int i = 0; i < s.GetMaxPower(); i++)
  {
    if (s.IsMember(i))
    {
      ostr << ch << i;
      ch = ',';
    }
  }
  ostr << '}';
  return ostr;
}
