#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

 /**
 * @file
 * \brief Módulo que define a API para interagir com as estururas
 *        definidas que armazenam toda a informação retirada dos ficheiros xml.
 */
#include "date.h"
#include "soUser.h"
#include "answer.h"
#include "question.h"
#include "types.h"

#include <glib.h>

 /**
 * Alias para a função community_create.
 * @returns Uma instância da estrutura.
 */
TAD_community init();

 /**
 * Cria uma instância da estrutura.
 * @returns Uma instância da estrutura.
 */
TAD_community community_create();

 /**
 * Liberta a memória ocupada pela instância da estrutura.
 * @param com Uma instância da estrutura.
 */
void community_destroy(TAD_community com);

 /**
 * Adiciona uma questão à estrutura.
 * @param com Uma instância da estrutura.
 * @param question A questão a adicionar.
 */
void community_add_question(TAD_community com, QUESTION question);

 /**
 * Adiciona uma resposta à estrutura
 * @param com Uma instância da estrutura.
 * @param answer A resposta a adicionar.
 */
void community_add_answer(TAD_community com, ANSWER answer);

 /**
 * Adiciona um user à estrutura.
 * @param com Uma instância da estrutura.
 * @param user O user a adicionar.
 */
void community_add_user(TAD_community com, SO_USER user);

 /**
 * Adiciona uma tag à estrutura.
 * @param com Uma instância da estrutura.
 * @param id O id da tag.
 * @param tag O nome da tag.
 */
void community_add_tag(TAD_community com, long id, const xmlChar* tag);

 /**
 * Encontra o user com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id do user.
 * @returns Um user.
 */
SO_USER community_get_user(TAD_community com, long id);

 /**
 * Encontra a questão com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id da questão.
 * @returns Uma questão.
 */
QUESTION community_get_question(TAD_community com, long id);

 /**
 * Encontra a resposta com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id da resposta.
 * @returns Uma resposta.
 */
ANSWER community_get_answer(TAD_community com, long id);

 /**
 * Retorna o número total de users.
 * @param com Uma instância da estrutura.
 * @returns O número total de users.
 */
long community_get_user_count(TAD_community com);

 /**
 * Retorna o número total de questões.
 * @param com Uma instância da estrutura.
 * @returns O número total de questões.
 */
long community_get_question_count(TAD_community com);

 /**
 * Retorna o número total de respostas.
 * @param com Uma instância da estrutura.
 * @returns O número total de respostas.
 */
long community_get_answer_count(TAD_community com);

 /** Lista ligada de users. */
typedef GSList* USERS;

 /**
 * Retorna uma lista ordenada de users.
 * @param com Uma instância da estrutura.
 * @param cfunc Função de comparação.
 * @param N Tamanho da lista retornada.
 * @returns Uma lista ordenada de users.
 */
USERS community_get_sorted_user_list(TAD_community com, ComCmpFunc cfunc, int N);

 /** Lista ligada de questões. */
typedef GSList* QUESTIONS;

 /**
 * Retorna uma lista ordenada de questões.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param func Função de comparação.
 * @param N Tamanho da lista retornada.
 * @returns Uma lista ordenada de questões.
 */
QUESTIONS community_get_sorted_question_list(TAD_community com, DATETIME from, DATETIME to, ComCmpFunc func, int N);

 /**
 * Retorna uma lista ordenada de questões.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param func Função de comparação.
 * @param N Tamanho da lista retornada.
 * @param compare_data Informação extra passada a função de comparação.
 * @returns Uma lista ordenada de questões.
 */
QUESTIONS community_get_sorted_question_list_with_data(TAD_community com, DATETIME from, DATETIME to, ComGetValueFunc func, int N, void* compare_data);

 /** Lista ligada de respostas. */
typedef GSList* ANSWERS;

 /**
 * Retorna uma lista ordenada de respostas.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param func Função de comparação.
 * @param N Tamanho da lista retornada.
 * @returns Uma lista ordenada de respostas.
 */
ANSWERS community_get_sorted_answer_list(TAD_community com, DATETIME from, DATETIME to, ComCmpFunc func, int N);

 /**
 * Retorna uma lista de questões filtrada conforme a função de filtragem.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param N Tamanho da lista retornada.
 * @param func Função de filtragem.
 * @param filter_data Informação passada a func.
 * @returns Uma lista de questões filtrada conforme a função de filtragem.
 */
QUESTIONS community_get_filtered_questions(TAD_community com, DATETIME from, DATETIME to, int N, ComFilterFunc func, void* filter_data);

 /**
 * Encontra o id da tag fornecida.
 * @param com Uma instância da estrutura.
 * @param tag O nome da tag.
 * @returns O id.
 */
long community_get_tag_id(TAD_community com, xmlChar* tag);

 /**
 * Itera pelas questões, por ordem cronológica, aplicando a função dada a cada questão.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param data Informação para passar à função.
 * @param calFunc A função aplicada a cada questão.
 */
void community_iterate_questions(TAD_community com, DATETIME from, DATETIME to, void* data, CalFunc calFunc);

 /**
 * Itera pelas respostas, por ordem cronológica, aplicando a função dada a cada resposta.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param data Informação para passar à função.
 * @param calFunc A função aplicada a cada resposta.
 */
void community_iterate_answers(TAD_community com, DATETIME from, DATETIME to, void* data, CalFunc calFunc);

/* ------------- PRINTING --------------------- */

 /**
 * Imprime os users de uma estrutura.
 * @param com Uma instância da estrutura.
 */
void community_print_users(TAD_community com);

 /**
 * Imprime as questões de uma estrutura.
 * @param com Uma instância da estrutura.
 */
void community_print_questions(TAD_community com);

 /**
 * Imprime as respostas de uma estrutura.
 * @param com Uma instância da estrutura.
 */
void community_print_answers(TAD_community com);

 /**
 * Imprime o calendário de uma estrutura.
 * @param com Uma instância da estrutura.
 */
void community_print_calendario(TAD_community com);

 /**
 * Imprime os ids das respostas e da questão da thread a que o post pertence,
 * acompanhadas do id do autor.
 * @param com Uma instância da estrutura.
 * @param id Id de uma pergunta ou resposta.
 */
void community_print_thread(TAD_community com, long id);

#endif /* __COMMUNITY_H__ */
