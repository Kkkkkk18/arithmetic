#ifndef __COMPL_H__
#define __COMPL_H__


template<class T>
class ones_compl_int {
private:
	T bits; // Биты числа
	void set_bits(T bits); // Прямое присваивание в обратном коде
	void add(T op); // Сложение в обратном коде
	void mul(T op); // Умножение в обратном коде
	void div(T op); // Деление в обратном коде
	void shl(); // Сдвиг влево на 1 бит
	void shr(); // Сдвиг вправо на 1 бит
	T negate() const; // Возвращает число с обратным знаком в обратном коде
	T negate(T op) const; // Возвращает число op с обратным знаком в обратном коде
public:
	ones_compl_int(long long num); // Конструктор. В него передается число = значение данного объекта
	long long value(); // Метод, возвращающий значение числа
	// Операторы
	ones_compl_int<T> operator + (const ones_compl_int<T>& op) {
		ones_compl_int<T> result(0);
		result.set_bits(bits);
		result.add(op.bits);
		return result;
	}
	ones_compl_int<T> operator - (const ones_compl_int<T>& op) {
		ones_compl_int<T> result(0);
		result.set_bits(bits);
		result.add(op.negate());
		return result;
	}
	ones_compl_int<T> operator * (const ones_compl_int<T>& op) {
		ones_compl_int<T> result(0);
		result.set_bits(bits);
		result.mul(op.bits);
		return result;
	}
	ones_compl_int<T> operator / (const ones_compl_int<T>& op) {
		ones_compl_int<T> result(0);
		result.set_bits(bits);
		result.div(op.bits);
		return result;
	}
	ones_compl_int<T> operator += (const ones_compl_int<T>& op) {
		add(op.bits);
		return *this;
	}
	ones_compl_int<T> operator -= (const ones_compl_int<T>& op) {
		add(op.negate());
		return *this;
	}
	ones_compl_int<T> operator *= (const ones_compl_int<T>& op) {
		mul(op.bits);
		return *this;
	}
	ones_compl_int<T> operator /= (const ones_compl_int<T>& op) {
		div(op.bits);
		return *this;
	}
	bool operator == (const ones_compl_int<T>& op) {
		ones_compl_int<T> buf(0);
		buf.set_bits(bits);
		buf.add(op.negate());
		return buf.value() == 0;
	}
	bool operator != (const ones_compl_int<T>& op) {
		return !(*this == op);
	}
	bool operator < (const ones_compl_int<T>& op) {
		ones_compl_int<T> buf(0);
		buf.set_bits(bits);
		buf.add(op.negate());
		return buf.value() < 0;
	}
	bool operator > (const ones_compl_int<T>& op) {
		ones_compl_int<T> buf(0);
		buf.set_bits(bits);
		buf.add(op.negate());
		return buf.value() > 0;
	}
	bool operator <= (const ones_compl_int<T>& op) {
		ones_compl_int<T> buf(0);
		buf.set_bits(bits);
		buf.add(op.negate());
		return buf.value() <= 0;
	}
	bool operator >= (const ones_compl_int<T>& op) {
		ones_compl_int<T> buf(0);
		buf.set_bits(bits);
		buf.add(op.negate());
		return buf.value() >= 0;
	}
};

template<class T>
ones_compl_int<T>::ones_compl_int(long long num) { // Конструктор
	if (num >= 0)
		bits = num;
	else {
		unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
		unsigned long long inv_mask = leftmost_bit - 1;
		unsigned long long positive = -num;
		// Старший бит устанавливаем в 1, прочие биты инвертируем
		bits = leftmost_bit | (positive ^ inv_mask);
	}
}

template<class T>
long long ones_compl_int<T>::value() { // Метод, возвращающий значение числа
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long inv_mask = leftmost_bit - 1;
	if ((bits & inv_mask) == 0)
		return 0;
	if (bits & leftmost_bit) {
		// Отрицательно число
		return -(long long)(((bits & inv_mask) ^ inv_mask));
	}
	else // Положительное число
		return bits;
}

