#ifndef __LOAD_H__
#define __LOAD_H__

 /**
 * @file
 * \brief Módulo que carrega os dados dos ficheiros xml para a estrutura definida.
 */
#include "types.h"

 /**
 * Carrega os posts, users e tags dos ficheiros em dump_path para uma instância da estrutura.
 * @param com Uma instância da estrutura.
 * @param dump_path Caminho para os ficheiros xml.
 * @returns A instância com os novos dados inseridos.
 */
TAD_community load(TAD_community com, char* dump_path);

#endif /* __LOAD_H__ */
