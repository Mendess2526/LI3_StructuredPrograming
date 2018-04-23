#ifndef __SO_USER_H__
#define __SO_USER_H__

#include "post.h"
#include <glib.h>
#include "types.h"

#include <libxml/parserInternals.h>

typedef GSList * POSTS;

 /**
 * Cria um user.
 * @param id O id do user.
 * @param reputation A reputação do user.
 * @param name O nome do user.
 * @param bio A biografia do user.
 * @returns Um user.
 */
SO_USER so_user_create(long id,
                        int reputation,
                        xmlChar *name,
                        xmlChar *bio);

 /**
 * Retorna o id do user.
 * @param user Um user.
 * @returns O id do user.
 */
long so_user_get_id(SO_USER user);

 /**
 * Retorna a reputação do user.
 * @param user Um user.
 * @returns A reputação do user.
 */
int so_user_get_reputation(SO_USER user);

 /**
 * Retorna o nome do user.
 * @param user Um user.
 * @returns O nome do user.
 */
xmlChar *so_user_get_name(SO_USER user);

 /**
 * Retorna a biografia do user.
 * @param user Um user.
 * @returns A biografia do user.
 */
xmlChar *so_user_get_bio(SO_USER user);

 /**
 * Adiciona um post na lista de posts do user.
 * @param user Um user.
 * @param post O post a adicionar.
 */
void so_user_add_post(SO_USER user, POST post);

 /**
 * Retorna o número de posts de um user.
 * @param user Um user.
 * @returns O número de posts.
 */
int so_user_get_post_count(SO_USER user);

 /**
 * Retorna a lista de posts de um user.
 * @param user Um user.
 * @returns A lista de posts.
 */
POSTS so_user_get_posts(SO_USER user);

 /**
 * Liberta a memória ocupada pelo user.
 * @param user Um user.
 */
void so_user_destroy(SO_USER user);

 /**
 * Liberta a memória ocupada pelo user.
 * @param user Um user.
 */
void so_user_destroy_generic(gpointer user);

/**
 * Compara dois utilizadore conforme o número de posts
 * @param a Utilizador a
 * @param b Utilizador b
 * @returns Um número positivo se \p a tiver menos posts, 0 se ambos tiverem
 *          o mesmo número de posts, e -1 se \p a tiver mais posts.
 */
int so_user_post_count_cmp(const void* a, const void* b);

int so_user_reputation_cmp(const void* a, const void* b);

#endif /*__SO_USER_H__*/
