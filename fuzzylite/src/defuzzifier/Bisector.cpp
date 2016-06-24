/*
 Copyright © 2010-2016 by FuzzyLite Limited.
 All rights reserved.

 This file is part of fuzzylite®.

 fuzzylite® is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with
 fuzzylite®. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite® is a registered trademark of FuzzyLite Limited.

 */

#include "fl/defuzzifier/Bisector.h"

#include "fl/term/Aggregated.h"
#include "fl/term/Term.h"

namespace fl {

    Bisector::Bisector(int resolution)
    : IntegralDefuzzifier(resolution) {
    }

    Bisector::~Bisector() {

    }

    std::string Bisector::className() const {
        return "Bisector";
    }

    scalar Bisector::defuzzify(const Term* term, scalar minimum, scalar maximum) const {
        if (not Op::isFinite(minimum + maximum)) return fl::nan;

        const scalar dx = (maximum - minimum) / getResolution();
        int counter = getResolution();
        int left = 0, right = 0;
        scalar leftArea = 0, rightArea = 0;
        scalar xLeft = minimum, xRight = maximum;
        while (counter-- > 0) {
            if (Op::isLE(leftArea, rightArea)) {
                xLeft = minimum + (left + 0.5) * dx;
                leftArea += term->membership(xLeft);
                left++;
            } else {
                xRight = maximum - (right + 0.5) * dx;
                rightArea += term->membership(xRight);
                right++;
            }
        }
        //Inverse weighted average to compensate
        return (leftArea * xRight + rightArea * xLeft) / (leftArea + rightArea);
    }

    Bisector* Bisector::clone() const {
        return new Bisector(*this);
    }

    Defuzzifier* Bisector::constructor() {
        return new Bisector;
    }

}
