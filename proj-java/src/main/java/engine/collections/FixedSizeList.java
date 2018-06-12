package engine.collections;

/**
 * Lista com tamanho fixo.
 * @param <T> Tipo dos elementos da lista.
 */
public class FixedSizeList<T> {
    /** Array onde os elementos da lista estão guardados. */
    private final Object[] list;

    /**
     * Cria uma lista com tamanho fixo.
     * @param size O tamanho da lista.
     */
    public FixedSizeList(int size){
        this.list = new Object[size];
    }

    /**
     * Retorna um elemento da lista.
     * @param index O índice do elemento que queremos.
     * @return Um elemento da lista.
     */
    @SuppressWarnings("unchecked")
    public T get(int index){
        return (T) this.list[index];
    }

    /**
     * Muda um elemento da lista.
     * @param index Índice do elemento da lista que queremos mudar.
     * @param element Novo elemento.
     */
    public void set(int index, T element){
        this.list[index] = element;
    }
}
