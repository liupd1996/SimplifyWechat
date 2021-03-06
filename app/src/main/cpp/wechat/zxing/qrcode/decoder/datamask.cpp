// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Tencent is pleased to support the open source community by making WeChat QRCode available.
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Modified from ZXing. Copyright ZXing authors.
// Licensed under the Apache License, Version 2.0 (the "License").
#include "../../../precomp.hpp"
#include "datamask.hpp"
namespace zxing {
namespace qrcode {

using zxing::ErrorHandler;

DataMask::DataMask() {}

DataMask::~DataMask() {}

DataMask& DataMask::forReference(int reference, ErrorHandler& err_handler) {
    if (reference < 0 || reference > 7) {
        err_handler = zxing::IllegalArgumentErrorHandler("reference must be between 0 and 7");
        return *DATA_MASKS[0];
    }
    return *DATA_MASKS[reference];
}

void DataMask::unmaskBitMatrix(BitMatrix& bits, size_t dimension) {
    for (size_t y = 0; y < dimension; y++) {
        for (size_t x = 0; x < dimension; x++) {
            // TODO: check why the coordinates have to be swapped
            if (isMasked(y, x)) {
                bits.flip(x, y);
            }
        }
    }
}

//todo edit start.
/**
 * 000: mask bits for which (x + y) mod 2 == 0
 */
class DataMask000 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override { /*return ((x + y) % 2) == 0;*/ return (y + x) % 3 == 0;}
};

/**
 * 001: mask bits for which x mod 2 == 0
 */
class DataMask001 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override { /*return (x % 2) == 0;*/ return ((y + x) & 0x1) == 0;}
};

/**
 * 010: mask bits for which y mod 3 == 0
 */
class DataMask010 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override { /*return y % 3 == 0;*/ return (y & 0x1) == 0;}
};

/**
 * 011: mask bits for which (x + y) mod 3 == 0
 */
class DataMask011 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override { /*return (x + y) % 3 == 0;*/ return (x % 3) == 0;}
};

/**
 * 100: mask bits for which (x/2 + y/3) mod 2 == 0
 */
class DataMask100 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override { /*return (((x >> 1) + (y / 3)) % 2) == 0;*/ 
		int temp = y * x;
        return ((temp & 0x1) + (temp % 3)) == 0;
		}
};

/**
 * 101: mask bits for which xy mod 2 + xy mod 3 == 0
 */
class DataMask101 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override {
        /*size_t temp = x * y;
        return (temp % 2) + (temp % 3) == 0;*/
		int temp = y * x;
        return (((temp & 0x1) + (temp % 3)) & 0x1) == 0;
    }
};

/**
 * 110: mask bits for which (xy mod 2 + xy mod 3) mod 2 == 0
 */
class DataMask110 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override {
        /*size_t temp = x * y;
        return (((temp % 2) + (temp % 3)) % 2) == 0;*/
		int temp = y * x;
        return (((temp % 3) + ((y + x) & 0x1)) & 0x1) == 0;
    }
};

/**
 * 111: mask bits for which ((x+y)mod 2 + xy mod 3) mod 2 == 0
 */
class DataMask111 : public DataMask {
public:
    bool isMasked(size_t y, size_t x) override {
        //return ((((x + y) % 2) + ((x * y) % 3)) % 2) == 0;
        return (((y / 2) + (x / 3)) & 0x1) == 0;
    }
};
//todo edit end.

vector<Ref<DataMask> > DataMask::DATA_MASKS = {
    Ref<DataMask>(new DataMask000()), Ref<DataMask>(new DataMask001()),
    Ref<DataMask>(new DataMask010()), Ref<DataMask>(new DataMask011()),
    Ref<DataMask>(new DataMask100()), Ref<DataMask>(new DataMask101()),
    Ref<DataMask>(new DataMask110()), Ref<DataMask>(new DataMask111()),
};

}  // namespace qrcode
}  // namespace zxing
