/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#ifndef JAJACODER_H
#define JAJACODER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_PROMPT_LEN 4096
#define MAX_REPLY_LEN 8192
#define VEC_DIM 64
#define MAX_CHUNK 1024
#define CHUNK_TEXT_LEN 512

typedef struct {
    float vec[VEC_DIM];
    char text[CHUNK_TEXT_LEN];
} RagChunk;

extern RagChunk rag_index[MAX_CHUNK];
extern int rag_count;

float vec_cosine(float *a, float *b);
void vec_normalize(float *v);
void embed_text(const char *txt, float *vec);
int rag_search(float *query_vec, char *out_text, float threshold);
void rag_add_chunk(float *vec, const char *txt);
int rag_save_index(const char *path);
int rag_load_index(const char *path);
void model_infer(const char *prompt, char *out, const char *retrieved_context);
void ingest_text(const char *text);

#endif
