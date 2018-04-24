#ifndef __SO_USER_H__
#define __SO_USER_H__

/**
 * @file
 * Módulo que define um user.
 */
#include "post.h"
#include "types.h"

#include <glib.h>
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
 * Compara dois users conforme o número de posts.
 * @param a Um user.
 * @param b Um user.
 * @returns Um número positivo se o user a tem mais posts, um número negativo se
 *          o user b tem mais posts ou 0 se os users têm o mesmo número de posts.
 */
int so_user_post_count_cmp(const void* a, const void* b);

/**
 * Compara dois users conforme a reputação dos users.
 * @param a Um user.
 * @param b Um user.
 * @returns Um número positivo se o user a tem melhor reputação, um número 
 *          negativo se o user b tem melhor reputação ou 0 se os users têm a 
 *          mesma reputação.
 */
int so_user_reputation_cmp(const void* a, const void* b);

#endif /* __SO_USER_H__ */