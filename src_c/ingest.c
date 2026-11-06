/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#include "jajacoder.h"
void ingest_text(const char *text)
{
    char buf[CHUNK_TEXT_LEN];
    float vec[VEC_DIM];
    const char *p = text;
    while(*p)
    {
        int len = 0;
        while(*p && len < CHUNK_TEXT_LEN-1)
        {
            buf[len++] = *p++;
            if(*p == '.' || *p == '\n') { p++; break; }
        }
        buf[len] = 0;
        embed_text(buf, vec);
        rag_add_chunk(vec, buf);
    }
}
