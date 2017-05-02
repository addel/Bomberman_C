#ifndef __SERVER_H__
#define __SERVER_H__

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

/* Client's Structure */
typedef struct	s_clients
{
  int		fd;
  int		id;
  int           nb_bomb;
  int		fbomb;
  int		stock_bomb;
  int		power_bomb;
  int		done;
}		t_clients;

/* Bomb's Structure */
typedef struct  s_bombs
{
  int		id;
  int           x;
  int           y;
  int		to_explode;
}               t_bombs;

/* Map's Structure */
typedef struct  s_map
{
  int           x;
  int		y;
  int		min;
  int		max;
  int		new_move;
}               t_map;

/* Prototypes */
int     server_main(int fd_socket, t_clients *clients);
int     init_serv(int fd_socket, int port);
int     wait_client(int fd_socket, t_clients **clients);
int     client_connect(int fd_socket);
int     start_coms(int fd_socket, t_clients *clients, int map[10][10], t_bombs *bombs);
void    init_fd_set(int fd_socket, fd_set *readfds, t_clients *clients);
int     my_select(fd_set *readfds, int n);
int     manage(fd_set *readfds, t_clients *clients, int map[10][10], t_bombs *bombs, int fd_socket);
void	prohibit_client(int fd_socket, fd_set *readfds);
int     my_close_sock(int client);
void    my_putstr(char *str, int fd);
void    my_putint(int nb, int fd);
char    *my_memset(char *s, int n);
char	*my_strcat(char *str1, char *str2);
int     my_strcmp(char *str1, char *str2);
int	commands(char *buff, t_clients *clients, int map[10][10], t_bombs *bombs);
void    *find_player(t_map *coord, int player, int map[10][10]);
int     init_map(int fd_socket, t_clients *clients);
void    display_map(int map[10][10]);
void    trigger(int *a, int *box, t_map coord, int map[10][10], int trig);
int     move_xory(t_map coord, t_clients *clients, char *buff, int map[10][10], int trig);
int     player_dies(t_clients *clients, int player_id, int map[10][10]);
void	init_coord(int client, char *buff, t_map *coord, int map[10][10]);
int	clients_signal(int client, int id, int len, char *buff);
int	send_info(t_clients *clients, char *buff, int flag);
int     send_borm(t_clients *clients, int id, int borm, int pm);
void	init_bomb(t_clients *clients);
int     drop_bomb(t_clients *clients, char *buff, t_map *coord, t_bombs **bombs);
void	put_bomb_map(t_clients *clients, int map[10][10], t_bombs **bombs);;
int     verif_fbomb(t_clients *clients);
int     explode_bomb(t_clients *clients, t_bombs *bombs, int map[10][10]);
int     verif_players(t_clients *clients, int map[10][10]);
int	my_random(t_clients *clients, int x, int y);
int	bonus_malus(t_clients *clients, int borm, int id);
void    map_bm(t_clients *clients, t_bombs *bombs, int cible, int map[10][10]);
void	map_pw(t_bombs *bombs, int map[10][10], int cible, int pw);
void	manage_bomb(t_clients *clients);
int	new_position(t_map coord, t_clients *clients, char *buff, int map[10][10], int trig);
int	up_flag(int map[10][10], int id);
int	verif_neg(t_clients *clients, int id, int p);
int	win_or_lose(t_clients *clients, int player_id);

#endif
