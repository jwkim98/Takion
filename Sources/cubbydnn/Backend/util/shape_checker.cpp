//
// Created by jwkim on 18. 11. 20.
//
#include "Backend/util_decl/shape_checker.hpp"

bool shape_checker::check_shape(const tensor_shape &shape,
                                const std::string &op_name)
{
    // TODO: find way to check if argument was verifiable
    static bool has_been_valid = true;

    if (!has_been_valid)
        return false;

    if (shape.empty())
    {
        has_been_valid = false;
        std::cout << "Argument shape is empty" << std::endl;
    }

    if (!has_been_valid)
    {
        std::cout << "This Error occurs from operation: " << op_name
                  << std::endl;
    }
    return has_been_valid;
}


tensor_shape::tensor_shape(long rows, long columns, long height){
    this->shape_vect = {rows, columns, height};
    total_size = 1;
    for(auto mul: shape_vect){
        total_size*= mul;
    }
}

bool tensor_shape::operator==(const tensor_shape &rhs) const {
    return shape_vect == rhs.shape_vect;
}

bool tensor_shape::operator!=(const tensor_shape &rhs) const {
    return !(rhs == *this);
}
