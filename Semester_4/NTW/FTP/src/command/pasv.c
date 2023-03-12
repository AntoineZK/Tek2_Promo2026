/*
** EPITECH PROJECT, 2023
** B-NWP-400-NCY-4-1-myftp-antoine.khalidy
** File description:
** pasv
*/

#include "ftp.h"

ftp_t *pasv(ftp_t *ftp, int j)
{
    if (ftp->tmp->logged == false) {
        dprintf(ftp->tmp->client_fd, M_530);
        return (ftp);
    }
    srand(time(NULL));
    int new_port = 1024 + rand() % 64511;
    int new_socket = create_socket(new_port);
    if (new_socket == -1) {
        dprintf(ftp->tmp->client_fd, M_425);
        return (ftp);
    }
    int new_port_bit = new_port / 256;
    int new_port_bit2 = new_port % 256;
    dprintf(ftp->tmp->client_fd,
    "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n", new_port_bit,
    new_port_bit2);
    ftp->tmp->pasv_fd = new_socket;
    ftp->tmp->pasv = true;
    return (ftp);
}
