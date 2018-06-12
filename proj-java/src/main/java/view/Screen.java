package view;

/**
 * Interface que define um ecrã onde T é o tipo dos resultados.
 *
 * @param <T> Tipo dos elementos.
 */
public interface Screen<T> {

    /**
     * Corre e apresenta o ecrã.
     */
    Screen execute();

    /**
     * Retorna os resultados de executar o ecrã.
     *
     * @return Os resultados de executar o ecrã.
     */
    T getResult();
}
