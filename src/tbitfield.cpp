// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len) : BitLen(len)
{
	if (len <= 0)
		throw "error";
	MemLen = ((len + sizeof(int)* 8 - 1) / (sizeof(int)* 8));
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen))
		return n >> 5;
	else throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	
	if ((n > -1) && (n < BitLen))
		return 1 << (n & 31);
	else throw  "error";

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else throw  "error";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else throw "error";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
		return	pMem[GetMemIndex(n)] & GetMemMask(n);
	else throw  "error";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	if (pMem != 0)
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int tmp = 1, i = 0;
	if (BitLen != bf.BitLen)
		tmp = 0;
	else
	for (i = 0; i < MemLen; i++)
	if (pMem[i] != bf.pMem[i])
	{
		tmp = 0;
		break;
	}
	return tmp;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{


	int tmp = 1; int i = 0;
	if (BitLen != bf.BitLen)
		tmp = 0;
	else
	for (i = 0; i < MemLen; i++)
	if (pMem[i] == bf.pMem[i])
	{
		tmp = 0;
		break;
	}
	return tmp;
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
	if (bf.BitLen>len) len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField tmp(len);

	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
		{
			tmp.SetBit(i);
		}
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0; char vvod = 0;
	while (vvod != ' ')
	do { istr >> vvod; } while (vvod != ' ');
	
	while (1)
	{
		istr >> vvod;
		if (vvod == '0') bf.ClrBit(i++); 
		else
		if (vvod == '1') bf.SetBit(i++); else break;
	}
	return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
	if (bf.GetBit(i) == 0) ostr << '1';
	else ostr << '1';
	return ostr;
}