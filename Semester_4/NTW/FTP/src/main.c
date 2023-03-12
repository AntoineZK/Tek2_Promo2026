/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** main
*/

#include "ftp.h"

void ftp_loop(ftp_t *ftp)
{
    while (1) {
        set_fd(ftp);
        int max_fd = fd_max(ftp) + 1;
        int select_status = select(FD_SETSIZE, &ftp->readfds, NULL, NULL, NULL);
        select_status == -1 ? exit(84) : 0;
        if (FD_ISSET(ftp->server_fd, &ftp->readfds))
            handle_connection(ftp);
        handle_requests(ftp);
    }
    lk_list_destroy(ftp->clients);
    close(ftp->server_fd);
}

int main(int ac, char **av)
{
    int error_value = error_handling(ac, av);
    if (error_value != 1)
        return error_value;
    ftp_t *ftp = malloc(sizeof(ftp_t));
    init_ftp(ftp, av);
    ftp_loop(ftp);
    free(ftp);
    return 0;
}
