#pragma once

#include <vector>
#include "core/types.h"
#include "core/encoding.h"
#include "lsp/position.h"

class text_document;

class source_iterator
{
public:
    source_iterator& operator++();   // pre
    source_iterator operator++(int); // post

    source_iterator(text_document& text_document);
    
    utf16unit operator*();

    lsp::position position;
    text_document& text_document;
};