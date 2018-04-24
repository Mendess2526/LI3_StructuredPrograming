#ifndef __LOAD_H__
#define __LOAD_H__
/**
 * @file
 * \brief Módulo que carrega os dados dos ficheiros xml para a estrutura definida
 */
#include "types.h"

/**
 * Carrega os conteudos do ficheiros em \p dump_path
 * para a estrutura
 * @param com Instância da estrutura
 * @param dump_path Caminho para os ficheiros xml
 * @returns A instância com os novos dados inseridos
 */
TAD_community load(TAD_community com, char* dump_path);

#endif /*__LOAD_H__*/
