#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__
/**
 * @file
 * Ficheiro que define a API para interagir com as estururas
 * definidas que armazenam toda a informação retirada dos ficheiros xml
 */
#include <glib.h>
#include "date.h"
#include "soUser.h"
#include "answer.h"
#include "question.h"
#include "types.h"

/**
 * Alias para a função community_create
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
 * Adiciona um user ao tipo abstrato de dados.
 * @param com Uma instância da estrutura.
 * @param user O user a adicionar.
 */
void community_add_user(TAD_community com, SO_USER user);

 /**
 * Adiciona uma tag ao tipo abstrato de dados.
 * @param com Uma instância da estrutura.
 * @param id O id da tag.
 * @param tag O nome da tag.
 */
void community_add_tag(TAD_community com, long id, xmlChar* tag);

 /**
 * Encontra o user com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id do user.
 * @returns O user.
 */
SO_USER community_get_user(TAD_community com, long id);

 /**
 * Encontra a questão com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id da questão.
 * @returns A questão.
 */
QUESTION community_get_question(TAD_community com, long id);

 /**
 * Encontra a resposta com o id fornecido.
 * @param com Uma instância da estrutura.
 * @param id O id da resposta.
 * @returns A resposta.
 */
ANSWER community_get_answer(TAD_community com, long id);

long community_get_user_count(TAD_community com);

long community_get_question_count(TAD_community com);

long community_get_answer_count(TAD_community com);

typedef GSList* USERS;

USERS community_get_sorted_user_list(TAD_community com, ComCmpFunc cfunc, int N);

typedef GSList* QUESTIONS;

QUESTIONS community_get_sorted_question_list(TAD_community com, DATETIME from, DATETIME to, ComCmpFunc func, int N);

typedef GSList* ANSWERS;

ANSWERS community_get_sorted_answer_list(TAD_community com, DATETIME from, DATETIME to, ComCmpFunc func, int N);

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
void community_iterate_questions(TAD_community com, DATETIME from, DATETIME to, void* data, CFunc calFunc);

 /**
 * Itera pelas respostas, por ordem cronológica, aplicando a função dada a cada resposta.
 * @param com Uma instância da estrutura.
 * @param from A data de início.
 * @param to A data do fim.
 * @param data Informação para passar à função.
 * @param calFunc A função aplicada a cada resposta.
 */
void community_iterate_answers(TAD_community com, DATETIME from, DATETIME to, void* data, CFunc calFunc);

/* ------------- PRINTING --------------------- */


void printUsers(TAD_community com);

void printQuestions(TAD_community com);

void printAnswers(TAD_community com);

void printFavouritesCount(TAD_community com);

void community_print_calendario(TAD_community com);

void community_print_thread(TAD_community com, long id);
#endif /*__COMMUNITY_H__*/
