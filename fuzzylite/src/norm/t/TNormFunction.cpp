/*
 Copyright © 2010-2015 by FuzzyLite Limited.
 All rights reserved.

 This file is part of fuzzylite®.

 fuzzylite® is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with 
 fuzzylite®. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite® is a registered trademark of FuzzyLite Limited.

 */

#include "fl/norm/t/TNormFunction.h"

#include "fl/Operation.h"

namespace fl {

    TNormFunction::TNormFunction(const std::string& formula) : TNorm() {
        _function.variables["a"] = fl::nan;
        _function.variables["b"] = fl::nan;
        if (not formula.empty()) {
            _function.load(formula);
        }
    }

    std::string TNormFunction::className() const {
        return "TNormFunction";
    }

    scalar TNormFunction::compute(scalar a, scalar b) const {
        _function.variables["a"] = a;
        _function.variables["b"] = b;
        return _function.membership(fl::nan);
    }

    Function& TNormFunction::function() {
        return this->function();
    }

    void TNormFunction::setFormula(const std::string& formula) {
        this->_function.load(formula);
    }

    std::string TNormFunction::getFormula() const {
        return _function.getFormula();
    }

    TNormFunction* TNormFunction::clone() const {
        return new TNormFunction(*this);
    }

    TNorm* TNormFunction::constructor() {
        return new TNormFunction;
    }


}
