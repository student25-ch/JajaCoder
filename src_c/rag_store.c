/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#include "jajacoder.h"
RagChunk rag_index[MAX_CHUNK];
int rag_count = 0;

float vec_cosine(float *a, float *b)
{
    float dot=0, sa=0, sb=0;
    for(int i=0;i<VEC_DIM;i++){
        dot += a[i]*b[i];
        sa += a[i]*a[i];
        sb += b[i]*b[i];
    }
    if(sa<1e-9 || sb<1e-9) return 0;
    return dot / (sqrtf(sa)*sqrtf(sb));
}

void rag_add_chunk(float *vec, const char *txt)
{
    if(rag_count >= MAX_CHUNK) return;
    memcpy(rag_index[rag_count].vec, vec, sizeof(float)*VEC_DIM);
    strncpy(rag_index[rag_count].text, txt, CHUNK_TEXT_LEN-1);
    rag_index[rag_count].text[CHUNK_TEXT_LEN-1] = 0;
    rag_count++;
}

int rag_search(float *query_vec, char *out_text, float threshold)
{
    float best_sim = -1;
    int best_idx = -1;
    for(int i=0;i<rag_count;i++)
    {
        float s = vec_cosine(query_vec, rag_index[i].vec);
        if(s > best_sim && s > threshold){
            best_sim = s;
            best_idx = i;
        }
    }
    if(best_idx < 0) return 0;
    strcpy(out_text, rag_index[best_idx].text);
    return 1;
}

int rag_save_index(const char *path)
{
    FILE *fp = fopen(path, "wb");
    if(!fp) return -1;
    fwrite(&rag_count, sizeof(int), 1, fp);
    fwrite(rag_index, sizeof(RagChunk), rag_count, fp);
    fclose(fp);
    return 0;
}

int rag_load_index(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if(!fp) return -1;
    fread(&rag_count, sizeof(int), 1, fp);
    fread(rag_index, sizeof(RagChunk), rag_count, fp);
    fclose(fp);
    return 0;
}
