#ifndef __SO_USER_H__
#define __SO_USER_H__

typedef struct _so_user *SO_USER;

SO_USER create_so_user(int id,
                        int reputation,
                        char *bio);

void destroy_so_user(SO_USER user);

#endif /*__SO_USER_H__*/