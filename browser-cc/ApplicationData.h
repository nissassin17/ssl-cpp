/*
 * ApplicationData.h
 *
 *  Created on: Nov 21, 2015
 *      Author: nissassin17
 */

#ifndef APPLICATIONDATA_H_
#define APPLICATIONDATA_H_

#include "Exportable.hpp"
#include <vector>
using namespace std;

class ApplicationData: public Exportable {
public:
	ApplicationData(vector<uint8_t> const& appData);
	vector<uint8_t> getData() const;
};

#endif /* APPLICATIONDATA_H_ */