template<class T>
void ones_compl_int<T>::set_bits(T bits) { // Прямое присваивание в обратном коде
	this->bits = bits;
}

template<class T>
T ones_compl_int<T>::negate(T op) const { // Возвращает число op с обратным знаком в обратном коде
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long inv_mask = leftmost_bit - 1;

	if (op & leftmost_bit) // Отрицательное число
		return (op ^ leftmost_bit) ^ inv_mask;
	else
		return leftmost_bit | (op ^ inv_mask);
}

template<class T>
T ones_compl_int<T>::negate() const { // Возвращает число с обратным знаком в обратном коде
	return negate(bits);
}

template<class T>
void ones_compl_int<T>::add(T op) { // Сложение в обратном коде
	unsigned long long carry_bit = (unsigned long long) 1 << (sizeof(T) * 8);
	unsigned long long mask = carry_bit - 1;
	unsigned long long sum = (((unsigned long long) bits) & mask) + (((unsigned long long) op) & mask);
	if (sum & carry_bit) { // Если возник перенос
		sum = (sum ^ carry_bit) + 1; // то бит переноса отбрасываем
	}
	bits = (T)sum;
}

template<class T>
void ones_compl_int<T>::mul(T op) { // Умножение в обратном коде
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long B = (op & leftmost_bit) ? negate(op) : op; // Множитель
	ones_compl_int<T> addition(0);
	addition.set_bits(bits);
	set_bits(0);
	// Порязрядное умножение
	for (int i = 0; i < sizeof(T) * 8 - 1; i++) {
		if (B & (1 << i))
			*this += addition;
		addition.shl();
	}
	if (op & leftmost_bit)
		set_bits(negate());
}

template<class T>
void ones_compl_int<T>::shl() { // Сдвиг влево на 1 бит
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long carry_bit = (unsigned long long) 1 << (sizeof(T) * 8);
	unsigned long long mask = carry_bit - 1;
	if (bits & leftmost_bit)
		bits = leftmost_bit | ((((unsigned long long) bits) & mask) << 1) | 1;
	else
		bits <<= 1;
}

template<class T>
void ones_compl_int<T>::div(T op) { // Деление в обратном коде
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long A = (bits & leftmost_bit) ? negate(bits) : bits; // Делимое
	unsigned long long B = (op & leftmost_bit) ? negate(op) : op; // Делитель
	bool neg_flag = ((op & leftmost_bit) ^ (bits & leftmost_bit)) != 0;
	unsigned long long res = 0;
	ones_compl_int<T> subtraction(0);
	int nB = 0; // Считаем число значимых битов в положительном делителе
	unsigned long long _B = B;
	while (_B) {
		_B >>= 1;
		nB++;
	}
	// Сдвигаем делитель влево, насколько возможно
	unsigned long long _A = A >> nB;
	nB = 1;
	_B = B;
	while (_A) {
		_B <<= 1;
		_A >>= 1;
		nB++;
	}
	subtraction.set_bits(_B);
	set_bits(A);
	// Обычное деление "столбиком"
	while (nB) {
		res <<= 1;
		if (*this >= subtraction) {
			add(subtraction.negate());
			res |= 1;
		}
		nB--;
		subtraction.shr();
	}
	if (neg_flag)
		set_bits(negate(res));
	else
		set_bits(res);
}

template<class T>
void ones_compl_int<T>::shr() { // Сдвиг вправо на 1 бит
	unsigned long long leftmost_bit = (unsigned long long) 1 << (sizeof(T) * 8 - 1);
	unsigned long long carry_bit = (unsigned long long) 1 << (sizeof(T) * 8);
	unsigned long long mask = carry_bit - 1;
	if (bits & leftmost_bit)
		bits = leftmost_bit | (leftmost_bit >> 1) | ((((unsigned long long) bits) & mask) >> 1);
	else
		bits >>= 1;
}

#endif