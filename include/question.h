#ifndef __QUESTION_H__
#define __QUESTION_H__

/**
 * @file
 * \brief Módulo que define uma questão.
 */
#include "dateTime.h"
#include "answer.h"
#include "types.h"

#include <glib.h>
#include <libxml/parserInternals.h>


/**
 * Cria uma questão.
 * @param id O id da questão.
 * @param date A data da questão.
 * @param score O score da questão.
 * @param ownerId O id do autor da questão.
 * @param title O título da questão.
 * @param tags As tags da questão.
 * @param answerCount Conta o número de respostas que a questão tem.
 * @param ownerName O nome do autor da questão.
 * @returns Uma questão.
 */
QUESTION question_create(long id,
                         DATETIME date,
                         int score,
                         long ownerId,
                         const xmlChar* title,
                         const xmlChar* tags,
                         int answerCount,
                         const xmlChar* ownerName);

/**
 * Retorna o id da questão.
 * @param question Uma questão.
 * @returns O id da questão.
 */
long question_get_id(QUESTION question);

/**
 * Retorna a data da questão.
 * @param question Uma questão.
 * @returns A data da questão.
 */
DATETIME question_get_date(QUESTION question);

/**
 * Retorna o score da questão.
 * @param question Uma questão.
 * @returns O score da questão.
 */
int question_get_score(QUESTION question);

/**
 * Retorna o id do autor da questão.
 * @param question Uma questão.
 * @returns O id do autor da questão.
 */
long question_get_owner_id(QUESTION question);

/**
 * Retorna o título da questão.
 * @param question Uma questão.
 * @returns O título da questão.
 */
xmlChar* question_get_title(QUESTION question);

/**
 * Retorna as tags da questão.
 * @param question Uma questão.
 * @returns As tags da questão.
 */
char** question_get_tags(QUESTION question);

/**
 * Retorna o nome do autor da questão.
 * @param question Uma questão.
 * @returns O nome do autor da questão.
 */
xmlChar* question_get_owner_name(QUESTION question);

/**
 * Retorna o número de respostas que a questão tem.
 * @param question Uma questão.
 * @returns O número de respostas que a questão tem.
 */
int question_get_answer_count(QUESTION question);

/**
 * Retorna o número de respostas que a questão tem dentro de um intervalo de tempo.
 * @param question Uma questão.
 * @param dti Um intervalo de tempo.
 * @returns O número de respostas que a questão tem dentro de um intervalo de tempo.
 */
int question_get_answer_count_between_dates(QUESTION question,
                                            DATETIME_INTERVAL dti);

/** Lista ligada de respostas. */
typedef GSList* ANSWERS;

/**
 * Retorna uma lista com as respostas da questão.
 * @param question Uma questão.
 * @returns A lista com as respostas da questão.
 */
ANSWERS question_get_answers(QUESTION question);

/**
 * \brief Adiciona uma resposta na lista de respostas da questão.
 *
 * Inicializa também o apontador para esta questão na resposta
 * passada
 *
 * @param question Uma questão.
 * @param answer Uma resposta.
 */
void question_add_answer(QUESTION question, ANSWER answer);

/**
 * Liberta a memória ocupada pela questão.
 * @param question Uma questão.
 */
void question_destroy(QUESTION question);

/**
 * Liberta a memória ocupada pela questão.
 * @param question Uma questão.
 */
void question_destroy_generic(gpointer question);

/**
 * Compara duas questões conforme o número de respostas que a questão tem.
 * @param a Uma questão.
 * @param b Uma questão.
 * @returns Um número positivo se a questão a tem maior número de respostas, um
 *          número negativo se a questão b tem maior número de respostas ou 0 se
 *          as questões têm o mesmo número de respostas.
 */
int question_answer_count_cmp(const void* a, const void* b);

/**
 * Compara duas questões conforme o número de respostas que a questão tem dentro de um intervalo de tempo.
 * @param a Uma questão.
 * @param b Uma questão.
 * @param dates Um intervalo de tempo.
 * @returns Um número positivo se a questão a tem maior número de respostas, um
 *          número negativo se a questão b tem maior número de respostas ou 0 se
 *          as questões têm o mesmo número de respostas.
 */
int question_answer_count_cmp_with_dates(const void* a,
                                         const void* b,
                                         const void* dates);

/**
 * Compara duas questões conforme a data.
 * @param a Uma questão.
 * @param b Uma questão.
 * @returns Um número negativo se a primeira questão for mais antiga, um número
 *          positivo se a primeira questão for mais recente ou 0 se as questões
 *          tiverem a mesma data.
 */
int question_date_cmp(const void* a, const void* b);

/**
 * Verifica se uma questão tem uma tag.
 * @param question Uma questão.
 * @param tag A tag.
 * @returns 1 se a questão tem a tag, 0 caso contrário.
 */
int question_has_tag(QUESTION question, char* tag);

#endif /* __QUESTION_H__ */
