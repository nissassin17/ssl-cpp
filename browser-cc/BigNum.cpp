/*
 * BigNum.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: nissassin17
 */

#include "BigNum.h"


const vector<uint8_t>& BigNum::toVector() const {
	return data;
}
bool BigNum::operator!=(BigNum const& operand) const{
    return not operator==(operand);
}
BigNum BigNum::exponent(long long const& exp, BigNum const& modulus) const {
	if (exp == 0)
		return BigNum(1);
    BigNum result(this->exponent(exp >> 1, modulus));

	//square result here
	result = result * result;
    if (modulus != 0)
        result = result % modulus;

    if (exp bitand 1){ //odd
        result = result * *this;
        if (modulus != 0)
            result = result % modulus;
    }

	return result;
}

BigNum::BigNum(const vector<uint8_t>& data, bool const& negative):
	data(data),
	negative(negative){
	refine();
}

BigNum::BigNum(const uint8_t& digit)
: BigNum((digit < 0 ? vector<uint8_t>(1, -digit) : vector<uint8_t> (1, digit)),	digit < 0)
{}



void BigNum::refine() {
	while (!data.empty() and data[0] == 0)
		data.erase(data.begin());
    if (data.empty())
        negative = false;
}

BigNum BigNum::operator *(const BigNum& operand) const{
	std::vector<uint32_t> ret(data.size() + operand.data.size() - 1, 0);
		for (int i = 0; i < data.size(); i++)
			for (int j = 0; j < operand.data.size(); j++)
				ret[i + j] += (uint16_t) data[i] * operand.data[j];
		uint32_t carry(0);
		for (std::vector<uint32_t>::iterator it = ret.begin(); it != ret.end();
				it++) {
			*it += carry;
			carry = *it >> 8;
			*it &= (1 << 8) - 1;
		}
		while (carry > 0) {
			ret.push_back(carry & ((1 << 8) - 1));
			carry >>= 8;
		}
		while (not ret.empty() and *ret.rbegin() == 0)
			ret.pop_back();

    vector<uint8_t> r8;
    for(int i = 0; i < ret.size(); i++)
        r8.push_back(static_cast<uint8_t>(ret[i]));
    return r8;
}

BigNum BigNum::operator -(const BigNum& operand) const{
	return operator+(- operand);
}

BigNum BigNum::operator +(const BigNum& operand) const{
	if (negative)
		return -((*this) + -operand);
	if (operand.negative){//compare
		if (operator==(operand))
			return BigNum(0);
		if (operator<(operand))
			return -((-operand) - *this);
		//do subtract here

		vector<uint8_t> ret(data);
		int carry = 0;
		for(int i = 0; i < data.size(); i++){
	        //with distance i from last digit
			if (i < operand.data.size())
	            //if digit exists in b
				carry += operand.data[operand.data.size() - 1 - i];
			int tmp = (int)ret[ret.size() - 1 - i] - carry;
			if (tmp < 0){
				carry = 1;
				ret[ret.size() - 1 - i] = tmp + (1 << 8);
			}else{
				ret[ret.size() - 1 - i] = tmp;
				carry = 0;
			}
		}
		while (!ret.empty() and ret[0] == 0)
			ret.erase(ret.begin());
		return BigNum(ret);
	}
	//do plus here
	vector<uint8_t> ret(data);
	int carry = 0;
	for(int i = 0; i < data.size(); i++){
        //with distance i from last digit
		if (i < operand.data.size())
            //if digit exists in b
			carry += operand.data[operand.data.size() - 1 - i];
		int tmp = (int)ret[ret.size() - 1 - i] + carry;
		carry = tmp >> 8;
		ret[ret.size() - 1 - i] = tmp bitand ((1 << 8) - 1);
	}
	while (!ret.empty() and ret[0] == 0)
		ret.erase(ret.begin());
	return ret;
}

BigNum BigNum::operator-() const{
	return BigNum(data, not negative);
}

BigNum BigNum::operator %(const BigNum& operand) const{
	return operator-(operator/(operand) * operand);
}

BigNum BigNum::operator /(const BigNum& operand) const{
	std::vector<uint8_t> quotient, current;
		bool started = false;
		for (int i = 0; i < data.size(); i++) {
			current.push_back(data[i]);
			BigNum bcurrent(current);
			uint8_t q = bcurrent.smallDivide(operand);
			current = (bcurrent - operand * q).toVector();
			if (started or q != 0){
				started = true;
				quotient.push_back(q);
			}
		}
	return BigNum(quotient);
}

bool BigNum::operator <(const BigNum& operand) const{
	if (data.size() != operand.data.size())
		return data.size() < operand.data.size();
	return data < operand.data;

}

BigNum BigNum::operator *(uint8_t const& operand) const{
	int carry(0);
	vector<uint8_t> ret(data.size(), 0);
	for (ssize_t i = data.size() - 1; i >= 0; i--) {
		int tmp = static_cast<int>(data[i]) * operand + carry;
		carry = tmp >> 8;
		ret[i] = tmp bitand ((1 << 8) - 1);
	}
    while (carry != 0){
		ret.insert(ret.begin(), carry bitand ((1 << 8) - 1));
        carry >>= 8;
    }
	while(not ret.empty() and ret[0] == 0)
		ret.erase(ret.begin());
	return BigNum(ret);
}

bool BigNum::isNegative() const {
	return negative;
}

BigNum BigNum::abs() const{
	return BigNum(data);
}

bool BigNum::operator ==(const BigNum& operand) const {
	return negative == operand.negative and data == operand.data;
}

uint8_t BigNum::smallDivide(BigNum const& devider) {
	uint8_t low = 0;
	uint8_t high = (1 << 8) - 1;
	while (low < high) {
		uint8_t mid = (low + high) >> 1;
		if (operator<(devider * mid))
		//low = high + 1
		//divider * high <= dividend < divider * (high + 1)
            high = mid - 1;
		else
			low = mid + 1;
	}
	return high;
}
