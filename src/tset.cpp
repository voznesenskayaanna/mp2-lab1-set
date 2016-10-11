// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return  BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	//return BitField == s.BitField; // true
	int tmp = 1, i = 0;
	if (GetMaxPower() != s.GetMaxPower())
		tmp = 0;
	else
	for (i = 0; i < GetMaxPower(); i++)
	if (BitField != s.BitField)
	{
		tmp = 0;
		break;
	}
	return tmp;

}

int TSet::operator!=(const TSet &s) const // сравнение
{
	//return BitField != s.BitField;
	int tmp = 1, i = 0;
	if (GetMaxPower() != s.GetMaxPower())
		tmp = 0;
	else
	for (i = 0; i < GetMaxPower(); i++)
	if (BitField == s.BitField)
	{
		tmp = 0;
		break;
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(BitField | s.BitField);
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem > -1) && (Elem < GetMaxPower()))
	{
		InsElem(Elem);
		return *this;
	}
	else throw "error";
}


TSet TSet::operator-(const int Elem) // разность с элементом
{

	if ((Elem > -1) && (Elem < GetMaxPower()))
	{
		DelElem(Elem);
		return *this;
	}
	else throw "error";
}


TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(~BitField);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmp; char vvod;
	do
	{
		istr >> vvod;
	} while (vvod != '{');
	do
	{
		istr >> tmp; s.InsElem(tmp);
		do { istr >> vvod; } while ((vvod != ',') && (vvod != '}'));
	} while (vvod != '}');

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i = 0, n;
	char vivod = ' ';
	ostr << "{";
	n = s.GetMaxPower();
	for (i = 0; i < n; i++)
	{
		if (s.IsMember(i))
		{
			ostr << vivod << ' ' << i;
			vivod = ',';
		}
	}
	ostr << " }";
	return ostr;
}
