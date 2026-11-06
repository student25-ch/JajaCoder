/* Copyright (C) 2026 JajaCoder-GUI Authors
 * Licensed under GPLv3 */
#include "jajacoder.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8899

static char index_path[] = "./index/rag.index";

int main()
{
    rag_load_index(index_path);

    int server_fd, new_socket;
    struct sockaddr_in addr;
    int opt = 1;
    int addrlen = sizeof(addr);
    char buf[MAX_PROMPT_LEN];
    char reply[MAX_REPLY_LEN];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket fail");
        exit(1);
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 3);
    printf("JajaCoder core listening on :%d\n", PORT);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
        ssize_t r = read(new_socket, buf, MAX_PROMPT_LEN-1);
        if(r <= 0) { close(new_socket); continue; }
        buf[r]=0;

        float qvec[VEC_DIM];
        char retrieved[CHUNK_TEXT_LEN] = {0};

        if(!strncmp(buf, "INGEST:",7)){
            ingest_text(buf+7);
            rag_save_index(index_path);
            snprintf(reply, MAX_REPLY_LEN, "OK: ingested and saved");
        }else if(!strncmp(buf, "QUERY:",6)){
            embed_text(buf+6, qvec);
            rag_search(qvec, retrieved, 0.25f);
            model_infer(buf+6, reply, retrieved);
        }else if(!strncmp(buf, "SAVE:",5)){
            rag_save_index(index_path);
            snprintf(reply, MAX_REPLY_LEN, "OK: saved");
        }else if(!strncmp(buf, "LOAD:",5)){
            rag_load_index(index_path);
            snprintf(reply, MAX_REPLY_LEN, "OK: loaded");
        }else{
            snprintf(reply, MAX_REPLY_LEN, "ERR: unknown cmd");
        }
        write(new_socket, reply, strlen(reply));
        close(new_socket);
    }
    close(server_fd);
    return 0;
}
