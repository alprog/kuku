
#include "unicode_streams.h"

namespace unicode {

utf8to16_stream::utf8to16_stream(::input_stream<utf8unit>& input_stream)
    : input_stream{ input_stream }
{
}

bool utf8to16_stream::read(utf16unit& out_unit)
{
    if (queue_stream.read(out_unit))
    {
        return true;
    }

    character character;
    if (read_character(input_stream, character))
    {
        write_character(queue_stream, character);
        if (queue_stream.read(out_unit))
        {
            return true;
        }
    }
    
    return false;
}

}