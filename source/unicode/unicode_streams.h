#pragma once

#include "unicode.h"
#include "streams.h"
#include <deque>

namespace unicode
{
    class utf8to16_stream : public input_stream<utf16unit>
    {
    public:
        input_stream<utf8unit>& input_stream;
        queue_stream<utf16unit> queue_stream;

        utf8to16_stream(::input_stream<utf8unit>& utf8_stream);

        virtual bool read(utf16unit& out_unit) override;
    };
}
