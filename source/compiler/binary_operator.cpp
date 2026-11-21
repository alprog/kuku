
#include "binary_operator.h"

std::vector<binary_operator>& get_binary_operators()
{
    static std::vector<binary_operator> operators {
        { token_type::exponent_operator, precedence::exponentiation },

        { token_type::multiply_Operator, precedence::multiplication },
        { token_type::divide_Operator, precedence::multiplication },

        { token_type::plus_operator, precedence::addition },
        { token_type::minus_operator, precedence::addition },
        
        { token_type::less_operator, precedence::relational },
        { token_type::greater_operator, precedence::relational },
        { token_type::less_or_equal_operator, precedence::relational },
        { token_type::greater_or_equal_operator, precedence::relational },

        { token_type::equal_operator, precedence::equality },
        { token_type::not_equal_operator, precedence::equality },
    };

    return operators;
}