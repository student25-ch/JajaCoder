/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#include "jajacoder.h"
void model_infer(const char *prompt, char *out, const char *retrieved_context)
{
    if(retrieved_context && strlen(retrieved_context) > 0)
    {
        snprintf(out, MAX_REPLY_LEN,
        "[RAG CONTEXT]: %s\nUser Question: %s\nAnswer: Based on the context above, I reply.",
        retrieved_context, prompt);
    }else{
        snprintf(out, MAX_REPLY_LEN,
        "User Question: %s\nAnswer: No relevant context found in index.", prompt);
    }
}
