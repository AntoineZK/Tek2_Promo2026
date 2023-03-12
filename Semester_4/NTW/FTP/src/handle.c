/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** handle
*/

#include "ftp.h"

int create_socket(int port)
{
    int server_fd = 0;
    int bind_status = 0;
    int listen_status = 0;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_fd == -1 ? exit(84) : 0;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt)) < 0 ? exit(84) : 0;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind_status = bind(server_fd, (const struct sockaddr *)&addr, sizeof(addr));
    printf("Server listening on port %d.\r\n", port);
    bind_status == -1 ? exit(84) : 0;
    listen_status = listen(server_fd, 42);
    listen_status == -1 ? exit(84) : 0;
    return server_fd;
}

void handle_connection(ftp_t *ftp)
{
    int new_client = accept(ftp->server_fd, (struct sockaddr *)
    &ftp->socket_addr, &ftp->socket_addr_len);
    new_client == -1 ? exit(84) : 0;
    ftp->clients = add_node_last(ftp->clients, new_client, ftp->path);
    dprintf(new_client, M_220);
}

void handle_requests(ftp_t *ftp)
{
    ftp->tmp = ftp->clients;
    ftp->num_remove = 0;
    for (int i = 0; ftp->tmp; i++) {
        if (FD_ISSET(ftp->tmp->client_fd, &ftp->readfds))
            ftp = fd_is_set(ftp, i);
        ftp->tmp = ftp->tmp->next;
    }
    for (; ftp->num_remove > 0; ftp->num_remove--)
        ftp->clients = remove_node_terminated(ftp->clients);
}

ftp_t *fd_is_set(ftp_t *ftp, int i)
{
    int read_status = 0;
    char *tmp = NULL;

    printf("Client %d is ready.\n", ftp->tmp->client_fd);
    tmp = malloc(sizeof(char) * (4097));
    read_status = read(ftp->tmp->client_fd, tmp, 4096);
    tmp[read_status] = '\0';
    if (read_status > 0) {
        my_strcat(&ftp->tmp->buffer, tmp);
        if (check_buffer(ftp->tmp->buffer) == false)
            return (ftp);
        printf("Client %d sent: %s\n", ftp->tmp->client_fd, ftp->tmp->buffer);
        ftp = execute_command(ftp, i);
        free(ftp->tmp->buffer);
        ftp->tmp->buffer = malloc(sizeof(char));
        ftp->tmp->buffer[0] = '\0';
    } else
        ftp = disconnect(ftp, i);
    free(tmp);
    return ftp;
}
