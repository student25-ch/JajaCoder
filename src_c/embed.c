/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#include "jajacoder.h"

void embed_text(const char *txt, float *vec)
{
    memset(vec, 0, sizeof(float)*VEC_DIM);
    unsigned int hash = 1315423911;
    int i = 0;
    while (*txt && i < CHUNK_TEXT_LEN - 1)
    {
        char c = tolower((unsigned char)*txt);
        hash ^= ((hash << 5) + c + (hash >> 2));
        int slot = hash % VEC_DIM;
        vec[slot] += (c - 'a' + 1) / 26.0f;
        txt++;
        i++;
    }
    vec_normalize(vec);
}

void vec_normalize(float *v)
{
    float sum = 0.0f;
    for(int i=0; i<VEC_DIM; i++) sum += v[i]*v[i];
    if(sum < 1e-9f) return;
    float inv = 1.0f / sqrtf(sum);
    for(int i=0; i<VEC_DIM; i++) v[i] *= inv;
}
